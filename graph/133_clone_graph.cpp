#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

/**
 * 《克隆图》
 * 给你无向连通图中一个节点的引用，请你返回该图的深拷贝（克隆）。
 * 图中的每个节点都包含它的值 val（int） 和其邻居的列表（list[Node]）。
 */
class Solution {
public:
    Node* cloneGraph(Node* node) {
        if(!node)
            return nullptr;

        vector<Node*> visited(101, nullptr); // 节点值在1到100之间
        return dfsClone(node, visited);
    }

private:
    Node* dfsClone(Node* node, vector<Node*>& visited) {
        if(visited[node->val])
            return visited[node->val];

        Node* cloneNode = new Node(node->val);
        visited[node->val] = cloneNode;

        for(auto neighbor : node->neighbors){
            cloneNode->neighbors.push_back(dfsClone(neighbor, visited));
        }

        return cloneNode;
    }
};

int main() {
    // 示例用法
    Solution sol;
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    Node* node4 = new Node(4);
    node1->neighbors = {node2, node4};
    node2->neighbors = {node1, node3};
    node3->neighbors = {node2, node4};
    node4->neighbors = {node1, node3};
    Node* clonedGraph = sol.cloneGraph(node1);
    cout << "Cloned node value: " << clonedGraph->val << endl;
    return 0;
}