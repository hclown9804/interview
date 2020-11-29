#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <unordered_map>

using namespace std;
char g[2][4];
unordered_map<string, pair<char, string>> pre;
unordered_map<string, int> dist;

void set(string state) {
    for (int i = 0; i < 4; ++i)g[0][i] = state[i];
    for (int i = 7, j = 0; j < 4; --i, ++j) g[1][j] = state[i];
}

string get() {
    string ans;
    for (int i = 0; i < 4; ++i) ans += g[0][i];
    for (int i = 3; i >= 0; --i) ans += g[1][i];
    return ans;
}

string move0(string state) {
    set(state);
    for (int i = 0; i < 4; ++i) swap(g[0][i], g[1][i]);
    return get();
}

string move1(string state) {
    set(state);
    int v0 = g[0][3], v1 = g[1][3];
    for (int i = 3; i >= 0; --i) {
        g[0][i] = g[0][i - 1];
        g[1][i] = g[1][i - 1];
    }
    g[0][0] = v0, g[1][0] = v1;
    return get();
}

string move2(string state) {
    set(state);
    int v = g[0][1];
    g[0][1] = g[1][1];
    g[1][1] = g[1][2];
    g[1][2] = g[0][2];
    g[0][2] = v;
    return get();
}

int bfs(string start, string end) {
    if (start == end) return 0;
    queue<string> q;
    q.push(start);
    dist[start] = 0;
    
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        
        string m[3];
        m[0] = move0(t);
        m[1] = move1(t);
        m[2] = move2(t);
        
        for (int i = 0; i < 3; ++i) {
            if (!dist.count(m[i])) {
                dist[m[i]] = dist[t] + 1;
                pre[m[i]] = {'A' + i, t};
                q.push(m[i]);
                if (m[i] == end) return dist[end];
            }
        }
    }
    return -1;
}

int main() {
    int x;
    string start, end;
    for (int i = 0; i < 8; ++i) {
        cin >> x;
        end += char(x + '0');
    }
    
    for (int i = 1; i <= 8; ++i) start += char('0' + i);
    int step = bfs(start, end);
    
    cout << step << endl;
    
    string ans;
    while (end != start) {
        ans += pre[end].first;
        end = pre[end].second;
    }
    reverse(ans.begin(), ans.end());
    if (step > 0) cout << ans << endl;
    return 0;
}