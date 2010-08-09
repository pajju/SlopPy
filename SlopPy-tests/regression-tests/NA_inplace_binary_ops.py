# do a bunch of in-place binary operations on an NA object

x = 1 / 0
assert type(x) is NA

x += 5
x -= 5
x *= 5
x /= 5
x //= 5
x %= 5
x <<= 5
x >>= 5
x &= 5
x ^= 5
x |= 5


y = 10
y += x
assert y is x
y = 10
y -= x
assert y is x
y = 10
y *= x
assert y is x
y = 10
y /= x
assert y is x
y = 10
y //= x
assert y is x
y = 10
y %= x
assert y is x
y = 10
y <<= x
assert y is x
y = 10
y >>= x
assert y is x
y = 10
y &= x
assert y is x
y = 10
y ^= x
assert y is x
y = 10
y |= x
assert y is x

