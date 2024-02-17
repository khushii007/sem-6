import sys

max_cases_country = {}

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
    if country not in max_cases_country or conf > max_cases_country[country][0]:
        max_cases_country[country] = (conf, state)

for country, (max_cases, max_state) in max_cases_country.items():
    print("Max cases in %s country: %d" % (country, max_cases))
