import sys
for line in sys.stdin:
    line = line.strip().split(',')
    if len(line)==8:
        state, country, conf = line[2], line[3], line[5]
    else:
        continue
    print("%s \t %s \t %s" % (country,state, conf)) #repr function returns string representation