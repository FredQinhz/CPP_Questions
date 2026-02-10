#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
 
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end(), less<int>());
        int n = nums.size();

        // 枚举第一个数
        for(int first = 0; first < n; first++){
            if(nums[first] > 0) 
                return res;
            // 需要和上一个不同【相当于保证第一层不会重复】
            if(first > 0 && nums[first] == nums[first - 1])
                continue;
            
            // c 对应的指针初始指向数组的最右端
            int third = n - 1;

            // 枚举第二个数
            for(int second = first + 1; second < n; second++){
                // 需要和上一个不同【相当于保证第二层不会重复】
                if(second > first + 1 && nums[second] == nums[second - 1])
                    continue;
                
                while(second < third && (nums[first] + nums[second] + nums[third] > 0)){
                    third--;
                }
                // 如果指针重合，那么这种情况不存在，结束这个循环
                if(second == third){
                    break;
                }
                if(nums[first] + nums[second] + nums[third] == 0){
                    res.emplace_back(vector<int>{nums[first], nums[second], nums[third]});
                }
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    vector<int> nums{1,1,-2};
    vector<vector<int>> res;
    res = s.threeSum(nums);
}