# we want to make sure that SlopPy catches the exception in MyParser and
# NOT in the SGMLParser standard library code (since that leads to an
# infinite loop)

import sgmllib

class MyParser(sgmllib.SGMLParser):
  "A simple parser class."
  def __init__(self, src):
    self.src = src
    sgmllib.SGMLParser.__init__(self)

  def parse(self, s):
    "Parse the given string 's'."
    self.feed(s)
    self.close()

  def start_a(self, attributes):
    for (type, val) in attributes:
      if type == 'href':
        #print val, self.src
        pass

def foo():
  contents = open('regression-tests/error.html').read()
  p = MyParser('error.html')
  p.parse(contents)

foo()

