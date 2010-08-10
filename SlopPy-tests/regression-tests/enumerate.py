def foo():
  '''Disassembly of foo:
  2           0 SETUP_LOOP              61 (to 64)
              3 LOAD_GLOBAL              0 (enumerate)
              6 LOAD_CONST               1 ('a')
              9 LOAD_CONST               2 ('b')
             12 LOAD_CONST               3 ('c')
             15 LOAD_CONST               4 ('d')
             18 BUILD_LIST               4
             21 CALL_FUNCTION            1
             24 GET_ITER            
        >>   25 FOR_ITER                35 (to 63)
             28 UNPACK_SEQUENCE          2
             31 STORE_FAST               0 (i)
             34 STORE_FAST               1 (line)

  3          37 LOAD_FAST                1 (line)
             40 LOAD_CONST               1 ('a')
             43 COMPARE_OP               2 (==)
             46 JUMP_IF_TRUE            10 (to 59)
             49 POP_TOP             
             50 LOAD_GLOBAL              1 (AssertionError)
             53 LOAD_FAST                1 (line)
             56 RAISE_VARARGS            2
        >>   59 POP_TOP             
             60 JUMP_ABSOLUTE           25
        >>   63 POP_BLOCK           
        >>   64 LOAD_CONST               0 (None)
             67 RETURN_VALUE
  '''
  for (i, line) in enumerate(['a', 'b', 'c', 'd']):
    assert line == 'a', line

foo()
