#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 1010, M = N * N;
typedef pair<int, int> PII;
#define x first
#define y second

int n, m, dist[N][N];
PII q[M];
char g[N][N];

void bfs() {
    int hh = 0, tt = -1;
    memset(dist, -1, sizeof dist);
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (g[i][j] == '1') {
                dist[i][j] = 0;
                q[++tt] = {i, j}; 
            }
        }
    }
    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
    while (hh <= tt) {
        auto t = q[hh++];
        for (int i = 0; i < 4; ++i) {
            int a = t.x + dx[i], b = t.y + dy[i];
            if (a < 0 || a >= n || b < 0 || b >= m) continue;
            if (dist[a][b] != -1) continue;
            dist[a][b] = dist[t.x][t.y] + 1;
            q[++tt] = {a, b};
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> g[i];
    }
    
    bfs();
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << dist[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}