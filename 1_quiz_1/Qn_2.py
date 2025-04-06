#Rotating an Array

def rotate(nums, k):
    n = len(nums)
    k = k % n  # Normalize k to be within the bounds of the array length
    
    # Reverse the entire array
    nums.reverse()
    
    # Reverse the first k elements
    nums[:k] = reversed(nums[:k])
    
    # Reverse the remaining elements
    nums[k:] = reversed(nums[k:])