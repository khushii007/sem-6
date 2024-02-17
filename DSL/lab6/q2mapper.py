import sys
separator = "\t"
for line in sys.stdin:
    line=line.strip().split(',') #, for excel
    if len(line)==8:
        country, conf = line[3], line[5]
    else:
        continue
    print("%s%s%s" % (country, separator, conf))