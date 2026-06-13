---
tags:
  - 算法
  - 数据结构
  - 图论
  - 动态规划
  - 全源最短路
---
# 1. Floyd
Floyd用于解决全源最短路的问题。

当我们跑完Floyd的时候，我们就能直到图中任意两点 (i,j) 的距离，时间复杂度是 $O(n^3)$ 。

我们定义 $d[i]$ 是点 $i$ 到 $j$ 的最短距离（通过邻接矩阵实现），初始时我们判断两点是否相邻，如果是，那么 $d[i]$ 就等于连接两点的边的边权，否则就是 INF 。

这是初始化的操作，核心部分涉及三层循环：

1. 最外层（k）：代表当前需要经过的中间点
2. 中间层（i）：起点
3. 最内层（j）：终点

状态转移方程如下：

$$  
d_k[i][j] = min(d_{k-1}[i][j], d_{k-1}[i][k] + d_{k-1}[k][j])  
$$

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int INF = 1e9;
const int N = 105;
int d[N][N],n,m;

int main() {
    cin >> n >> m;
    for (int i = 1 ; i <= n ; i++) {
        for (int j = 1 ; j <= n ; j++) {
            if (i == j) d[i][j] = 0;
            else d[i][j] = INF;
        }
    }
    //初始化，如果两点相邻就直接讲最短距离赋值为边权
    for (int i = 1 ; i <= m ; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        d[u][v] = min(d[u][v],w);
        d[v][u] = min(d[v][u],w);
    }
    //floyd部分
    for (int k = 1 ; k <= n ; k++) {
        for (int i = 1 ; i <= n ; i++) {
            for (int j = 1 ; j <= n ; j++) {
                if (d[i][k] != INF && d[k][j] != INF) {
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }
    for (int i = 1 ; i <= n ; i++) {
        for (int j = 1 ; j <= n ; j++) {
            cout << d[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
```

# 2. Warshall 与 传递闭包

Warshall算法可以用于求取传递闭包。

我们知道偏序关系是具有传递性的，放在有向图中即如果 $i$ 能到达 $k$，且 $k$ 能到达 $j$ ，那么 $i$ 就能到达 $j$，状态转移方程如下：

$$  
dp[i][j] = dp[i][j]\ | (dp[i][k] \&dp[k][j])  
$$

这里用到位运算是因为我们求取传递闭包只需关注两点间是否联通，即联通或不连通，用 1 和 0 表示，于是我们只需要对这个结果进行逻辑运算即可。

```cpp
for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] |= dp[i][k] & dp[k][j];
        }
    }
}
```