# do a bunch of binary operations on an NA object

x = 1 / 0
assert type(x) is NA

assert type(x + 5) is NA
assert type(5 + x) is NA

assert type(x - 5) is NA
assert type(5 - x) is NA

assert type(x * 5) is NA
assert type(5 * x) is NA

assert type(x / 5) is NA
assert type(5 / x) is NA

assert type(x // 5) is NA
assert type(5 // x) is NA

assert type(x % 5) is NA
assert type(5 % x) is NA

assert type(x << 5) is NA
assert type(5 << x) is NA

assert type(x >> 5) is NA
assert type(5 >> x) is NA

assert type(x & 5) is NA
assert type(5 & x) is NA

assert type(x ^ 5) is NA
assert type(5 ^ x) is NA

assert type(x | 5) is NA
assert type(5 | x) is NA

