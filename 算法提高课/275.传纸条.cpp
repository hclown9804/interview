#include <iostream>
using namespace std;

const int N = 55;
int n, m;
int w[N][N], f[N * 2][N][N];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> w[i][j];
        }
    }
    
    for (int k = 2; k <= n + m; ++k) {
        for (int x1 = max(1, k - m); x1 <= min(k - 1, n); x1++) {
            for (int x2 = max(1, k - m); x2 <= min(k - 1, n); x2++) {
                int t = w[x1][k - x1];
                if (x1 != x2) t += w[x2][k - x2];
                for (int a = 0; a <= 1; ++a) {
                    for (int b = 0; b <= 1; ++b) {
                        f[k][x1][x2] = max(f[k][x1][x2], f[k - 1][x1 - a][x2 - b] + t);
                    }
                }
            }
        }
    }
    cout << f[n + m][n][n] << endl;
    return 0;
}