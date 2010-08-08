/* 

   SlopPy: A Python interpreter that facilitates sloppy, error-tolerant
   data parsing and analysis
  
   Copyright 2010 Philip J. Guo (pg@cs.stanford.edu). All rights reserved.

   This code carries the same license as the enclosing Python
   distribution: http://www.python.org/psf/license/ 

*/

#include "NAobject.h"
#include "slop.h"

static PyObject *
NA_repr(SlopNAObject *self)
{
  PyObject* type_repr = PyObject_Repr(self->exc_type);
  PyObject* value_repr = PyObject_Repr(self->exc_value);

  PyObject* repr = PyTuple_Pack(2, type_repr, value_repr);

  PyObject* fmt = PyString_FromString("NA(%s, %s)");
  PyObject* ret = PyString_Format(fmt, repr);

  Py_DECREF(fmt);
  Py_DECREF(value_repr);
  Py_DECREF(type_repr);
  Py_DECREF(repr);

  return ret;
}

static int
NA_print(SlopNAObject *self, FILE *fp, int flags)
{
  // don't do any fancy printing or else Python will crash with a weird
  // error like:
  //   Fatal Python error: PyThreadState_Get: no current thread
	Py_BEGIN_ALLOW_THREADS
	fputs("<NA>", fp);
	Py_END_ALLOW_THREADS
	return 0;
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

  Py_INCREF(self->exc_type);
  Py_INCREF(self->exc_value);
  Py_INCREF(self->exc_traceback);

  return 0;
}

static void
NA_dealloc(SlopNAObject *self) {
  Py_XDECREF(self->exc_type);
  Py_XDECREF(self->exc_value);
  Py_XDECREF(self->exc_traceback);
}

PyObject* SlopNA_New(PyObject* exc_type, PyObject* exc_value, PyObject* exc_traceback) {
  // TODO: use a free list like intobject and friends
  SlopNAObject* self = (SlopNAObject*)PyObject_MALLOC(sizeof(SlopNAObject));
  if (self == NULL)
    return (PyObject *)PyErr_NoMemory();
	PyObject_INIT(self, &SlopNA_Type);

  self->exc_type = exc_type;
  self->exc_value = exc_value;
  self->exc_traceback = exc_traceback;

  Py_INCREF(self->exc_type);
  Py_INCREF(self->exc_value);
  Py_INCREF(self->exc_traceback);

	return (PyObject*)self;
}


/* Doc string */
PyDoc_STRVAR(NA_doc, "Special NA type for SlopPy");


static SlopNAObject* alias(SlopNAObject* self) {
  Py_INCREF(self);
  return self;
}

static PyObject* NA_unary(PyObject* self) {
  assert(SlopNA_CheckExact(self));
  return (PyObject*)alias((SlopNAObject*)self);
}

static PyObject* NA_GetAttr(PyObject* self, PyObject* name) {
  // TODO: create a derived object and link it back to self to track 'lineage'
  return NA_unary(self);
}

static PyObject* NA_SetAttr(PyObject* self, PyObject* name, PyObject* value) {
  return 0; // NOP - 0 stands for no error
}

static PyObject* NA_item(SlopNAObject* self, Py_ssize_t i) {
  // TODO: create a derived object and link it back to self to track 'lineage'
  return (PyObject*)alias(self);
}

static int NA_ass_item(SlopNAObject *a, Py_ssize_t i, PyObject *v) {
  return 0; // NOP - 0 stands for no error
}


static PyObject* NA_slice(SlopNAObject* self, Py_ssize_t ilow, Py_ssize_t ihigh) {
  return (PyObject*)alias(self);
}

static Py_ssize_t NA_length(SlopNAObject* self) {
  return 1;
}

static PyObject* NA_concat(SlopNAObject *a, PyObject *bb) {
  return (PyObject*)alias(a);
}

static PyObject* NA_repeat(SlopNAObject *a, Py_ssize_t n) {
  return (PyObject*)alias(a);
}

static int NA_ass_slice(SlopNAObject *a, Py_ssize_t ilow, Py_ssize_t ihigh, PyObject *v) {
  return 0; // NOP - 0 stands for no error
}

