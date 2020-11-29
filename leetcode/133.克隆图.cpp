/*
 * @lc app=leetcode.cn id=133 lang=cpp
 *
 * [133] 克隆图
 * 1、复制所有点
 * 2、复制所有边
 */

// @lc code=start
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    unordered_map<Node*, Node*> map;

    Node* cloneGraph(Node* node) {
        if (!node) return NULL;
        dfs(node);   

        for (auto [s, d]: map) {
            for (auto ver: s->neighbors) {
                d->neighbors.push_back(map[ver]);
            }
        }
        return map[node];
    }

    void dfs(Node* node) {
        map[node] = new Node(node->val);
        for (auto ver: node->neighbors) {
            if (map.count(ver) == 0) dfs(ver);
        }
    } 
};
// @lc code=end

