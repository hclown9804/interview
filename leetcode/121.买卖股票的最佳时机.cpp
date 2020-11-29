/*
 * @lc app=leetcode.cn id=121 lang=cpp
 *
 * [121] 买卖股票的最佳时机
 */

// @lc code=start
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int ans = 0, minp = INT_MAX;
        for (int i = 0; i < prices.size(); ++i) {
            ans = max(ans, prices[i] - minp);
            minp = min(minp, prices[i]);
        }
        return ans;
    }
};
// @lc code=end

