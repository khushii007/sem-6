list=[]
n=int(input('Enter number of elements: '))
for i in range (0,n):
    ele = int(input())
    if ele<0:
        list.append(ele)
print(list)