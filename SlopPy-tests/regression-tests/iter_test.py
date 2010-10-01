# iterators should NOT yield NA objects

x = 1 / 0
assert type(x) is NA

# list
y = [1, 2, x, 3, 4]
z = []
for e in y:
  z.append(e)

assert z == [1, 2, 3, 4]

# tuple:
y = (1, 2, x, 3, 4, x)
z = []
for e in y:
  z.append(e)

assert z == [1, 2, 3, 4]

# set:
y = set()
y.add(1)
y.add(2)
y.add(x)
y.add(3)
y.add(4)

z = set()
for e in y:
  z.add(e)

assert z == set([1, 2, 3, 4])

