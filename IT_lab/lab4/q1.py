class subsetGen:
    
    def gen(self,curr_subset,remaining_nums):
        self.subsets.append(curr_subset[:])
        for i in range(len(remaining_nums)):
            curr_subset.append(remaining_nums[i])
            self.gen(curr_subset,remaining_nums[i+1:])
            curr_subset.pop()
            
    def gen_subsets(self,nums): 
        self.subsets=[] #creating an empty subset
        self.gen([],nums)   #send an empty subset to the function which will return subsets
        return self.subsets
    
nums = [4,5,6]
result = subsetGen().gen_subsets(nums)
print(result)