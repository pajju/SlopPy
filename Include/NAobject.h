/* 

   SlopPy: A Python interpreter that facilitates sloppy, error-tolerant
   data parsing and analysis
  
   Copyright 2010 Philip J. Guo (pg@cs.stanford.edu). All rights reserved.

   This code carries the same license as the enclosing Python
   distribution: http://www.python.org/psf/license/ 

*/

#ifndef Py_SLOP_NAOBJECT_H
#define Py_SLOP_NAOBJECT_H
#ifdef __cplusplus
extern "C" {
#endif

#include <Python.h> // TODO: why do I need to include this but intobject.h doesn't???

// 'NA' stands for 'Not Available' (i.e., missing data), inspired by NA type in R:
//   http://www.statmethods.net/input/missingdata.html

typedef struct {
  PyObject_HEAD
} SlopNAObject;


PyAPI_DATA(PyTypeObject) SlopNA_Type;
#define SlopNA_CheckExact(op) ((op)->ob_type == &SlopNA_Type)


#ifdef __cplusplus
}
#endif
#endif /* !Py_SLOP_NAOBJECT_H */

