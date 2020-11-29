/*
 * @lc app=leetcode.cn id=118 lang=cpp
 *
 * [118] 杨辉三角
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ans;
        for (int i = 0; i < numRows; ++i) {
            vector<int> line(i + 1);
            line[0] = line[i] = 1;
            for (int j = 1; j < i; j++) {
                line[j] = ans[i - 1][j - 1] + ans[i -1][j];
            }
            ans.push_back(line);
        }
        return ans;
    }
};
// @lc code=end

