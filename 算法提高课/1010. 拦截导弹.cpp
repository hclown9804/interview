#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1010;
int n, q[N], f[N], g[N];

int main() {
    while (cin >> q[n]) n++;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        f[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (q[j] >= q[i]) f[i] = max(f[i], f[j] + 1);
        }
        ans = max(ans, f[i]);
    }
    cout << ans << endl;
    
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        int k = 0;
        while (k < cnt && g[k] < q[i]) k++;
        g[k] = q[i];
        if (k >= cnt) cnt++;
    }
    cout << cnt << endl;
    return 0;
}