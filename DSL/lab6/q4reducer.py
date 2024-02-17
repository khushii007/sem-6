import sys

nums = sys.stdin.read().strip().split()
print(nums)
oddCount = evenCount = 0
for num in nums:
    if int(num)%2 == 0:
        evenCount+=1
    else:
        oddCount+=1
print("Odd count: ", oddCount)
print("Even count: ", evenCount)