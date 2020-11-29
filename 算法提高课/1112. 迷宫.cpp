#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 110;
int n, xa,xb, ya, yb;
char g[N][N];
bool st[N][N];
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

bool dfs(int x, int y) {
    if (g[x][y] == '#') return false;
    if (x == xb && y == yb) return true;
    
    st[x][y] = true;
    for (int i = 0; i < 4; ++i) {
        int a = x + dx[i], b = y + dy[i];
        if (a < 0 || a >= n || b < 0 || b >= n) continue;
        if (st[a][b]) continue;
        
        if (dfs(a, b)) return true;
    }
    return false;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; ++i) cin >> g[i];
        memset(st, 0, sizeof st);
        cin >> xa >> ya >> xb >> yb;
        if (dfs(xa, ya)) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}