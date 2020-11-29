#include <cstring>
#include <algorithm>
#include <deque>
#include <iostream>

using namespace std;
const int N = 510, M = N * N;
#define x first
#define y second

typedef pair<int, int> PII;
int n, m;
char g[N][N];
PII q[M];
int dist[N][N];
bool st[N][N];

int bfs() {
    deque<PII> q;
    q.push_back({0, 0});
    memset(dist, 0x3f, sizeof dist);
    memset(st, false, sizeof st);
    
    dist[0][0] = 0;
    int dx[4] = {-1, -1, 1, 1}, dy[4] = {-1, 1, 1, -1};
    int ix[4] = {-1, -1, 0, 0}, iy[4] = {-1, 0, 0, -1};
    char cs[5] = "\\/\\/";
    
    while (q.size()) {
        auto t = q.front();
        q.pop_front();
        
        int x = t.x, y = t.y;
        
        if (x == n && y == m) return dist[x][y];
        
        if (st[x][y]) continue;
        st[x][y] = true;
        
        for (int i = 0; i < 4; ++i) {
            int a = x + dx[i], b = y + dy[i];
            if (a < 0 || a > n || b < 0 || b > m) continue;
            int ga = x + ix[i], gb = y + iy[i];
            int w = g[ga][gb] != cs[i];
            int d = dist[x][y] + w;
            
            if (d <= dist[a][b]) {
                dist[a][b] = d;
                if (!w) q.push_front({a, b});
                else q.push_back({a, b});
            }
        }
    }
    return -1;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 0; i < n; ++i) cin >> g[i];
         
        if (n + m & 1) puts("NO SOLUTION");
        else cout << bfs() << endl;
    }
    return 0;
}