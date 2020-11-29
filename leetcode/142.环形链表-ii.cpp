/*
 * @lc app=leetcode.cn id=142 lang=cpp
 *
 * [142] 环形链表 II
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (!head || !head->next) return NULL;
        auto s = head, f = head->next;
        while (f) {
            s = s->next;
            f = f->next;
            if (!f) return NULL;
            f = f->next;
            if (s == f) {
                s = head;
                f = f->next;
                while (s != f) s = s->next, f = f->next;
                return s;
            }
        } 
        return NULL;
    }
};
// @lc code=end

