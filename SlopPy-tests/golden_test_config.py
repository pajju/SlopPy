PROGRAM = '~/SlopPy/python.exe'
TEST_DIR = 'regression-tests/'
INPUT_FILE_EXTENSION = '.py'
OUTPUT_FILE = 'slop_verbose.log'

import re

# output is in the form of a list of strings
def filter_output(str_lst):
  # filter out all memory addresses
  return [re.sub(' 0x.+?>', ' 0xADDR>', e) for e in str_lst]

