#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <unordered_map>
using namespace std;

int f(string state) {
    int ans = 0;
    for (int i = 0; i < state.size(); ++i) {
        if (state[i] != 'x') {
            int t = state[i] - '1';
            ans += abs(i / 3 - t / 3) + abs(i % 3 - t % 3);
        }
    }
    return ans;
}

string bfs(string start) {
    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
    char op[4] = {'u', 'r', 'd', 'l'};
    
    string end = "12345678x";
    unordered_map<string, int> dist;
    unordered_map<string, pair<string, char>> prev;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> heap;

    heap.push({f(start), start});
    dist[start] = 0;
    
    while (heap.size()) {
        auto t= heap.top();
        heap.pop();
        
        string state = t.second;
        if (state == end) break;
        
        int step = dist[state];
        int x, y;
        for (int i = 0; i < state.size(); ++i) {
            if (state[i] == 'x') {
                x = i / 3, y = i % 3;
                break;
            }
        }
        string source = state;
        for (int i = 0; i < 4; ++i) {
            int a = x + dx[i], b = y + dy[i];
            if (a >= 0 && a < 3 && b >= 0 && b < 3) {
                swap(state[x * 3 + y], state[a * 3 + b]);
                if (!dist.count(state) || dist[state] > step + 1) {
                    dist[state] = step + 1;
                    prev[state] = {source, op[i]};
                    heap.push({dist[state] + f(state), state});
                }
                swap(state[x * 3 + y], state[a * 3 + b]);
            }
        }
    }
    string ans;
    while (start != end) {
        ans += prev[end].second;
        end = prev[end].first;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    string g, c, seq;
    while (cin >> c) {
        g += c;
        if (c != "x") seq += c;
    }
    
    int t = 0;
    for (int i = 0; i < seq.size(); ++i) {
        for (int j = i + 1; j < seq.size(); ++j) {
            if (seq[i] > seq[j]) ++t;
        }
    }
    
    if (t % 2) cout << "unsolvable" << endl;
    else cout << bfs(g) << endl;
    return 0;
}