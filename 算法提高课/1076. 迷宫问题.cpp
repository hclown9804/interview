#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
typedef pair<int, int> PII;
#define x first
#define y second

const int N = 1010, M = N * N;
int n, g[N][N];
PII q[M], pre[N][N];

void bfs(int sx, int sy) {
    int dx[4] = {-1, 0, 1, 0,}, dy[4] = {0, 1, 0, -1};
    int hh = 0, tt = 0;
    q[0] = {sx, sy};
    
    memset(pre, -1, sizeof pre);
    pre[sx][sy] = {0, 0};
    while (hh <= tt) {
        PII t = q[hh++];
        for (int i = 0; i < 4; ++i) {
            int a = t.x + dx[i], b = t.y + dy[i];
            if (a < 0 || a >= n || b < 0 || b >= n) continue;
            if (g[a][b]) continue;
            if (pre[a][b].x != -1) continue;
            
            q[++tt] = {a, b};
            pre[a][b] = t;
        }
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) 
        for (int j = 0; j < n; ++j) 
            cin >> g[i][j];
            
    bfs(n - 1,n - 1);
    PII end(0, 0);
    
    while (true) {
        cout << end.x << " " << end.y << endl;
        if (end.x == n - 1 && end.y == n - 1) break;
        end = pre[end.x][end.y];
    }
    return 0;
}