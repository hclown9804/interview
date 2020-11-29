#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 10;

int n, p[N], group[N][N], ans = N;
bool st[N];

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

bool check(int group[], int gc, int idx) {
    for (int i = 0; i < gc; ++i) {
        if (gcd(p[group[i]], p[idx]) > 1) return false;
    }
    return true;
}

void dfs(int u, int gc, int tc, int start) {
    if (u >= ans) return;
    if (tc == n) ans = u;
    bool flag = true;
    for (int i = start; i < n; ++i) {
        if (!st[i] && check(group[u], gc, i)) {
            st[i] = true;
            group[u][gc] = i;
            dfs(u, gc + 1, tc + 1, i + 1);
            st[i] = false;
            flag = false;
        }
    }    
    if (flag) dfs(u + 1, 0, tc, 0);
} 

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> p[i];
    dfs(1, 0, 0, 0);
    
    cout << ans << endl;
    return 0;
}