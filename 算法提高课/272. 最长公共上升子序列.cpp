#include <iostream>
#include <algorithm>
using namespace std;

const int N = 3010;
int n, a[N], b[N], f[N][N];

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int maxv = 1;
        for (int j = 1; j <= n; ++j) {
            f[i][j] = f[i - 1][j];
            if (a[i] == b[j]) f[i][j] = max(f[i][j], maxv);
            if (b[j] < a[i]) maxv = max(maxv, f[i][j] + 1);
        }
    }
    for (int i = 1; i <= n; ++i) ans = max(ans, f[n][i]);
    cout << ans << endl;
    return 0;
}