# don't resort to NA when you're within a try block

try:
  x = 1 / 0
except:
  x = "no harm done"

assert x == "no harm done"
