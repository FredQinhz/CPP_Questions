#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> res;
        int left = 0;
        int right = numbers.size() - 1;
        while(left <= right){
            int tmp = numbers[left] + numbers[right];
            if(tmp < target){
                left++;
            }else if(tmp > target){
                right--;
            }else{
                break;
            }
        }
        res.emplace_back(left + 1);
        res.emplace_back(right + 1);
        return res;
    }
};

int main(){
    Solution s;
    vector<int> res;
    vector<int> numbers{2,7,11,15};
    int target = 9;
    res = s.twoSum(numbers, target);

}