#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
#define x first
#define y second

typedef pair<int, int> PII;
const int N = 25010, M = 150010, INF = 0x3f3f3f3f;

int n, mr, mp, s;
int id[N];
int h[N], w[M], e[M], ne[M], idx, dist[N], din[N], bcnt;
vector<int> block[N];
bool st[N];
queue<int> q;

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u, int bid) {
    id[u] = bid, block[bid].push_back(u);
    
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!id[j]) dfs(j, bid);
    }
}

void dijkstra(int bid) {
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    for (auto u: block[bid]) {
        heap.push({dist[u], u});
    }
    while (heap.size()) {
        auto t = heap.top();
        heap.pop();
        
        int ver = t.y;
        if (st[ver]) continue;
        st[ver] = true;
        
        for (int i = h[ver]; ~i; i = ne[i]) {
            int j = e[i];
            if (id[j] != id[ver] && --din[id[j]] == 0) q.push(id[j]);
            if (dist[j] > dist[ver] + w[i]) {
                dist[j] = dist[ver] + w[i];
                if (id[j] == id[ver]) heap.push({dist[j], j});
            }
        }
    }
}

void topsort() {
    memset(dist, 0x3f, sizeof dist);
    dist[s] = 0;
    for (int i = 1; i <= bcnt; ++i) {
        if (!din[i]) q.push(i);
    }
    while (q.size()) {
        int t = q.front();
        q.pop();
        dijkstra(t);
    }
}

int main() {
    cin >> n >> mr >> mp >> s;
    memset(h, -1, sizeof h);
    while (mr--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    for (int i = 1; i <= n; ++i) {
        if (!id[i]) {
            bcnt++;
            dfs(i, bcnt);
        }
    }
    while (mp--) {
        int a, b, c;
        cin >> a >> b >> c;
        din[id[b]]++;
        add(a, b, c);
    }
    topsort();
    
    for (int i = 1; i <= n; ++i) {
        if (dist[i] > INF / 2) cout << "NO PATH" << endl;
        else cout << dist[i] << endl;
    }
    return 0;
}


