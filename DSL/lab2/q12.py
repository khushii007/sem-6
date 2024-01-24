list=[]
i=0
n = int(input('Enter number of elements: '))
while i<n:
    ele = int(input())
    i=i+1
    if ele<0:
        list.append(ele)
print(list)