#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010;
int n, m, h[N], sz;

void down(int u) {
    int t = u;
    if (u * 2 <= sz && h[u * 2] < h[t]) t = u * 2;
    if (u * 2 + 1 <= sz && h[u * 2 + 1] < h[t]) t = u * 2 + 1;
    if (u != t) {
        swap(h[u], h[t]);
        down(t);
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> h[i];
    sz = n;
    
    for (int i = n / 2; i; --i) down(i);
    while (m--) {
        cout << h[1] << " ";
        h[1] = h[sz--];
        down(1);
    }
    return 0;
}