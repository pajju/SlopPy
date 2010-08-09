# try to add an NA object to a set in various ways;
# all attempts should get rejected

x = 1 / 0
assert type(x) is NA

assert set([x]) == set()
assert set([x,x]) == set()
assert set([x,x,x]) == set()
assert set([1,2,x,3,4]) == set([1,2,3,4])
assert set([1,2,x,3,4,x]) == set([1,2,3,4])
assert set([x,1,2,x,3,4,x]) == set([1,2,3,4])
assert set([x,x,x,x,x,1,x]) == set([1])

s = set()
assert len(s) == 0
s.add(x)
assert len(s) == 0
s.update(set([x]))
assert len(s) == 0

