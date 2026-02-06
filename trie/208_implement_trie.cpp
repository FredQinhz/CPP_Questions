#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/**
 * 《实现 Trie (前缀树)》
 * Trie（发音为 "try"）或者说前缀树是一种树形数据结构，主要用于存储字符串集合，
 * 以便高效地支持以下两种操作：
 * 1. 插入字符串
 * 2. 查找字符串
 * 
 * 请你实现 Trie 类：
 * Trie() 初始化前缀树对象。
 * void insert(String word) 向前缀树中插入字符串 word 。
 * boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回 false 。
 * boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true ；否则，返回 false 。
 */
class Trie {
public:
    Trie() {
        isEndOfWord = false;
    }
    
    void insert(string word) {
        Trie* node = this;  // 从根节点开始插入
        for(char ch : word){
            if(node->children.find(ch) == node->children.end()){
                node->children[ch] = new Trie(); // 创建新节点
            }
            node = node->children[ch];
        }
        node->isEndOfWord = true; // 标记单词结尾
    }
    
    bool search(string word) {
        Trie* node = searchPrefix(word);
        return node != nullptr && node->isEndOfWord;
    }
    
    bool startsWith(string prefix) {
        Trie* node = searchPrefix(prefix);
        return node != nullptr;
    }
private:
    unordered_map<char, Trie*> children; // 存储子节点
    bool isEndOfWord; // 标记是否为单词结尾

    Trie* searchPrefix(const string& prefix){
        Trie* node = this;
        for(char ch : prefix){
            if(node->children.find(ch) == node->children.end()){
                return nullptr; // 前缀不存在
            }
            node = node->children[ch];
        }
        return node;
    }
};

int main(){
    Trie* obj = new Trie();
    obj->insert("apple");
    bool param_2 = obj->search("apple"); // return true
    bool param_3 = obj->startsWith("app"); // return true
    obj->insert("app");
    bool param_4 = obj->search("app"); // return true
    cout << param_2 << " " << param_3 << " " << param_4 << endl;
    return 0;
}