static int NA_contains(SlopNAObject *a, PyObject *el) {
  return 0; // always return False
}

static PyObject* NA_inplace_concat(PyListObject *self, PyObject *other) {
  return (PyObject*)self;
}

static PyObject* NA_inplace_repeat(SlopNAObject *self, Py_ssize_t n) {
  return (PyObject*)self;
}


static PySequenceMethods NA_as_sequence = {
	(lenfunc)NA_length,                 /* sq_length */
	(binaryfunc)NA_concat,              /* sq_concat */
	(ssizeargfunc)NA_repeat,            /* sq_repeat */
	(ssizeargfunc)NA_item,              /* sq_item */
	(ssizessizeargfunc)NA_slice,        /* sq_slice */
	(ssizeobjargproc)NA_ass_item,       /* sq_ass_item */
	(ssizessizeobjargproc)NA_ass_slice, /* sq_ass_slice */
	(objobjproc)NA_contains,            /* sq_contains */
	(binaryfunc)NA_inplace_concat,      /* sq_inplace_concat */
	(ssizeargfunc)NA_inplace_repeat,    /* sq_inplace_repeat */
};


static PyObject* NA_subscript(SlopNAObject* self, PyObject* item) {
  return (PyObject*)alias(self);
}

static int NA_ass_subscript(SlopNAObject* self, PyObject* item, PyObject* value) {
  return 0; // NOP - 0 stands for no error
}

static PyMappingMethods NA_as_mapping = {
	(lenfunc)NA_length,
	(binaryfunc)NA_subscript,
	(objobjargproc)NA_ass_subscript,
};


static PyObject* NA_call(SlopNAObject *self, PyObject *args, PyObject *kwds) {
  return (PyObject*)alias(self);
}


/* Arithmetic methods -- so we can override unary operators */
static PyNumberMethods NA_as_number = {
  0,/* nb_add */
  0,/* nb_subtract */
  0,/* nb_multiply */
  0,/* nb_divide */
  0,/* nb_remainder */
  0,/* nb_divmod */
  0,/* nb_power */
  NA_unary,/* nb_negative */
  NA_unary,/* nb_positive */
  NA_unary,/* nb_absolute */
  0,/* nb_nonzero */
  NA_unary,/* nb_invert */
  0,/* nb_lshift */
  0,/* nb_rshift */
  0,/* nb_and */
  0,/* nb_xor */
  0,/* nb_or */
  0,/* nb_coerce */
  0,/* nb_int */
  0,/* nb_long */
  0,/* nb_float */
  0,/* nb_oct */
  0,/* nb_hex */
  0,/* nb_inplace_add */
  0,/* nb_inplace_subtract */
  0,/* nb_inplace_multiply */
  0,/* nb_inplace_divide */
  0,/* nb_inplace_remainder */
  0,/* nb_inplace_power */
  0,/* nb_inplace_lshift */
  0,/* nb_inplace_rshift */
  0,/* nb_inplace_and */
  0,/* nb_inplace_xor */
  0,/* nb_inplace_or */
  0,/* nb_floor_divide */
  0,/* nb_true_divide */
  0,/* nb_inplace_floor_divide */
  0,/* nb_inplace_true_divide */
};


PyTypeObject SlopNA_Type = {
  PyVarObject_HEAD_INIT(&PyType_Type, 0)
  "NA",
  sizeof(SlopNAObject),
  0,
  (destructor)NA_dealloc,		/* tp_dealloc */
  (printfunc)NA_print,			/* tp_print */
  (getattrfunc)NA_GetAttr,  /* tp_getattr */
  (setattrfunc)NA_SetAttr,  /* tp_setattr */
  0,					/* tp_compare */
  (reprfunc)NA_repr,  /* tp_repr */
  &NA_as_number,      /* tp_as_number */
  &NA_as_sequence,    /* tp_as_sequence */
  &NA_as_mapping,     /* tp_as_mapping */
  (hashfunc)PyObject_HashNotImplemented, /* tp_hash */
  (ternaryfunc)NA_call,					/* tp_call */
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

