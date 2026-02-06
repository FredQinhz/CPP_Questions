#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/** 
 * 《添加与搜索单词 - 数据结构设计》
 * 设计一个支持以下两种操作的数据结构：
 * void addWord(word)：将 word 添加到数据结构中，之后可以对它进行匹配
 * bool search(word)：如果数据结构中存在字符串与 word 匹配，则返回 true
 * 其中 word 可能包含一些 '.' ，每个 . 都可以表示任何一个字母。
 * 例如：
 * addWord("bad")
 * addWord("dad")
 * addWord("mad")
 * search("pad") -> false
 * search("bad") -> true
 * search(".ad") -> true
 * search("b..") -> true
 */
class WordDictionary {
public:
    WordDictionary() {
        isEndOfWord = false;
    }
    
    void addWord(string word) {
        WordDictionary* node = this;  // 从根节点开始插入
        for(char ch : word){
            if(node->children.find(ch) == node->children.end()){
                node->children[ch] = new WordDictionary(); // 创建新节点
            }
            node = node->children[ch];
        }
        node->isEndOfWord = true; // 标记单词结尾
    }
    
    bool search(string word) {
        return searchInNode(word, this, 0);
    }

private:
    unordered_map<char, WordDictionary*> children; // 存储子节点
    bool isEndOfWord; // 标记是否为单词结尾

    bool searchInNode(const string& word, WordDictionary* node, int index) {
        if(index == word.size()){
            return node->isEndOfWord;
        }
        char ch = word[index];
        if(ch != '.'){
            if(node->children.find(ch) == node->children.end()){
                return false; // 字符不存在
            }
            return searchInNode(word, node->children[ch], index + 1);
        } else {
            // 遇到 '.'，尝试所有可能的子节点
            for(const auto& pair : node->children){
                if(searchInNode(word, pair.second, index + 1)){
                    return true;
                }
            }
            return false; // 所有路径均不匹配
        }
    }
};

int main(){
    WordDictionary wordDictionary;
    wordDictionary.addWord("bad");
    wordDictionary.addWord("dad");
    wordDictionary.addWord("mad");
    cout << boolalpha << wordDictionary.search("pad") << endl; // 返回 false
    cout << boolalpha << wordDictionary.search("bad") << endl; // 返回 true
    cout << boolalpha << wordDictionary.search(".ad") << endl; // 返回 true
    cout << boolalpha << wordDictionary.search("b..") << endl; // 返回 true
    return 0;
}