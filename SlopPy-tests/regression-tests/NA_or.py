''' 
  (NA or True) = True
  (True or NA) = True

  Sources: http://databases.about.com/cs/sql/a/aa042803a.htm
           http://www.sqlite.org/nulls.html
''' 

x = 1 / 0
assert type(x) is NA
assert (x or True) is True
assert (True or x) is True

assert (x or True or x) is True
assert (x or x or True) is True
assert (True or x or x) is True

