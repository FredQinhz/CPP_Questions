#include <iostream>
#include <vector>

using namespace std;

/**
 * 《环形链表》
 * 给你一个链表的头节点 head ，判断链表中是否有环。
 * 如果链表中存在环，则返回 true 。 否则，返回 false 。
 */
class Solution {
public:
    struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };

    bool hasCycle(ListNode *head) {
        ListNode *fast = head;
        ListNode *slow = head;
        while(fast != NULL && fast->next != NULL){
            fast = fast->next->next;
            slow = slow->next;
            if(fast == slow)
                return true;
        }
        return false;
    }
};

int main(){
    Solution sol;
    Solution::ListNode* head = new Solution::ListNode(3);
    head->next = new Solution::ListNode(2);
    head->next->next = new Solution::ListNode(0);
    head->next->next->next = new Solution::ListNode(-4);
    head->next->next->next->next = head->next; // Create a cycle
    bool result = sol.hasCycle(head);
    cout << (result ? "true" : "false") << endl;
    return 0;
}