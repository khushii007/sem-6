class powCalc:
    def calculate(self,num,power):
        if num==0:
            return 1
        result=1
        for i in range (0,power):
            result*=num
        return result

num = int(input("Enter number: "))
power = int(input("Enter its power: "))
result = powCalc().calculate(num,power)
print(result)