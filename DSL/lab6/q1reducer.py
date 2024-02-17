import sys
#from operator import itemgetter

separator = '-'
currWord = None
word = None
currCount = 0

for line in sys.stdin:
    line=line.strip()
    parts=line.split('%s' % (separator))
    if len(parts)==2:
        word, count = parts
    else:
        continue
    try:
        count=int(count)
    except ValueError:
        continue
    if currWord==word:
        currCount+=count
    else:
        if currWord:
            print("%s%s%d" % (currWord, separator, currCount))
        currWord = word
        currCount = count
if currWord:
    print("%s%s%d" % (currWord, separator, currCount))