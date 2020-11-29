/*
 * @lc app=leetcode.cn id=143 lang=cpp
 *
 * [143] 重排链表
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head) return;
        int n = 0; 
        for (auto p = head; p; p = p->next) n++;

        auto mid = head;
        for (int i = 0; i < (n + 1) / 2 - 1; ++i) mid = mid->next;
        auto a = mid, b = a->next;
        for (int i = 0; i < n / 2; ++i) {
            auto c = b->next;
            b->next = a, a = b, b = c;
        }
        auto p = head, q = a;
        for (int i = 0 ; i < n / 2; ++i) {
            auto o = q->next;
            q->next = p->next;
            p->next = q;
            if (n % 2 == 0 && i == n / 2 - 1) q->next = NULL;
            p = q->next;
            q = o;
        }
        if (n % 2) p->next = NULL;
    }
};
// @lc code=end

