#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/**
 * 《课程表》
 * 你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses-1 。
 * 在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们：[0,1] 。
 * 给你课程总量 numCourses 和一个先修课程列表 prerequisites ，请你判断你是否能够完成所有课程的学习？
 */

class Solution {
public:
    
/** DFS + 路径标记（检测有向环）
 * 在有向图里，用 DFS 判环的经典做法是维护两个数组：
 * visited[u]：u 是否已经被访问过（DFS 已经处理过）
 * onPath[u]：u 是否在当前 DFS 递归栈（当前路径）上
 * 判环的关键判断：
 * 当从 u 走到 v 时：
 * 若 v 没访问过：继续 DFS
 * 若 v 访问过且 onPath[v] == true：说明出现回边（回到当前路径中的祖先），存在环
 * DFS 结束（回溯）时要把 onPath[u] = false，表示离开递归路径。
*/ 
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) { // 问题本质上是能否完成一次有向图的遍历
        // 构建有向图的邻接表表示
        unordered_map<int, vector<int>> graph;
        for(const auto& pre: prerequisites){
            graph[pre[1]].push_back(pre[0]); // pre[1] -> pre[0]
        }
        vector<bool> visited(numCourses, false); // 记录节点是否被访问过
        vector<bool> onPath(numCourses, false);  // 记录节点是否在当前路径上
        for(int i = 0; i < numCourses; ++i){
            if(!visited[i]){
                if(hasCycle(graph, i, visited, onPath)){
                    return false; // 有环，无法完成课程
                }
            }
        }
        return true; // 无环，可以完成课程
    }

/**
 * 拓扑排序（Kahn / BFS）
思路：

统计每门课入度 indegree
把入度为 0 的课入队
不断出队学习，并把其后继入度减 1
最后学到的课程数 == numCourses 则无环，否则有环
它的时间复杂度同样是 O(V+E)，并且没有递归栈风险。
 */
    bool canFinish2(int numCourses, vector<vector<int>>& prerequisites) {
        unordered_map<int, vector<int>> graph;
        vector<int> indegree(numCourses, 0); // 记录每个节点的入度

        for(const auto& pre: prerequisites){
            graph[pre[1]].push_back(pre[0]);
            indegree[pre[0]]++;
        }

        vector<int> queue;
        for(int i = 0; i < numCourses; ++i){
            if(indegree[i] == 0){
                queue.push_back(i); // 入度为 0 的节点入队
            }
        }

        int learnedCourses = 0;
        while(!queue.empty()){
            int course = queue.back();
            queue.pop_back();
            learnedCourses++;

            if(graph.find(course) != graph.end()){
                for(const int neighbor : graph.at(course)){
                    indegree[neighbor]--;
                    if(indegree[neighbor] == 0){
                        queue.push_back(neighbor);
                    }
                }
            }
        }

        return learnedCourses == numCourses;
    }
private:
    bool hasCycle(const unordered_map<int, vector<int>>& graph, int node, vector<bool>& visited, vector<bool>& onPath){
        visited[node] = true;
        onPath[node] = true;

        if(graph.find(node) != graph.end()){
            for(const int neighbor : graph.at(node)){
                if(!visited[neighbor]){
                    if(hasCycle(graph, neighbor, visited, onPath)){
                        return true; // 在子路径中发现环
                    }
                } else if(onPath[neighbor]){
                    return true; // 发现回到当前路径上的节点，存在环
                }
            }
        }

        onPath[node] = false; // 离开当前路径
        return false; // 未发现环
    }
};

int main() {
    Solution solution;
    int numCourses = 2;
    vector<vector<int>> prerequisites = {{1,0}};
    bool result = solution.canFinish(numCourses, prerequisites);
    cout << (result ? "true" : "false") << endl; // Expected output: true
    return 0;
}