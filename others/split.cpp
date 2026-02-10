#include <iostream>
#include <vector>

using namespace std;

vector<string> Split1(const string &s, const string &seperator) {
    vector<string> ans;
    string token, str = s;
    size_t pos = 0;
    while((pos = str.find(seperator)) != string::npos) {
  	    token = str.substr(0, pos);
        if(token != "")
  	        ans.push_back(token);
  	    str.erase(0, pos + seperator.length());
    }
    if(str != "")
        ans.push_back(str);
    return ans;
}

vector<string> Split(const string &s, const char &seperator) {
    vector<string> ans;
    string tmp = "";
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != seperator) {
            tmp += s[i];
        }else {
            if(tmp != ""){
                ans.push_back(tmp);
                tmp = "";
            }  
        }
    }
    if(tmp != "")
        ans.push_back(tmp);
    return ans;
}

int main(){
    string str1("green apple");
    string str2("red apple");

    // str1和str2比较：参数形式1
    int res = str1.compare(str2);
    cout << res << endl;

    string str = "the sky is blue";
    vector<string> ans;
     //ans = Split(str, ' ');
    ans = Split1(str, " ");
    
    string resStr;
    int n = ans.size();
    for(int i = n - 1; i >= 0; i--){
        if(i != 0)
            resStr += ans[i] + " ";
        else 
            resStr += ans[i];
    }
   
    
    cout << resStr << endl;
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << endl;
    }
}