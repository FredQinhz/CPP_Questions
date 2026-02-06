#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/**
 * 《除法求值》
 * 给你一个由变量对组成的方程式列表 equations 和一个实数值列表 values ，
 * 其中 equations[i] = [Ai, Bi] 和 values[i] 共同表示方程 Ai / Bi = values[i] 。
 * 每个 Ai 或 Bi 是一个表示单个变量的字符串。  
 * 另有一些以数组 queries 给出的查询，其中 queries[j] = [Cj, Dj] 表示第 j 个查询问的是 Cj / Dj = ? 。
 * 返回 所有查询的结果 。如果存在某个无法确定的答案，则返回 -1.0 。
 * 注意：输入总是有效的。你可以假设除法运算中不会出现除以 0 的情况，且不存在任何矛盾的结果。
 */

class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        // 构建有向图
        unordered_map<string, vector<pair<string, double>>> graph;

        for (int i = 0; i < equations.size(); ++i) {
            const string& A = equations[i][0];
            const string& B = equations[i][1];
            double value = values[i];
            graph[A].emplace_back(B, value);
            graph[B].emplace_back(A, 1.0 / value);
        }
        
        vector<double> results;
        for (const auto& query : queries) {
            const string& C = query[0];
            const string& D = query[1];
            if (graph.find(C) == graph.end() || graph.find(D) == graph.end()) {
                results.push_back(-1.0);
            } else if (C == D) {
                results.push_back(1.0);
            } else {
                unordered_map<string, bool> visited;
                double result = dfs(graph, C, D, 1.0, visited);
                results.push_back(result == 0.0 ? -1.0 : result);
            }
        }
        return results;
    }

private:
    double dfs(const unordered_map<string, vector<pair<string, double>>>& graph, const string& current, const string& target, double accumulatedProduct, unordered_map<string, bool>& visited) {
        if (current == target) {
            return accumulatedProduct;
        }
        visited[current] = true;

        for (const auto& neighbor : graph.at(current)) {
            const string& nextNode = neighbor.first;
            double value = neighbor.second;
            if (!visited[nextNode]) {
                double result = dfs(graph, nextNode, target, accumulatedProduct * value, visited);
                if (result != 0.0) {
                    return result;
                }
            }
        }
        return 0.0;
    }
};

int main() {
    Solution sol;
    vector<vector<string>> equations = {{"a", "b"}, {"b", "c"}};
    vector<double> values = {2.0, 3.0};
    vector<vector<string>> queries = {{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}};
    vector<double> results = sol.calcEquation(equations, values, queries);
    
    for(double res : results) {
        cout << res << " ";
    }
    cout << endl;

    return 0;
}