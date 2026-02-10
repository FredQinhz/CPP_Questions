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
class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        TrieNode* root = new TrieNode();
        for(const string& word : words){
            root->insert(root, word); // 将单词插入 Trie
        }
    }
private:

};
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