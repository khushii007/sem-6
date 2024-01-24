import pandas as pd
student_data = {
    'Name':['Kiara', 'Tina'],
    'Height': [157, 162],
    'Qualification': ['Fashion Desigining', 'Medical']
}
df = pd.DataFrame(student_data)
address_list = ['Paris', 'Manila']
df.insert(1, 'Address', address_list)
print(df)