# do a bunch of compare operations on an NA object

x = 1 / 0
assert type(x) is NA

assert not (x < 5)
assert not (x <= 5)
assert not (x > 5)
assert not (x >= 5)
assert not (x == 5)
assert not (x != 5)
