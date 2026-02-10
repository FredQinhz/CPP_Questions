#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main(){
    unordered_map<int, char> mp;
    for(int i = 1; i <= 26; i++){
        mp[i] = 'a' + i - 1;
    }

    string r_str = "zyx";
    string str;

    for(int i = 0; i < r_str.size(); i++){
        str += mp[26 - (r_str[i] - 'a')];
    }
    cout << str;
}