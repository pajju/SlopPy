/* 

   SlopPy: A Python interpreter that facilitates sloppy, error-tolerant
   data parsing and analysis
  
   Copyright 2010 Philip J. Guo (pg@cs.stanford.edu). All rights reserved.

   This code carries the same license as the enclosing Python
   distribution: http://www.python.org/psf/license/ 

*/

#ifndef Py_SLOP_H
#define Py_SLOP_H
#ifdef __cplusplus
extern "C" {
#endif

#include "Python.h"
#define PYPRINT(obj) do {PyObject_Print(obj, stdout, 0); printf("\n");} while(0)

// are we currently within a 'try' block (even transitively for ANY
// function on stack?)
int transitively_within_try_block(void);


#define DO_NOTHING             100
#define DO_PUSH_1              101
#define DO_SET_TOP_1           102
#define NEED_SPECIAL_HANDLING  103
int get_NA_stack_action(int opcode);

int pg_activated;

void pg_initialize(void);
void pg_finalize(void);

#define PG_LOG(str) fprintf(verbose_log_file, "%s\n", str)
#define PG_LOG_PRINTF(...) fprintf (verbose_log_file, __VA_ARGS__)

// initialize in pg_initialize(), destroy in pg_finalize()
FILE* verbose_log_file;

void log_NA_event(const char* event_name);


#ifdef __cplusplus
}
#endif
#endif /* !Py_SLOP_H */

