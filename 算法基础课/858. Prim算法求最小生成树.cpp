#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 510, INF = 0x3f3f3f3f;

int n, m, g[N][N], dist[N];
bool st[N];

int prim() {
    memset(dist, 0x3f, sizeof dist);
    int ans = 0;
    
    for (int i = 0; i < n; ++i) {
        int t = -1;
        for (int j = 1; j <= n; ++j) {
            if (!st[j] && (t == -1 || dist[t] > dist[j])) {
                t = j;
            }
        }
        if (i && dist[t] == INF) return INF;
        if (i) ans += dist[t];
        
        for (int j = 1; j <= n; ++j) dist[j] = min(dist[j], g[t][j]);
        st[t] = true;
    }
    return ans;
}

int main() {
    cin >> n >> m;
    memset(g, 0x3f, sizeof g);
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = g[b][a] = min(g[a][b], c);
    }
    int t = prim();
    if (t == INF) puts("impossible");
    else cout << t << endl;
}