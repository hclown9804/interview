#include <iostream>
using namespace std;

const int N = 100010;
int n, m;
int p[N], sz[N];

int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}

int main() {
    cin >> n >> m;
    
    for (int i = 1; i <= n; ++i) p[i] = i, sz[i] = 1;
    
    while (m--) {
        char op[5];
        int a, b;
        cin >> op;
        
        if (op[0] == 'C') {
            cin >> a >> b;
            if (find(a) == find(b)) continue;
            sz[find(b)] += sz[find(a)];
            p[find(a)] = find(b);
        }
        else if (op[1] == '1') {
            cin >> a >> b;
            if (find(a) == find(b)) puts("Yes");
            else puts("No");
        } else {
            cin >> a;
            cout << sz[find(a)] << endl;
        }
    }
    return 0;
}