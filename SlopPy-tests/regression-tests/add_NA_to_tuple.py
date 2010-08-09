# try to add an NA object to a tuple in various ways;
# all attempts should get rejected

x = 1 / 0
assert type(x) is NA

# tuple constructor should ignore all instances of x
assert (x,) == ()
assert (x,x) == ()
assert (x,x,x) == ()
assert (1,2,x,3,4) == (1,2,3,4)
assert (1,2,x,3,4,x) == (1,2,3,4)
assert (x,1,2,x,3,4,x) == (1,2,3,4)
assert (x,x,x,x,x,1,x) == (1,)

