# don't resort to NA when you're (transitively) within a try block
def foo():
  try:
    bar()
  except:
    return "no harm done"

def bar():
  baz()

def baz():
  x = 1 / 0

assert foo() == "no harm done"
