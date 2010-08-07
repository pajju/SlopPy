/* 

   SlopPy: A Python interpreter that facilitates sloppy, error-tolerant
   data parsing and analysis
  
   Copyright 2010 Philip J. Guo (pg@cs.stanford.edu). All rights reserved.

   This code carries the same license as the enclosing Python
   distribution: http://www.python.org/psf/license/ 

*/

#include "slop.h"
#include "frameobject.h"
#include "opcode.h"

// are we currently within a 'try' block (even transitively for ANY
// function on stack?)
int transitively_within_try_block() {
  PyFrameObject* f = PyEval_GetFrame();
  while (f) {
    int i;
    for (i = 0; i < f->f_iblock; i++) {
      PyTryBlock* b = &f->f_blockstack[i];
      if (b->b_type == SETUP_FINALLY || b->b_type == SETUP_EXCEPT) {
        return 1;
      }
    }

    f = f->f_back;
  }

  return 0;
}

