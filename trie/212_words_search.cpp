#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/**
 * 《单词搜索 II》
 * 给定一个 m x n 二维字符网格 board 和一个单词（字符串）列表 words ，找出所有同时在二维网格和字典中出现的单词。
 * 单词必须按照字母顺序，通过 相邻的单元格 内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。
 * 同一个单元格内的字母在一个单词中不允许被重复使用。
 * 例如：
 * 输入：board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
 * 输出：["eat","oath"]
 */
class TrieNode {
public:
    string word; // 存储单词
    unordered_map<char, TrieNode*> children; // 存储子节点
    bool isEndOfWord; // 标记是否为单词结尾

    TrieNode() {
        isEndOfWord = false;
    }

    void insert(TrieNode* root, const string& word) {
        TrieNode* node = root; // 从根节点开始插入
        for(char c : word){
            if(node->children.find(c) == node->children.end()){
                node->children[c] = new TrieNode(); // 创建新节点
            }
            node = node->children[c];
        }
        node->isEndOfWord = true; // 标记单词结尾
        node->word = word; // 存储完整单词
    }
};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        TrieNode* root = new TrieNode();
        for(const string& word : words){
            root->insert(root, word); // 将单词插入 Trie
        }
        vector<string> result;
        int m = board.size();
        int n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false)); // 记录访问状态
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                dfs(board, visited, i, j, root, result); // 从每个单元格开始 DFS
            }
        }
        return result;
    }
private:
    void dfs(vector<vector<char>>& board, vector<vector<bool>>& visited, int x, int y, TrieNode* node, vector<string>& result) {
        if(x < 0 || x >= board.size() || y < 0 || y >= board[0].size() || visited[x][y]){
            return; // 越界或已访问
        }

        char c = board[x][y];
        if(node->children.find(c) == node->children.end()){
            return; // 当前字符不在 Trie 中
        }

        visited[x][y] = true; // 标记当前单元格为已访问
        node = node->children[c]; // 移动到 Trie 的下一个节点(对应当前字符)
        if(node->isEndOfWord){
            result.push_back(node->word); // 找到一个单词，加入结果
            node->isEndOfWord = false; // 避免重复添加同一个单词
        }

        // 继续 DFS 搜索相邻的单元格
        dfs(board, visited, x + 1, y, node, result);
        dfs(board, visited, x - 1, y, node, result);
        dfs(board, visited, x, y + 1, node, result);
        dfs(board, visited, x, y - 1, node, result);
        visited[x][y] = false; // 回溯，标记当前单元格为未访问
    }
};

int main() {
    Solution sol;
    vector<vector<char>> board = {
        {'o','a','a','n'},
        {'e','t','a','e'},
        {'i','h','k','r'},
        {'i','f','l','v'}
    };
    vector<string> words = {"oath","pea","eat","rain"};
    vector<string> result = sol.findWords(board, words);
    for (const string& word : result) {
        cout << word << " ";
    }
    cout << endl;
    return 0;
}