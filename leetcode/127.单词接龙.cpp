/*
 * @lc app=leetcode.cn id=127 lang=cpp
 *
 * [127] 单词接龙
 */

// @lc code=start
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> S;
        for (auto& word : wordList) S.insert(word);
        unordered_map<string, int> dist;
        dist[beginWord] = 0; 
        queue<string> q;
        q.push(beginWord);

        while (q.size()) {
            auto t = q.front();
            q.pop();

            string r = t;
            for (int i = 0; i < t.size(); i++) {
                t = r;
                for (char j = 'a'; j <= 'z'; ++j) {
                    t[i] = j;
                    if (S.count(t) && !dist.count(t)) {
                        dist[t] = dist[r] + 1;
                        if (t == endWord) return dist[t] + 1;
                        q.push(t);
                    }
                }
            }
        }    
        return 0;
    }
};
// @lc code=end

