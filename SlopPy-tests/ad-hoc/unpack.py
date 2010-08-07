# this should NOT crash!

'''
Disassembly of foo:
  3           0 LOAD_CONST               1 ('hello,world')
              3 LOAD_ATTR                0 (split)
              6 LOAD_CONST               2 (',')
              9 CALL_FUNCTION            1
             12 UNPACK_SEQUENCE          3
             15 STORE_FAST               0 (x)
             18 STORE_FAST               1 (y)
             21 STORE_FAST               2 (z)
             24 LOAD_CONST               0 (None)
             27 RETURN_VALUE
'''
def foo():
  (x, y, z) = "hello,world".split(',')

foo()
