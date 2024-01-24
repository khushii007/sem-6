def binary_search_recursive(list,target,low,high):
	if low<=high:
		mid=(low+high)//2 #to get integer result, we use //
		if list[mid]==target:
			return mid
		elif list[mid]>target:
			return binary_search_recursive(list,target,low,mid-1)
		else:
			return binary_search_recursive(list,target,mid+1,high)
	else:
		return -1

list=[]
n = int(input("Enter number of elements: "))
for i in range(0,n):
	ele=int(input())
	list.append(ele)
target = int(input("Enter element to find: "))
result = binary_search_recursive(list,target,0,len(list)-1)
if result != -1:
    print(f"Element {target} is present at index {result}.")
else:
    print(f"Element {target} is not present in the array.")