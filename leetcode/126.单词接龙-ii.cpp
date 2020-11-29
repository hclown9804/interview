/*
 * @lc app=leetcode.cn id=126 lang=cpp
 *
 * [126] 单词接龙 II
 */

// @lc code=start
class Solution {
public:
    unordered_map<string, int> dist;
    unordered_set<string> S;
    queue<string> q;
    vector<vector<string>> ans;
    vector<string> path;
    string beginWord_, endWord_;

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        beginWord_ = beginWord;
        endWord_ = endWord;
        for (auto& word : wordList) S.insert(word);
        dist[beginWord] = 0;
        q.push(beginWord);
        while (q.size()) {
            auto t = q.front();
            q.pop();
            string r = t;
            for (int i = 0; i < t.size(); ++i) {
                t = r;
                for (char j = 'a'; j <= 'z'; ++j) {
                    t[i] = j;
                    if (S.count(t) && dist.count(t) == 0) {
                        dist[t] = dist[r] + 1;
                        if (t == endWord) break;
                        q.push(t);
                    }
                }
            }
        }
        if (dist.count(endWord) == 0) return ans;
        path.push_back(endWord);
        dfs(endWord);
        return ans;
    }

    void dfs(string t) {
        if (t == beginWord_) {
            reverse(path.begin(), path.end());
            ans.push_back(path);
            reverse(path.begin(), path.end());
        } else {
            string r = t;
            for (int i = 0; i < t.size(); ++i) {
                t = r;
                for (char j = 'a'; j <= 'z'; ++j) {
                    t[i] = j;
                    if (dist.count(t) && dist[t] + 1 == dist[r]) {
                        path.push_back(t);
                        dfs(t);
                        path.pop_back();
                    }
                }
            }
        }
    }
};
// @lc code=end

