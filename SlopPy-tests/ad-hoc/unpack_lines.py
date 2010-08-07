s = '''johnny, smith, 640
jane, turner, 932
jimmy, brad, jones, 150
barbara, milton, 183
jenny, cox, 9432'''

for line in s.split('\n'):
  (first_name, last_name, id) = line.split(',')
  first_name = first_name.strip()
  last_name = last_name.strip()
  id = int(id)
  print id, first_name, last_name

