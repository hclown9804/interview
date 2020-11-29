/*
 * @lc app=leetcode.cn id=148 lang=cpp
 *
 * [148] 排序链表
 * 归并排序：自底向上非递归
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
    ListNode* sortList(ListNode* head) {
        int n = 0;
        for (auto p = head; p; p = p->next) n++;
        auto dummy = new ListNode(-1);
        dummy->next = head;

        for (int i = 1; i < n; i *= 2) {
            auto cur = dummy;
            for (int j = 1; j + i <= n; j += i * 2) {
                auto p = cur->next, q = p;
                for (int k = 0; k < i; ++k) q = q->next;
                int x = 0, y = 0;
                while (x < i && y < i && p && q) {
                    if (p->val <= q->val) cur = cur->next = p, p = p->next, x++;
                    else cur = cur->next = q, q = q->next, y++;
                }
                while (x < i && p) cur = cur->next = p, p = p->next, x++;
                while (y < i && q) cur = cur->next = q, q = q->next, y++;
                cur->next = q;
            }
        }
        return dummy->next;
    }
};
// @lc code=end

