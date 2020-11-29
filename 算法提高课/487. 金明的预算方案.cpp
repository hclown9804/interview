#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> PII;
#define v first
#define w second

const int N = 70, M = 32010;
int n, m, f[M];
PII master[N];
vector<PII> servent[M];

int main() {
    cin >> m >> n;
    for (int i = 1; i <= n; ++i) {
        int v, w, q;
        cin >> v >> w >> q;
        if (!q) master[i] = {v, v * w};
        else servent[q].push_back({v, v * w});
    }
    for (int i = 1; i <= n; ++i) {
        if (master[i].v) {
            for (int j = m; j >= 0; --j) {
                auto &sv = servent[i];
                for (int k = 0; k < 1 << sv.size(); ++k) {
                    int v = master[i].v, w = master[i].w;
                    for (int u = 0; u < sv.size(); ++u) {
                        if (k >> u & 1) {
                            v += sv[u].v;
                            w += sv[u].w;
                        }
                    }
                    if (j >= v) f[j] = max(f[j], f[j - v] + w);
                }
            }
        }
    }
    cout << f[m] << endl;
    return 0;
}