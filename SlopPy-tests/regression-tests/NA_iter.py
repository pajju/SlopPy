# this should NOT result in an infinite loop, because iterating over an
# NA object should terminate instantly

for line in open(NON_EXISTENT_FILENAME):
  print line

