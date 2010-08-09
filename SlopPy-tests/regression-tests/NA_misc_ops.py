# try out misc. ops on an NA object

x = 1 / 0
assert type(x) is NA

assert x.attr is x
x.attr2 = 5
assert x[42] is x
x[42] = 5
assert x[1:5] is x
x[1:5] = 5
assert len(x) == 1
assert not 'foo' in x
assert x() is x
assert x(1,2,3) is x

