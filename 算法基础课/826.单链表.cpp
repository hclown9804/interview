#include <iostream>
using namespace std;

const int N = 100010;

// head:头节点的下标
// e:节点i的值
// ne:节点i的next指针
// idx:当前已经用到了哪个点
int head, e[N], ne[N], idx;

void init() {
    head = -1;
    idx = 0;
}

void add_to_head(int x) {
    e[idx] = x, ne[idx] = head, head = idx, idx++;   
}

// 将x插入下标为k的节点后面
void add(int k, int x) {
    e[idx] = x, ne[idx] = ne[k], ne[k] = idx, idx++;
}

// 将下标是k的点后面的点删掉
void remove(int k) {
    ne[k] = ne[ne[k]];
}

int main() {
    int m;
    cin >> m;
    init();
    while (m--) {
        int x, k;
        char op;
        cin >> op;
        if (op == 'H') {
            cin >> x;
            add_to_head(x);
        } else if (op == 'D') {
            cin >> k;
            if (!k) head = ne[head];
            else remove(k - 1);
        } else {
            cin >> k >> x;
            add(k - 1, x);
        }
    }
    
    for (int i = head; i != -1; i = ne[i]) cout << e[i] << ' ';
    cout << endl;
    return 0;
}                                              
