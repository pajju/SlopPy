# have generators NOT yield 'NA' values, so as not to corrupt results
lst = ['1', '2', 'bad', '3', 'bad2', 'bad3', 'bad4', '4']

y = [20*int(x) for x in lst]
yg = (20*int(x) for x in lst)

sum_y = 0
for e in y:
  sum_y += e

assert sum_y == 200
assert sum(yg) == 200
