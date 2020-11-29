#include <iostream>
using namespace std;

const int N = 20;
int n;
char g[N][N];
bool col[N], dg[N], udg[N];

void dfs(int u) {
    if (u == n) {
        for (int i = 0; i < n; ++i) cout << g[i] << endl;
        puts("");
        return;
    }
    
    for (int i = 0; i < n; ++i) {
        if (!col[i] && !dg[u + i] && !udg[n - u + i]) {
            g[u][i] = 'Q';
            col[i] = dg[u + i] = udg[n - u + i] = true;
            dfs(u + 1);
            col[i] = dg[u + i] = udg[n- u + i] = false;
            g[u][i] = '.';
        }
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            g[i][j] = '.';
        }
    }
    dfs(0);

    return 0;
}


#include <iostream>
using namespace std;

const int N = 20;
int n;
char g[N][N];
bool row[N], col[N], dg[N * 2], udg[N * 2];

void dfs(int x, int y, int s) {
    if (s > n) return;
    if (y == n) y = 0, x++;
    if (x == n) {
        if (s == n) {
            for (int i = 0; i < n; ++i) cout << g[i] << endl;
            puts("");
            
        } 
        return;
    }
    
    g[x][y] = '.';
    dfs(x, y + 1, s);
    
    if (!row[x] && !col[y] && !dg[x + y] && !udg[n - y + x]) {
        row[x] = col[y] = dg[x + y] = udg[ n- y + x] = true;
        g[x][y] = 'Q';
        dfs(x, y + 1, s + 1);
        g[x][y] = '.';
        row[x] = col[y] = dg[x + y] = udg[ n- y + x] = false;
    }
}

int main() {
    cin >> n;

    dfs(0, 0, 0);

    return 0;
}