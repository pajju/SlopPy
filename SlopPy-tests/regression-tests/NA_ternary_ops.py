# do a bunch of ternary operations on an NA object

x = 1 / 0
assert type(x) is NA

assert type(pow(x, 2)) is NA
assert type(pow(2, x)) is NA
assert type(x ** 2) is NA
assert type(2 ** x) is NA

