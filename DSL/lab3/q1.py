import numpy as np 
n = int(input("Enter number: "))
print("Factors: ")
for i in range(1,n):
    if n%i==0:
        print(i)