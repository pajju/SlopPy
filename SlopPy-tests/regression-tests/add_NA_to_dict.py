# try to add an NA object to a dict in various ways;
# all attempts should get rejected

x = 1 / 0
assert type(x) is NA

# dict constructor should ignore all instances of x in key or value
assert {x:1} == {}
assert {1:x} == {}
assert {x:1, 'hello' : 'world'} == {'hello' : 'world'}
assert {1:x, 'hello' : 'world'} == {'hello' : 'world'}

d = {}
d['bob'] = x
assert len(d) == 0
d[x] = 'joe'
assert len(d) == 0
d.update({x:1})
assert len(d) == 0
y = d.setdefault('unknown', x)
assert type(y) is NA
assert len(d) == 0

assert dict(key1=x) == {}
assert dict(key1=x, key2=x) == {}
assert dict(key1=x, key2=x, hello='world') == {'hello' : 'world'}
assert dict(key1=x, key2=x, hello='world', blah=5) == {'hello' : 'world', 'blah' : 5}

