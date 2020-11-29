#include <iostream>
#include <algorithm>
using namespace std;
typedef pair<int, int> PII;
const int N = 5010;
int n, f[N];
PII q[N];

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> q[i].first >> q[i].second;
    sort(q, q + n);
    
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        f[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (q[i].second > q[j].second) f[i] = max(f[i], f[j] + 1);
        }
        ans = max(ans, f[i]);
    }
    cout << ans << endl;
    return 0;
}