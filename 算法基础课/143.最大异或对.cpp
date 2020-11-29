#include <iostream>
using namespace std;

const int N = 100010, M = 31 * N;

int n;
int a[N], son[M][2], idx;

void insert(int x) {
    int p = 0;
    for (int i = 30; i >= 0; --i) {
        int u = x >> i & 1;
        if (!son[p][u]) son[p][u] = ++idx;
        p = son[p][u];
    }
}

int query(int x) {
    int p = 0, ans = 0;
    for (int i = 30; i >= 0; --i) {
        int u = x >> i & 1;
        if (son[p][!u]) {
            ans = ans * 2 + !u;
            p = son[p][!u];
        } else {
            p = son[p][u];
            ans = ans * 2 + u;
        }
    }
    return ans;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        insert(a[i]);
        int t = query(a[i]);
        ans = max(ans, a[i] ^ t);
    }
    cout << ans << endl;
    return 0;
}