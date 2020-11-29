/*
 * @lc app=leetcode.cn id=138 lang=cpp
 *
 * [138] 复制带随机指针的链表
 */

// @lc code=start
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        for (auto p = head; p != NULL; p = p->next->next) {
            auto q = new Node(p->val);
            q->next = p->next;
            p->next = q;
        }

        for (auto p = head; p != NULL; p = p->next->next) {
            if (p->random) p->next->random = p->random->next;
        }

        auto dummy = new Node(-1), cur = dummy;
        for (auto p = head; p != NULL; p = p->next) {
            auto q = p->next;
            cur = cur->next = q;
            p->next = q->next;
        }
        return dummy->next;
    }
};
// @lc code=end

