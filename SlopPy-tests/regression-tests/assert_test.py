# should ONLY taint 'ratio' as NA but leave other local vars alone
def foo(line):
  tokens = line.split()
  ratio = float(tokens[0]) / float(tokens[1])
  assert(ratio < 1.0)
  print tokens, ratio

foo('1 2')
foo('4 2')
foo('1 3')
foo('8 2')
foo('1 4')
