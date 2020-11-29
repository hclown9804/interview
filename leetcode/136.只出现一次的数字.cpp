/*
 * @lc app=leetcode.cn id=136 lang=cpp
 *
 * [136] 只出现一次的数字
 * x ^ x = 0
 */

// @lc code=start
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ans = 0;
        for (auto x: nums) ans ^= x;
        return ans;
    }
};
// @lc code=end

