#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;
typedef pair<int, int> PII;

const int N = 50010, M = 200010, INF = 0x3f3f3f3f;

int n, m;
int h[N], e[M], w[M], ne[M], idx;
int q[N], dist[6][N];
int source[6];
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

void dijkstra(int start, int dist[]) {
    memset(dist, 0x3f, N * 4);
    dist[start] = 0;
    memset(st, 0, sizeof st);
    
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, start});
    
    while (heap.size()) {
        auto t = heap.top();
        heap.pop();
        int ver = t.second;
        if (st[ver]) continue;
        st[ver] = true;
        
        for (int i = h[ver]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[ver] + w[i]) {
                dist[j] = dist[ver] + w[i];
                heap.push({dist[j], j});
            }
        }
    }
}

int dfs(int u, int start, int distance) {
    if (u > 5) return distance;
    
    int ans = INF;
    for (int i = 1; i <= 5; ++i) {
        if (!st[i]) {
            int ne = source[i];
            st[i] = true;
            ans = min(ans, dfs(u + 1, i, distance + dist[start][ne]));
            st[i] = false;
        }
    }
    return ans;
}


int main() {
    cin >> n >> m;
    source[0] = 1;
    for (int i = 1; i <= 5; ++i) cin >> source[i];
    memset(h, -1, sizeof h);
    
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    
    for (int i = 0; i < 6; ++i) dijkstra(source[i], dist[i]);
    memset(st, 0, sizeof st);
    cout << dfs(1, 0, 0) << endl;
    return 0;
}