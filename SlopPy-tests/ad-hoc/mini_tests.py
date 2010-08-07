x = 1 / 0
assert type(x) == NA
x = undefined_name
assert type(x) == NA
x = 5 + 'foo'
assert type(x) == NA
x = 5[5]
assert type(x) == NA
(x, y, z) = "hello,world".split(',')
assert type(x) == NA
assert type(y) == NA
assert type(z) == NA
x = 5()
assert type(x) == NA

