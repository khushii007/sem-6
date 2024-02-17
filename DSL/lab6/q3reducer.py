import sys

currCountry = country = maxState = None
max = 0

for line in sys.stdin:
    line = line.strip().split('\t')

    if len(line) == 3:
        country,state, conf = line
    else:
        continue

    try:
        conf = int(conf)
    except ValueError:
        continue

    if currCountry == country:
        if conf>max:
            max = conf
            maxState = state
    else:
        if currCountry:
            print("Max cases in %s country : %d" % (currCountry, max))
        currCountry = country
        max = conf
        maxState = state

if currCountry:
    print("Max cases in %s country : %d" % (currCountry, max))