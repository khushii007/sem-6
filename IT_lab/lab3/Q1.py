n1 = float(input("Enter 1st number: "))
n2 = float(input("Enter 2nd s=number: "))
op = input("Enter the operator (+,-,*,/): ")
if op == '+':
	result = n1+n2
elif op == '-':
	result = n1-n2
elif op == '*':
	result = n1*n2
elif op == '/':
	result = n1/n2
else:
	print("Invalid operator")
print(f"{n1} {op} {n2} = {result}")