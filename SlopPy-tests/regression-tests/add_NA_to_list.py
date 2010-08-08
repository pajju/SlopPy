# try to add an NA object to a list in various ways;
# all attempts should get rejected

x = 1 / 0
assert type(x) is NA

l = []
l.append(x)
assert len(l) == 0
l.insert(0, x)
assert len(l) == 0
l.extend([x])
assert len(l) == 0
l += [x]
assert len(l) == 0

l2 = ['dummy', 'dummy2']
l2[0] = x
assert l2 == ['dummy', 'dummy2']
l2[0:1] = x
assert l2 == ['dummy', 'dummy2']

# list constructor should ignore all instances of x
assert [x] == []
assert [x,x] == []
assert [x,x,x] == []
assert [1,2,x,3,4] == [1,2,3,4]
assert [1,2,x,3,4,x] == [1,2,3,4]
assert [x,1,2,x,3,4,x] == [1,2,3,4]
assert [x,x,x,x,x,1,x] == [1]

