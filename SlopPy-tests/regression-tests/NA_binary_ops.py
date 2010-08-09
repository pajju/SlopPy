# do a bunch of binary operations on an NA object

x = 1 / 0
assert type(x) is NA

assert x + 5 is x
assert 5 + x is x

assert x - 5 is x
assert 5 - x is x

assert x * 5 is x
assert 5 * x is x

assert x / 5 is x
assert 5 / x is x

assert x // 5 is x
assert 5 // x is x

assert x % 5 is x
assert 5 % x is x

assert x << 5 is x
assert 5 << x is x

assert x >> 5 is x
assert 5 >> x is x

assert x & 5 is x
assert 5 & x is x

assert x ^ 5 is x
assert 5 ^ x is x

assert x | 5 is x
assert 5 | x is x

