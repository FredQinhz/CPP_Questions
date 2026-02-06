#include<iostream>
#include<unordered_map>
#include<list>

using namespace std;

/**
 * 《LRU缓存》
 * 请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
 * 实现 LRUCache 类：
 * - LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
 * - int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
 * - void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
 * 函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。
 */

class LRUCache {
public:
    unordered_map<int, list<pair<int, int>>::iterator> cache;
    list<pair<int, int>> LRUList;
    int capacity;

    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        auto it = cache.find(key);
        if(it == cache.end()){
            return -1;
        } else {
            // 将该节点移动到链表头部
            LRUList.splice(LRUList.begin(), LRUList, it->second); // it->second: list<pair<int, int>>::iterator
            return it->second->second;
        }
    }
    
    void put(int key, int value) {
        auto it = cache.find(key);

        if(it != cache.end()){
            it->second->second = value;
            LRUList.splice(LRUList.begin(), LRUList, it->second);
            return;
        }

        if(capacity == 0) return;

        if(cache.size() == capacity){
            int oldKey = LRUList.back().first;
            cache.erase(oldKey);
            LRUList.pop_back();
        }
        LRUList.emplace_front(key, value);
        cache[key] = LRUList.begin();
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main(){
    int capacity = 2;
    LRUCache* obj = new LRUCache(capacity);
    obj->put(1, 1);
    obj->put(2, 2);
    cout << obj->get(1) << endl; // 返回 1
    obj->put(3, 3);              // 该操作会使得关键字 2 作废
    cout << obj->get(2) << endl; // 返回 -1 (未找到)
    obj->put(4, 4);              // 该操作会使得关键字 1 作废
    cout << obj->get(1) << endl; // 返回 -1 (未找到
    cout << obj->get(3) << endl; // 返回 3
    cout << obj->get(4) << endl; // 返回 4
    return 0;
}