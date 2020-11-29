#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

const int N = 100010;

int n, m, ph[N], hp[N], h[N], sz;

void heap_swap(int a, int b) {
    swap(ph[hp[a]], ph[hp[b]]);
    swap(hp[a], hp[b]);
    swap(h[a], h[b]);
}

void down(int u) {
    int t = u;
    if (u * 2 <= sz && h[u * 2] < h[t]) t = u * 2;
    if (u * 2 + 1 <= sz && h[u * 2 + 1] < h[t]) t = u * 2 + 1;
    if (u != t) {
        heap_swap(u, t);
        down(t);
    }
}

void up(int u) {
    while (u / 2 && h[u / 2] > h[u]) {
        heap_swap(u / 2, u);
        u /= 2;
    }
} 

int main() {
    cin >> n;
    while (n --) {
        char op[10];
        int k, x;
        cin >> op;
        
        if (!strcmp(op, "I")) {
            cin >> x;
            sz++;
            m++;
            ph[m] = sz, hp[sz] = m;
            h[sz] = x;
            up(sz);
        } else if (!strcmp(op, "PM")) cout << h[1] << endl;
        else if (!strcmp(op, "DM")) {
            heap_swap(1, sz--);
            down(1);
        } else if (!strcmp(op, "D")) {
            cin >> k;
            k = ph[k];
            heap_swap(k, sz);
            sz--;
            down(k), up(k);
        } else {
            cin >> k >> x;
            k = ph[k];
            h[k] = x;
            down(k), up(k);
        }
    }
    return 0;
}