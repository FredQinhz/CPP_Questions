#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> res;
        int n = words.size();
        string line;
        int line_l = 0;
        int idx_s = 0;
        for(int i = 0; i < n; i++){
            string tmp_s = words[i];
            int tmp_l = tmp_s.size();
            if((line_l + tmp_l) > maxWidth){
                line = processLine(idx_s, i, words, maxWidth);
                res.emplace_back(line);
                
                idx_s = i;
                line = tmp_s; // 删除并替换
                if(i != n - 1)
                    line += " ";
                line_l = line.size();
            }else if((line_l + tmp_l) == maxWidth){
                line += tmp_s;
                res.emplace_back(line);

                idx_s = i + 1;
                line = "";
                line_l = 0;
            }
            else{
                if(i != n - 1){
                    line += tmp_s + " ";
                    line_l = line.size();
                }else{
                    line += tmp_s;
                    line_l = line.size();
                }
            }
        }
        if(line_l != 0)
            res.emplace_back(line.append(maxWidth - line_l, ' '));
        return res;
    }

    string processLine(int idx_s, int idx_e, vector<string>& words, int maxWidth){
        int wordsCnt = idx_e - idx_s;
        int len = 0;
        for(int i = idx_s; i < idx_e; i++)
            len += words[i].size();

        int spaceCnt = maxWidth - len;
            if(wordsCnt == 1)
                return words[idx_s].append(spaceCnt, ' ');

        
        int spaceAvg = spaceCnt / (wordsCnt - 1);
        int spaceLeft = spaceCnt % (wordsCnt - 1);

        string res;
        for(int i = idx_s; i < idx_e; i++){
            if(i != idx_e - 1){
                res += words[i];
                res.append(spaceAvg, ' ');
                if(spaceLeft-- > 0){
                    res.append(" ");
                }
            }else{
                res += words[i];
            }
        }

        return res;
    }
};

int main(){
    // "This", "is", "an", "example", "of", "text", "justification."
    // "What","must","be","acknowledgment","shall","be"
    // "Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"
    vector<string> words{ "Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do" };
    vector<string> vec;
    Solution s;
    vec = s.fullJustify(words, 20);
    for(int i = 0; i < vec.size(); i++)
        cout << vec[i] << endl;
}