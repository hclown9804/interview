#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 810, M = 3000, INF = 0x3f3f3f3f;

int n, m, p;
int id[N];
int h[N], w[M], ne[M], e[M], idx;
int dist[N], q[N];
bool st[N];

void add(int a, int b, int c) {
    w[idx] = c, e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

int spfa(int s) {
    memset(dist, 0x3f, sizeof dist);
    dist[s] = 0;
    
    int hh = 0, tt = 1;
    q[0] = s, st[s] = true;
    
    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) hh = 0;
        st[t] = false;
        
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                if (!st[j]) {
                    q[tt++] = j;
                    if (tt == N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int j = id[i];
        if (dist[j] == INF) return INF;
        ans += dist[j];
    }
    return ans;
}

int main() {
    cin >> n >> p >> m;
    for (int i = 0; i < n; ++i) cin >> id[i];
    
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    
    int ans = INF;
    for (int i = 1; i <= p; ++i) ans = min(ans, spfa(i));
    cout << ans << endl;
    return 0;
}