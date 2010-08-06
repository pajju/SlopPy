/* 

   SlopPy: A Python interpreter that facilitates sloppy, error-tolerant
   data parsing and analysis
  
   Copyright 2010 Philip J. Guo (pg@cs.stanford.edu). All rights reserved.

   This code carries the same license as the enclosing Python
   distribution: http://www.python.org/psf/license/ 

*/

#include "NAobject.h"
#include "slop.h"

static int
NA_print(SlopNAObject *self, FILE *fp, int flags)
{
	Py_BEGIN_ALLOW_THREADS
	fputs("<NA>", fp);
	Py_END_ALLOW_THREADS
	return 0;
}

static PyObject *NA_str = NULL;

static PyObject *
NA_repr(SlopNAObject *self)
{
  PyObject *s;
  s = NA_str ? NA_str : (NA_str = PyString_InternFromString("<NA>"));
  Py_XINCREF(s);
  return s;
}

// initialize with the 3 arguments of sys.exc_info():
//   (exception type, exception value, traceback object)
static int
NA_init(SlopNAObject *self, PyObject *args, PyObject *kwds)
{
  assert(PyTuple_CheckExact(args));

  if (PyTuple_Size(args) != 3) {
		PyErr_SetString(PyExc_ValueError, "NA object takes exactly 3 args (those produced by sys.exc_info)");
    return -1;
  }

  self->exc_type      = PyTuple_GET_ITEM(args, 0);
  self->exc_value     = PyTuple_GET_ITEM(args, 1);
  self->exc_traceback = PyTuple_GET_ITEM(args, 2);

  return 0;
}


/* Arithmetic operations redefined to return bool if both args are bool. */

static PyObject *
NA_and(PyObject *a, PyObject *b)
{
	if (!PyBool_Check(a) || !PyBool_Check(b))
		return PyInt_Type.tp_as_number->nb_and(a, b);
	return PyBool_FromLong(
		((PyBoolObject *)a)->ob_ival & ((PyBoolObject *)b)->ob_ival);
}

static PyObject *
NA_or(PyObject *a, PyObject *b)
{
	if (!PyBool_Check(a) || !PyBool_Check(b))
		return PyInt_Type.tp_as_number->nb_or(a, b);
	return PyBool_FromLong(
		((PyBoolObject *)a)->ob_ival | ((PyBoolObject *)b)->ob_ival);
}

static PyObject *
NA_xor(PyObject *a, PyObject *b)
{
	if (!PyBool_Check(a) || !PyBool_Check(b))
		return PyInt_Type.tp_as_number->nb_xor(a, b);
	return PyBool_FromLong(
		((PyBoolObject *)a)->ob_ival ^ ((PyBoolObject *)b)->ob_ival);
}


/* Doc string */
PyDoc_STRVAR(NA_doc, "Special NA type for SlopPy");


/* Arithmetic methods -- only so we can override &, |, ^. */
static PyNumberMethods NA_as_number = {
	0,			/* nb_add */
	0,			/* nb_subtract */
	0,			/* nb_multiply */
	0,			/* nb_divide */
	0,			/* nb_remainder */
	0,			/* nb_divmod */
	0,			/* nb_power */
	0,			/* nb_negative */
	0,			/* nb_positive */
	0,			/* nb_absolute */
	0,			/* nb_nonzero */
	0,			/* nb_invert */
	0,			/* nb_lshift */
	0,			/* nb_rshift */
	NA_and,		/* nb_and */
	NA_xor,		/* nb_xor */
	NA_or,		/* nb_or */
	0,			/* nb_coerce */
	0,			/* nb_int */
	0,			/* nb_long */
	0,			/* nb_float */
	0,			/* nb_oct */
	0,		 	/* nb_hex */
	0,			/* nb_inplace_add */
	0,			/* nb_inplace_subtract */
	0,			/* nb_inplace_multiply */
	0,			/* nb_inplace_divide */
	0,			/* nb_inplace_remainder */
	0,			/* nb_inplace_power */
	0,			/* nb_inplace_lshift */
	0,			/* nb_inplace_rshift */
	0,			/* nb_inplace_and */
	0,			/* nb_inplace_xor */
	0,			/* nb_inplace_or */
	0,			/* nb_floor_divide */
	0,			/* nb_true_divide */
	0,			/* nb_inplace_floor_divide */
	0,			/* nb_inplace_true_divide */
};


PyTypeObject SlopNA_Type = {
	PyVarObject_HEAD_INIT(&PyType_Type, 0)
	"NA",
	sizeof(SlopNAObject),
	0,
	0,					/* tp_dealloc */
	(printfunc)NA_print,			/* tp_print */
	0,					/* tp_getattr */
	0,					/* tp_setattr */
	0,					/* tp_compare */
	(reprfunc)NA_repr,			/* tp_repr */
	&NA_as_number,			/* tp_as_number */
	0,					/* tp_as_sequence */
	0,					/* tp_as_mapping */
	(hashfunc)PyObject_HashNotImplemented, /* tp_hash */
  0,					/* tp_call */
  (reprfunc)NA_repr,			/* tp_str */
	0,					/* tp_getattro */
	0,					/* tp_setattro */
	0,					/* tp_as_buffer */
	Py_TPFLAGS_DEFAULT, /* tp_flags */
	NA_doc,			/* tp_doc */
	0,					/* tp_traverse */
	0,					/* tp_clear */
	0,					/* tp_richcompare */
	0,					/* tp_weaklistoffset */
	0,					/* tp_iter */
	0,					/* tp_iternext */
	0,					/* tp_methods */
	0,					/* tp_members */
	0,					/* tp_getset */
	0,          /* tp_base */
	0,					/* tp_dict */
	0,					/* tp_descr_get */
	0,					/* tp_descr_set */
	0,					/* tp_dictoffset */
	(initproc)NA_init,		/* tp_init */
	0,					/* tp_alloc */
	PyType_GenericNew,		/* tp_new */
	0,      		/* tp_free */
};

