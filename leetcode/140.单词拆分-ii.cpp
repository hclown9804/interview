/*
 * @lc app=leetcode.cn id=140 lang=cpp
 *
 * [140] 单词拆分 II
 */

// @lc code=start
class Solution {
public:
    vector<string> ans;
    vector<bool> f;
    unordered_set<string> hash;
    int n;

    vector<string> wordBreak(string s, vector<string>& wordDict) {
        n = s.size();
        f.resize(n + 1);
        f[n] = true;
        for (auto& word : wordDict) hash.insert(word);
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i; j < n; ++j) {
                if (hash.count(s.substr(i, j - i + 1)) && f[j + 1]) f[i] = true;
            }
        }
        dfs(s, 0, "");
        return ans;
    }

    void dfs(string& s, int u, string path) {
        if (u == n) {
            path.pop_back();
            ans.push_back(path);
        } else {
            for (int i = u; i < n; ++i) {
                if (hash.count(s.substr(u, i - u + 1)) && f[i + 1]) {
                    dfs(s, i + 1, path + s.substr(u, i - u + 1) + ' ');
                }
            }
        }
    }
};
// @lc code=end

