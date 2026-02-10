#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumOperationsToMakeKPeriodic(string word, int k) {
        unordered_map<string, int> map;
        int n = word.size();
        for(int i = 0; i < n; i += k)
            map[word.substr(i, k)]++;

        int max = 0;
        for(auto it : map){
            if(it.second > max)
                max = it.second;
        }

        return n/k - max;
    }
};

int main(){
    Solution s;
    int res = s.minimumOperationsToMakeKPeriodic("leetcodeleet", 4);
    cout << res << endl;
}