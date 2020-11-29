#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 100010, INF = 0x3f3f3f3f;
int n, w[N], f[N][2];

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> w[i];
        f[0][0] = 0, f[0][1] = -INF;
        for (int i = 1; i <= n; ++i) {
            f[i][0] = max(f[i - 1][0], f[i - 1][1]);
            f[i][1] = f[i - 1][0] + w[i];
        }
        cout << max(f[n][0], f[n][1]) << endl;
    }
    return 0;
}