list=[]
neg_count=0
pos_count =0
n=int(input('Enter number of elements: '))
for i in range (0,n):
    ele = int(input())
    list.append(ele)
print(list)
for i in list:
    if i<0:
        neg_count = neg_count+1
    elif i>0:
        pos_count = pos_count+1
print('Positive count: ', pos_count)
print('Negative count: ', neg_count)