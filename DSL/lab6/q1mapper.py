import sys

separator = '-'
for line in sys.stdin:
    line=line.strip()
    words=line.split('\t')  #\t for txt files and , for csv files
    for word in words:
        print('%s%s%s' % (word,separator,1))