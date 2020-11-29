#include <iostream>
using namespace std;
const int N = 1010;

int v[5] = {0, 10, 20, 50, 100}, f[N];

int main() {
    int m;
    cin >> m;
    f[0] = 1;
    for (int i = 1; i <= 4; ++i) {
        for (int j = v[i]; j <= m; ++j) {
            f[j] = f[j] + f[j - v[i]];
        }
    }
    cout << f[m] << endl;
    return 0;
}