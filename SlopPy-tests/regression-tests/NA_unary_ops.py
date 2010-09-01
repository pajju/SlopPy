# do a bunch of unary operations on an NA object

x = 1 / 0
assert type(x) is NA

assert type(-x) is NA
assert type(+x) is NA
assert type(abs(x)) is NA
assert type(~x) is NA

