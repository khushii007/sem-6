class findPair:
    def find(self, nums, target):
        for i in range(0,len(nums)-1):
            for j in range(i+1,len(nums)):
                if nums[i]+nums[j] == target:
                    return i,j
    
nums = [10,20,10,40,50,60,70]
target = 130
result = findPair().find(nums,target)
print(result)