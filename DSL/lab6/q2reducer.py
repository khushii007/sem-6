#finding sum of all confirmed cases for each country
#displaying the country with max cases
import sys
currCountry = None
country = None
maxCountry = None
max = 0
cases = 0
for line in sys.stdin:
    line=line.strip().split('\t')
    if len(line)==2:
        country, conf = line
    else:
        continue
    try:
        conf = int(conf)
    except ValueError:
        continue
    if currCountry == country:
        cases+=conf
    else:
        if currCountry:
            print("%s - %d" % (currCountry, cases))
            if cases>max:
                max = cases
                maxCountry = currCountry
        currCountry=country
        cases=conf
if currCountry:
    print("%s - %d" % (currCountry, cases))
    if cases > max:
        max = cases
        maxCountry = currCountry
print("Max cases = %d in %s" % (max, maxCountry))