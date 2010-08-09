# do a bunch of unary operations on an NA object

x = 1 / 0
assert type(x) is NA

assert -x is x
assert +x is x
assert abs(x) is x
assert ~x is x

