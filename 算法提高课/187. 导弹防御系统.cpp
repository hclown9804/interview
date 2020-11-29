#include <iostream>
#include <algorithm>
using namespace std;

const int N = 55;
int n, q[N], up[N], down[N], ans;

void dfs(int u, int su, int sd) {
    if (su + sd >= ans) return;
    if (u == n) {
        ans = su + sd;
        return;
    }
    // 1.讲当前数放入上升子序列
    int k = 0;
    while (k < su && up[k] >= q[u]) k++;
    int t = up[k];
    up[k] = q[u];
    if (k < su) dfs(u + 1, su, sd);
    else dfs(u + 1, su + 1, sd);
    up[k] = t;
    
    // 2.讲当前数放入下降子序列
    k = 0;
    while (k < sd && down[k] <= q[u]) k++;
    t = down[k];
    down[k] = q[u];
    if (k < sd) dfs(u + 1, su, sd);
    else dfs(u + 1, su, sd + 1);
    down[k] = t;
}

int main() {
    while (cin >> n, n) {
        for (int i = 0; i < n; ++i) cin >> q[i];
        ans = n;
        dfs(0, 0, 0);
        cout << ans << endl;
    }
    return 0;
}