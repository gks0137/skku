nums = input().split('-')

result = sum(map(int, nums[0].split('+')))
for num in nums[1:]:
    result -= sum(map(int, num.split('+')))
print(result)