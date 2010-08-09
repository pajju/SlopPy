# do a bunch of ternary operations on an NA object

x = 1 / 0
assert type(x) is NA

assert pow(x, 2) is x
assert pow(2, x) is x
assert x ** 2 is x
assert 2 ** x is x

