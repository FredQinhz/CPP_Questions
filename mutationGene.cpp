#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        if(find(bank.begin(), bank.end(), endGene) == bank.end()) // 目标基因不在变异基因库里
            return -1;

        unordered_map<string, int> mutTimes; // map<变异基因, 变异次数>
        for(string str: bank){
            mutTimes.emplace(str, INT_MAX);
        }
        
        // 建立一个邻接表，用于优化枚举时间
        unordered_map<string, vector<string>> edges;
        for(int n = bank.size(), i = 0; i <= n; i++){
            string str;
            if(i != n)
                str = bank[i];
            else 
                str = startGene; // 不要忘记初始边

            vector<string> list;
            for(string edge: bank){
                if(edge != str){
                    int diff = 0;
                    for(int i = 0; i < str.size(); i++)
                        if(str[i] != edge[i])
                            diff++;
               
                    if(diff == 1)
                        list.emplace_back(edge);
                }
            } 
            edges.emplace(str, list);
        }
        
        
        queue<string> q;
        q.emplace(startGene);
        
        while(!q.empty()){
            string gene = q.front();
            q.pop();
            int steps = 0; // 当前基因的变异次数

            if(gene == startGene){ // 起始基因
                if(mutTimes.find(gene) != mutTimes.end()) // bank中找得到，原始基因无需经过变异就是一个变异基因，直接将置为0
                    mutTimes[gene] = 0;
            }else{ // 变异基因， 获取上一次变异次数
                steps = mutTimes[gene];
            }

            // 枚举所有可能变异情况
            for(string edge: edges[gene]){
                if(mutTimes[edge] >= (steps + 1)){ // 只有一处不同，并且变异次数比原来更少，允许变异
                    mutTimes[edge] = steps + 1; // 更新变异次数
                    q.emplace(edge);
                }
            }
        }
        return mutTimes[endGene] == INT_MAX ? -1 : mutTimes[endGene];
    }
};

int main(){
    Solution s;
    string startGene = "hit";
    string endGene = "cog";
    vector<string> bank {"hot","dot","dog","lot","log","cog"};
    cout << s.minMutation(startGene, endGene, bank);
}
