#include <iostream>
#include <algorithm>
#include <cstring>
#include <deque>
using namespace std;

const int N = 1010, M = 20010;
int n, m, k;
int h[N], e[M], w[M], ne[M], idx, dist[N];
deque<int> q;
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
} 

bool check(int bound) {
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
    
    q.push_back(1);
    dist[1] = 0;
    while (q.size()) {
        int t = q.front();
        q.pop_front();
        
        if (st[t]) continue;
        st[t] = true;
        
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i], x = w[i] > bound;
            if (dist[j] > dist[t] + x) {
                dist[j] = dist[t] + x;
                if (!x) q.push_front(j);
                else q.push_back(j);
            }
        }
    }
    return dist[n] <= k;
}

int main() {
    cin >> n >> m >> k;
    memset(h, -1, sizeof h);
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    int l = 0, r = 1e6 + 1;
    while (l < r) {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    if (r == 1e6 + 1) cout << -1 << endl;
    else cout << r << endl;
    return 0;
}
