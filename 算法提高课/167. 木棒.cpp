#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 70;

int n;
int w[N], sum, length;
bool st[N];

bool dfs(int u, int s, int start) {
    if (u * length == sum) return true;
    if (s == length) return dfs(u + 1, 0, 0);
    
    // 剪枝3-1，从start开始枚举
    for (int i = start; i < n; ++i) {
        if (st[i]) continue;
        if (s + w[i] > length) continue; // 可行性剪枝
        
        st[i] = true;
        if (dfs(u, s + w[i], i + 1)) return true;
        st[i] =  false;
        
        // 剪枝3-3
        if (!s) return false;
        
        // 剪枝3-4
        if (s + w[i] == length) return false;
        
        // 剪枝3-2
        int j = i;
        while (j < n && w[j] == w[i]) j++;
        i = j - 1;
    }
    return false;
}

int main() {
    while (cin >> n, n) {
        memset(st, 0, sizeof st);
        sum = 0;
        for (int i = 0; i < n; ++i)  {
            cin >> w[i];
            sum += w[i];
        }
        // 剪枝2，优化搜索顺序
        sort(w, w + n);
        reverse(w, w + n);
        
        length = 1;
        while (true) {
            // 剪枝1
            if (sum % length == 0 && dfs(0, 0, 0)) {
                cout << length << endl;
                break;
            }
            length++;
            if (length > sum) break;
        }
    }
    return 0;
}