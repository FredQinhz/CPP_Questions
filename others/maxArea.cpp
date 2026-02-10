#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int max = 0;
        int left = 0;
        int right = height.size() - 1;
        while(left < right){
            int area = calArea(left, right, height);
            max = std::max(max, area);
            if(height[left] <= height[right]){ // 移动低的一边，这样面积才可能变大；移动高的一边的面积一定会变小。
                left++;
            }else{
                right--;
            }
        }
        return max;
    }
    int calArea(int idx1, int idx2, vector<int>& height){
        return (idx2 - idx1) * std::min(height[idx1], height[idx2]);
    }
};

int main(){
    Solution s;
    vector<int> height{1,2,4,3};
    int res = s.maxArea(height);
    cout << res << endl;
}