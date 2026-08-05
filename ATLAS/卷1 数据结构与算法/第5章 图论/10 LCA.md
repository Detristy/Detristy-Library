---
tags:
  - 算法
  - 图论
  - LCA
---
# 1. LCA的概念
LCA 指的是树上两点的最近的公共祖先，解决这个问题可以使用树上倍增 和 tarjan，不过这里先介绍树上倍增的方法。

# 2. 树上倍增
我们在树上跑倍增过程，也就是按照倍增的步数从该节点开始向上查找。

在实现树上倍增之前，我们需要一些准备工作：

1. 定义 $d_i$ 为节点 $i$ 的层数。从而，若 $i$ 是 $j$ 的儿子，则 $d_i=d_j+1$；
2. 定义 $f[i][p]$ 为节点 $i$ 向上走 $2^p$ 步可以到达的节点，其中显然 $f[1][0]$ 是 $i$ 的父节点。其实和ST表很相似，我们可以通过这个定义推出这么一条性质： $f[i][p]=f[f[i][p-1]][p-1]$。

通过上面的准备工作我们就能实现在 $O(\log n)$ 内实现查询从 $i$ 节点向上走的路径中位于第 $s$ 层的节点编号。

这两个数组我们需要 DFS 遍历整张图进行预处理，其中 $f$ 的预处理时间复杂度为 $O(n\log n)$ 。

# 3. 树上倍增解决LCA
我们假设此时我们已经处理出了 $d$ 数组和 $f$ 数组。

假设要求 $a$ 和 $b$ 的最近公共祖先，我们使用树上倍增解决 LCA 的思路如下：

1. 先让 $a$ 和 $b$ 来到同一层；
2. 接着让 $a$ 和 $b$ 一起往上走，在过程中保证各自到达的节点均不同（注意需要特殊处理 $y$ 就是 $x$ 的祖先的情况，反之亦然）；
3. 跑完过程 2 后，两个节点在往上走 1 步就可以到达两点的最近公共祖先。

单次查询的时间复杂度为 $O(\log n)$ 。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 5e5+10;
const int M = 20;

vector<int> g[N];
int f[N][M+1];
int dep[N];
int n,m,s;

void dfs(int u,int fa) {
   dep[u] = dep[fa] + 1;
   f[u][0] = fa;
   for (int i = 1 ; i <= M ; ++i) {
      f[u][i] = f[f[u][i-1]][i-1]; //树上倍增预处理所有的 u 能通过 2^i 步能到达的节点
   }
   for (auto v : g[u]) if (v != fa) dfs(v,u);
}

int lca(int u,int v) {
   if (dep[u] < dep[v]) swap(u,v);
   
   //让 u 和 v 到达同一层
   for (int i = M ; i >= 0 ; i--) {
      if (dep[f[u][i]] >= dep[v]) {
         u = f[u][i];
      }
   }
   if (u == v) return u;
   
   //两个点一起向上跑
   for (int i = M ; i >= 0 ; i--) {
      if (f[u][i] != f[v][i]) {
         u = f[u][i];
         v = f[v][i];
      }
   }
   
   //此时两个节点任意一个的父节点就是他们的LCA
   return f[u][0];
}

int main() {
   cin >> n >> m >> s;
   for (int i = 1 ; i < n ; i++) {
      int u,v;
      cin >> u >> v;
      g[u].push_back(v);
      g[v].push_back(u);
   }
   dfs(s,0);
   while (m--) {
      int a,b;
      cin >> a >> b;
      cout << lca(a,b) << endl;
   }
}
```