# do a bunch of compare operations on an NA object, should ALL return <NA>

x = 1 / 0
assert type(x) is NA

assert type(x < 5) is NA
assert type(5 < x) is NA
assert type(x <= 5) is NA
assert type(5 <= x) is NA
assert type(x > 5) is NA
assert type(5 > x) is NA
assert type(x >= 5) is NA
assert type(5 >= x) is NA
assert type(x == 5) is NA
assert type(5 == x) is NA
assert type(x != 5) is NA
assert type(5 != x) is NA
assert type(5 in x) is NA
assert type(x in [1, 2, 3]) is NA
