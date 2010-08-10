/* 

   SlopPy: A Python interpreter that facilitates sloppy, error-tolerant
   data parsing and analysis
  
   Copyright 2010 Philip J. Guo (pg@cs.stanford.edu). All rights reserved.

   This code carries the same license as the enclosing Python
   distribution: http://www.python.org/psf/license/ 

*/

#include "NAobject.h"
#include "slop.h"
#include "cStringIO.h"

static PyObject *
NA_repr(SlopNAObject *self)
{
  PyObject* type_repr = PyObject_Repr(self->exc_type);
  PyObject* value_repr = PyObject_Repr(self->exc_value);

  PyObject* repr = PyTuple_Pack(3, type_repr, value_repr, self->exc_traceback_str);

  PyObject* fmt = PyString_FromString("{NA %s %s\n %s}");
  PyObject* ret = PyString_Format(fmt, repr);
  Py_DECREF(fmt);

  Py_DECREF(repr);
  Py_DECREF(value_repr);
  Py_DECREF(type_repr);

  return ret;
}

static int
NA_print(SlopNAObject *self, FILE *fp, int flags)
{
  // don't try to print anything fancy or else the interpreter might
  // croak with an error like this:
  //   Fatal Python error: PyThreadState_Get: no current thread
  //
  // use str() or repr() to get more details
	Py_BEGIN_ALLOW_THREADS
	fputs("<NA>", fp);
	Py_END_ALLOW_THREADS
	return 0;
}


static void
NA_dealloc(SlopNAObject *self) {
  Py_XDECREF(self->exc_type);
  Py_XDECREF(self->exc_value);
  Py_XDECREF(self->exc_traceback_str);
  Py_XDECREF(self->next_NA);
}


PyObject* SlopNA_New(PyObject* exc_type, PyObject* exc_value, PyObject* exc_traceback) {
  assert(pg_activated);

  // TODO: use a free list like intobject and friends
  SlopNAObject* self = (SlopNAObject*)PyObject_MALLOC(sizeof(SlopNAObject));
  if (self == NULL)
    return (PyObject *)PyErr_NoMemory();
	PyObject_INIT(self, &SlopNA_Type);

  // we can directly take these 2 fields, since they're picklable
  self->exc_type = exc_type;

  // could be NULL, in which case use Py_None
  if (exc_value) {
    self->exc_value = exc_value;
  }
  else {
    self->exc_value = Py_None;
  }

  Py_INCREF(self->exc_type);
  Py_INCREF(self->exc_value);

  // unfortunately exc_traceback isn't picklable, so we'll need to
  // call PyTraceBack_Print to print the traceback into a
  // cStringIO buffer, then convert that to a string

  if (!PycStringIO) {
    PycString_IMPORT; // don't repeat imports
  }

  PyObject* buf = PycStringIO->NewOutput(128);
  PyTraceBack_Print(exc_traceback, buf);

  self->exc_traceback_str = PycStringIO->cgetvalue(buf);
  Py_DECREF(buf);

  self->next_NA = NULL;

  // log this creation event:
  PyObject* repr = NA_repr(self);
  PG_LOG(PyString_AsString(repr));
  Py_DECREF(repr);

  return (PyObject*)self;
}


/* Doc string */
PyDoc_STRVAR(NA_doc, "Special NA type for SlopPy");


static SlopNAObject* alias(SlopNAObject* self) {
  Py_INCREF(self);
  return self;
}

static PyObject* NA_unary(PyObject* self) {
  log_NA_event("NA_unary");
  assert(SlopNA_CheckExact(self));
  return (PyObject*)alias((SlopNAObject*)self);
}

static PyObject* NA_GetAttr(PyObject* self, PyObject* name) {
  log_NA_event("NA_GetAttr");
  assert(SlopNA_CheckExact(self));
  return (PyObject*)alias((SlopNAObject*)self);
}

static PyObject* NA_SetAttr(PyObject* self, PyObject* name, PyObject* value) {
  return 0; // NOP - 0 stands for no error
}

static PyObject* NA_item(SlopNAObject* self, Py_ssize_t i) {
  log_NA_event("NA_item");
  return (PyObject*)alias(self);
}

static int NA_ass_item(SlopNAObject *a, Py_ssize_t i, PyObject *v) {
  return 0; // NOP - 0 stands for no error
}


static PyObject* NA_slice(SlopNAObject* self, Py_ssize_t ilow, Py_ssize_t ihigh) {
  log_NA_event("NA_slice");
  return (PyObject*)alias(self);
}

static Py_ssize_t NA_length(SlopNAObject* self) {
  return 1;
}

static PyObject* NA_concat(SlopNAObject *a, PyObject *bb) {
  log_NA_event("NA_concat");
  return (PyObject*)alias(a);
}

static PyObject* NA_repeat(SlopNAObject *a, Py_ssize_t n) {
  log_NA_event("NA_repeat");
  return (PyObject*)alias(a);
}

static int NA_ass_slice(SlopNAObject *a, Py_ssize_t ilow, Py_ssize_t ihigh, PyObject *v) {
  return 0; // NOP - 0 stands for no error
}

static int NA_contains(SlopNAObject *a, PyObject *el) {
  return 0; // always return False
}

static PyObject* NA_inplace_concat(PyListObject *self, PyObject *other) {
  log_NA_event("NA_inplace_concat");
  return (PyObject*)self;
}

static PyObject* NA_inplace_repeat(SlopNAObject *self, Py_ssize_t n) {
  log_NA_event("NA_inplace_repeat");
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
  log_NA_event("NA_subscript");
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
  log_NA_event("NA_call");
  return (PyObject*)alias(self);
}

static long NA_hash(SlopNAObject *a) {
  return PyObject_Hash(a->exc_traceback_str);
}

static int
NA_compare(SlopNAObject *v, SlopNAObject *w)
{
  log_NA_event("NA_compare");
  return 0;
}

// all iteration attempts should IMMEDIATELY FAIL
// (to prevent infinite loops in cases like "for x in <NA>:")
static PyObject *NA_iternext(SlopNAObject *self) {
  log_NA_event("NA_iternext");
  return NULL;
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
  (cmpfunc)NA_compare,					/* tp_compare */
  (reprfunc)NA_repr,  /* tp_repr */
  &NA_as_number,      /* tp_as_number */
  &NA_as_sequence,    /* tp_as_sequence */
  &NA_as_mapping,     /* tp_as_mapping */
  (hashfunc)NA_hash, /* tp_hash */
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
  PyObject_SelfIter, /* tp_iter */
  (iternextfunc)NA_iternext, /* tp_iternext */
  0,					/* tp_methods */
  0,					/* tp_members */
  0,					/* tp_getset */
  0,          /* tp_base */
  0,					/* tp_dict */
  0,					/* tp_descr_get */
  0,					/* tp_descr_set */
  0,					/* tp_dictoffset */
  0,          /* tp_init */
  0,					/* tp_alloc */
  PyType_GenericNew,		/* tp_new */
  0,      		/* tp_free */
};

