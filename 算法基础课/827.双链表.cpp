#include <iostream>
using namespace std;

const int N = 100010;

int e[N], l[N], r[N], idx, m;

void init() {
    // 0表示左端点,1表示右端点
    r[0] = 1, l[1] = 0;
    idx = 2;
}

// 在下标是k的点右边插入x
void insert(int k, int x) {
    e[idx] = x;
    r[idx] = r[k];
    l[idx] = k;
    l[r[k]] = idx;
    r[k] = idx++;
}

void remove(int k) {
    r[l[k]] = r[k];
    l[r[k]] = l[k];
}

int main() {
    init();
    cin >> m;
    while (m--) {
        string op;
        cin >> op;
        int k, x;
        
        if (op == "L") {
            cin >> x;
            insert(0, x);
        } else if (op == "R") {
            cin >> x;
            insert(l[1], x);
        } else if (op == "D") {
            cin >> k;
            remove(k + 1);
        } else if (op == "IL") {
            cin >> k >> x;
            insert(l[k + 1], x);
        } else {
            cin >> k >> x;
            insert(k + 1, x);
        }
    }
    
    for (int i = r[0]; i != 1; i = r[i]) cout << e[i] << ' ';
    cout << endl;
    return 0;
}