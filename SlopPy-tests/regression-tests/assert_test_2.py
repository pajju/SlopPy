# should taint both 'tokens' and 'ratio' as NA

def foo(line):
  tokens = line.split()
  ratio = float(tokens[0]) / float(tokens[1])
  assert(ratio > float(tokens[1]))
  print tokens, ratio

foo('1 2')
