# make sure SlopPy works with list comprehensions

lst = ['1', '2', 'baaad', '3', '4']

xs = [int(line) for line in lst]

y = [20*x for x in xs]
assert y == [20, 40, 60, 80]

