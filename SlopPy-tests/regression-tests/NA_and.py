''' 
  (NA and False) = False 
  (False and NA) = False

  Sources: http://databases.about.com/cs/sql/a/aa042803a.htm
           http://www.sqlite.org/nulls.html
''' 

x = 1 / 0
assert type(x) is NA
assert (x and False) is False
assert (False and x) is False

assert (x and False and x) is False
assert (x and x and False) is False
assert (False and x and x) is False

