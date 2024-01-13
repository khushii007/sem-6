list=[]
n=int(input('Enter number of elements: '))
for i in range (0,n):
    ele = int(input())
    list.append(ele)
print('List before: ', list)

new_list=[]
for ele in list:
    if ele%2!=0:
        new_list.append(ele)
list = new_list  
print('List after: ', list)