# handle finally opcode properly

# note that the 'finally' clause executes BEFORE the exception is caught
# at the top-level

def foo():
  try:
    raise Exception
  finally:
    print "FINALLY"

foo()
foo()
foo()

