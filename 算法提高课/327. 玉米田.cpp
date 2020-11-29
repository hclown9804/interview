#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 14, M = 1 << 12, mod = 1e8;
int n, m, g[N];
vector<int> state, head[M];
int f[N][M];

bool check(int state) {
    for (int i = 0; i < m; ++i) {
        if ((state >> i & 1) && (state >> i + 1 & 1)) return false;
    }
    return true;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < m; ++j) {
            int t;
            cin >> t;
            g[i] += !t << j;
        }
    }

    for (int i = 0; i < 1 << m; ++i) {
        if (check(i)) state.push_back(i);
    }

    for (int i = 0; i < state.size(); ++i) {
        for (int j = 0; j < state.size(); ++j) {
            int a = state[i], b = state[j];
            if ((a & b) == 0) head[i].push_back(j);
        }
    }
    f[0][0] = 1;
    for (int i = 1; i <= n + 1; ++i) {
        for (int a = 0; a < state.size(); ++a) {
            for (int b: head[a]) {
                if (g[i] & state[a]) continue;
                f[i][a] = (f[i][a] + f[i - 1][b]) % mod;
            }
        }
    }
    cout << f[n + 1][0] << endl;
    return 0;
}