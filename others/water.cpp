#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0;
        int left = 0, right = height.size() - 1;
        int leftMax = 0, rightMax = 0;
        while (left < right) {
            leftMax = max(leftMax, height[left]);
            rightMax = max(rightMax, height[right]);
            if (height[left] < height[right]) {
                ans += leftMax - height[left];
                ++left;
            } else {
                ans += rightMax - height[right];
                --right;
            }
        }
        return ans;
    }
};


// class Solution{
// public:
//     int trap(vector<int> &height){
//         int res = 0;
//         int n = height.size();
//         int waterFlag = false; // 当前状态是否可以装水【即是否在桶内】
//         int maxHigh = 0;   // 当前左边最高柱子
//         int waterHigh = 0; // 当前最高水位

//         vector<int> rightMax(n, 0);
//         for (int i = n - 2; i >= 0; i--) // 记录右边最高的柱子，限制最高水位 waterHigh
//             rightMax[i] = max(rightMax[i + 1], height[i + 1]);
        
//         for (int i = 0; i < n; i++){
//             if (height[i] > maxHigh) // 更新左边最高柱子
//                 maxHigh = height[i];
            
//             waterHigh = min(maxHigh, rightMax[i]); // 根据左边高度和右边高度来限制水位

//             if (waterHigh > height[i])
//                 res += waterHigh - height[i]; 
//         }
//         return res;
//     }
// };

int main(){
    Solution s;
    // 0,1,0,2,1,0,1,3,2,1,2,1
    // 4,2,0,3,2,5
    vector<int> height{0,1,0,2,1,0,1,3,2,1,2,1};
    cout << s.trap(height);
}