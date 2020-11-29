#include <iostream>
using namespace std;

const int N = 100010;
int n, m, p[N];

// 返回x的祖宗节点(路径压缩)
int find(int x) {
    if (p[x] != x)  p[x] = find(p[x]);
    return p[x];
}

int main() {
    cin >> n >> m;
    
    for (int i = 1; i <= n; ++i) p[i] = i;
    while (m--) {
        char op[2];
        int a, b;
        cin >> op >> a >> b;
        if (op[0] == 'M') p[find(a)] = find(b);
        else {
            if (find(a) == find(b)) puts("Yes");
            else puts("No");
        }
    }
    return 0;
}