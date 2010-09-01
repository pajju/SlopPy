# try out misc. ops on an NA object

x = 1 / 0
assert type(x) is NA

assert type(x.attr) is NA
x.attr2 = 5
assert type(x[42]) is NA
x[42] = 5
assert type(x[1:5]) is NA
x[1:5] = 5
assert len(x) == 1
assert type('foo' in x) is NA
assert type(x()) is NA
assert type(x(1,2,3)) is NA

