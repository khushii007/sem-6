import pandas as pd
student_data = {
    'Name':['Alice', 'Bob'],
    'Height':[160,180],
    'Qualification':['Master\'s', 'Bachelor\'s']
}
df = pd.DataFrame(student_data)
address_list = ['Miami', 'LA']
df['Address'] = address_list
print(df)