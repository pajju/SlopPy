# have generators NOT yield 'NA' values, so as not to corrupt results

import StringIO

lst = ['1', '2', 'bad', '3', 'bad2', 'bad3', 'bad4', '4']

def foo(l):
  for x in l:
    y = 20 * int(x)
    yield y

s = StringIO.StringIO()
for e in foo(lst):
  print >> s, e

assert s.getvalue() == '20\n40\n60\n80\n'

