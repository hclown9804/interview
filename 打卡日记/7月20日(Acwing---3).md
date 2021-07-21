### [1097. 池塘计数](https://www.acwing.com/problem/content/1099/)

```java
import java.io.*;
import java.util.*;

class Main {
    static int N = 1010, M = N * N;
    static char[][] matrix = new char[N][N];
    static boolean[][] st = new boolean[N][N];
    static int n, m;
        
    public static void bfs(int x, int y) {
        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{x, y});
        while (!queue.isEmpty()) {
            int[] cur = queue.poll();
            x = cur[0];
            y = cur[1];
            for (int i = x - 1; i <= x + 1; ++i) {
                for (int j = y - 1; j <= y + 1; ++j) {
                    if (i == x && j == y) continue;
                    if (i < 0 || i >= n || j < 0 ||j >= m) continue;
                    if (matrix[i][j] == '.' || st[i][j]) continue;
                    queue.offer(new int[]{i, j});
                    st[i][j] = true;
                }
            }
        }
    }
    
    public static void main(String[] args) throws IOException{
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String[] cur = in.readLine().split(" ");
        n = Integer.parseInt(cur[0]);
        m = Integer.parseInt(cur[1]);
        for (int i = 0; i < n; ++i) {
            char[] arr = in.readLine().toCharArray();
            matrix[i] = arr;
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (matrix[i][j] == '.' || st[i][j]) continue;
                bfs(i, j);
                ans++;
            }
        }
        System.out.println(ans);
    }
}
```

### [1098. 城堡问题](https://www.acwing.com/problem/content/1100/)

```java
import java.util.*;
import java.io.*;

class Main {
    static int N = 60;
    static int n, m;
    static int[][] matrix = new int[N][N];
    static boolean[][] st = new boolean[N][N];
    static int[] dx = {0, -1, 0, 1}, dy = {-1, 0, 1, 0};
    
    public static int bfs(int x, int y) {
        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{x, y});
        st[x][y] = true;
        int cnt = 0;
        while (!queue.isEmpty()) {
            int[] cur = queue.poll();
            x = cur[0];
            y = cur[1];
            cnt++;
            for (int i = 0; i < 4; ++i) {
                int a = x + dx[i], b = y + dy[i];
                if (a < 0 || a >= n || b < 0 || b >= m) continue;
                if ((matrix[x][y] >> i & 1) == 1 || st[a][b]) continue;
                st[a][b] = true;
                queue.offer(new int[]{a, b});
            }
        }
        return cnt;
    }
    
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String[] cur = in.readLine().split(" ");
        n = Integer.parseInt(cur[0]);
        m = Integer.parseInt(cur[1]);
        
        for (int i = 0; i < n; ++i) {
            cur = in.readLine().split(" ");
            for (int j = 0; j < m; ++j) {
                matrix[i][j] = Integer.parseInt(cur[j]);
            }
        }
        
        int sum = 0, area = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (!st[i][j]) {
                    area = Math.max(area, bfs(i, j));
                    sum++;
                }
            }
        }
        System.out.println(sum);
        System.out.println(area);
    }
}
```

### [1106. 山峰和山谷](https://www.acwing.com/problem/content/1108/)

```java
import java.io.*;
import java.util.*;

class Main {
    static int N = 1010;
    static int[][] matrix = new int[N][N];
    static boolean[][] st = new boolean[N][N];
    static int n;
    static boolean isHigher, isLower;
        
    public static void bfs(int x, int y) {
        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{x, y});
        while (!queue.isEmpty()) {
            int[] cur = queue.poll();
            x = cur[0];
            y = cur[1];
            for (int i = x - 1; i <= x + 1; ++i) {
                for (int j = y - 1; j <= y + 1; ++j) {
                    if (i == x && j == y) continue;
                    if (i < 0 || i >= n || j < 0 || j >= n) continue;
                    if (matrix[i][j] != matrix[x][y]) {
                        if (matrix[i][j] > matrix[x][y]) isHigher = true;
                        else isLower = true;
                    } else if (!st[i][j]) {
                        queue.offer(new int[]{i, j});
                        st[i][j] = true;
                    }
                }
            }
        }
    }
    
    public static void main(String[] args) throws IOException{
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        n = Integer.parseInt(in.readLine());
        for (int i = 0; i < n; ++i) {
            String[] cur = in.readLine().split(" ");
            for (int j = 0; j < n; ++j) {
                matrix[i][j] = Integer.parseInt(cur[j]);
            }
        }
        
        int high = 0, low = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (!st[i][j]) {
                    isHigher = false;
                    isLower = false;
                    bfs(i, j);
                    if (!isHigher) high++;
                    if (!isLower) low++;
                }
            }
        }
        System.out.println(high + " " + low);
    }
}
```







