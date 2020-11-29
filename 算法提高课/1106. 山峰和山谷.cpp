#include <iostream>
#include <algorithm>
using namespace std;

const int  N = 1010, M = N * N;
typedef pair<int, int> PII;
#define x first
#define y second
int n, h[N][N];
PII q[M];
bool st[N][N];

void bfs(int sx, int sy, bool& has_higher, bool& has_lower) {
    int hh = 0, tt = 0;
    q[0] = {sx, sy};
    st[sx][sy] = true;
    while (hh <= tt) {
        PII t = q[hh++];
        
        for (int i = t.x - 1; i <= t.x + 1; ++i) {
            for (int j = t.y - 1; j <= t.y + 1; ++j) {
                if (i == t.x && j == t.y) continue;
                if (i < 0 || i >= n || j < 0 || j >= n) continue;
                if (h[i][j] != h[t.x][t.y]) {
                    if (h[i][j] > h[t.x][t.y]) has_higher = true;
                    else has_lower = true;
                } else if (!st[i][j]) {
                    q[++tt] = {i, j};
                    st[i][j] = true;
                }
            }
        }
    }
}

int main() {
    cin >> n;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> h[i][j];
        }
    }
    
    int peak = 0, valley = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!st[i][j]) {
                bool has_higher = false, has_lower = false;
                bfs(i, j, has_higher, has_lower);
                if (!has_higher) peak++;
                if (!has_lower) valley++;
            }
        }
    }
    cout << peak << " " << valley << endl;
    return 0;
}