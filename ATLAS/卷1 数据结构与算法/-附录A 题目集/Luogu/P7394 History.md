---
tags:
  - 树状数组
  - 树
---
树状数组神题。

题目给出了三种操作，一一分解。

## 维护第二种操作

### 问题转化

首先对于第二种操作，考虑维护结点的深度 $dep$ ，那么结点 $x,y$ 之间的距离就是：

$$
dist(x,y)=dep[x]+dep[y]-2dep[lca(x,y)]
$$
由于 $x,y$ 深度相同，所以变形为：
$$
dist(x,y)=2(dep[x]-dep[lca(x,y)]) 
$$
令 $k=\frac{dist(x,y)}{2}$ ，那么我们就要求的就可以转化为 $x$ 的第 $k$ 个祖先的所有深度为 $dep[x]$ 的点。

第 $k$ 个祖先可以用倍增维护：

```cpp
int find(int u,int k) {  
    for (int i = 0 ; i <= M ; i++) {  
        if ((k >> i) & 1) {  
            u = f[u][i];  
        }  
    }  
    return u;  
}
```

### 将树映射到树状数组

接下来我们考虑如何把整棵树压缩到一个树状数组上进行查询。

首先考虑对树上结点求 DFN 序，这样我们就可以将子树上的结点映射为一个连续的区间。

顺便我们可以维护一个 `out[u]` 表示子树 DFN 序区间的右端点。

但是我们不能只考虑子树，我们还需要将子树内的点按所在的层数划分。

对结点按深度分组，用一个表 `pos` 来维护，每组按 DFN 升序排列。

接下来考虑如何利用树状数组存储所有层，设
- `base[d]` 表示深度小于 $d$ 的结点总数。
- `id[u]` 将结点 u 映射为树状数组的下标。
- `rk[u]` 表示同深度点中的编号。

那么我们可以直接建立一个映射：
$$
id[u] = base[dep[u]] + rk[u]
$$
然后 $base$ 可以进行转移：
$$
base[i] = base[i-1]+pos[d-1].size()
$$

`rk[u]` 实际上是特别好维护的，当 $u$ 加入对应深度的 pos 表的时候，此时 `rk[u]` 就是表中对应深度的大小。

```cpp
void DFS(int u,int fa) {  
    dfn[u] = ++cnt;  
    dfnToNd[cnt] = u;  
    dep[u] = dep[fa] + 1;  
  
    pos[dep[u]].push_back(dfn[u]);  
    rk[u] = pos[dep[u]].size();  
  
    f[u][0] = fa;  
    for (int i = 1 ; i <= M ; ++i) {  
        f[u][i] = f[f[u][i-1]][i-1];  
    }  
    for (auto v : g[u]) {  
        if (v != fa) {  
            DFS(v,u);  
        }  
    }  
    out[u] = cnt;  
}
```

### 灯的计数

定义 $F(u,d)$ 为 $u$ 的子树中深度为 $d$ 的亮灯个数，我们可以利用二分，在 `pos` 表中快速定位区间位置，然后加上 $base$ 的增量，对应的区间和就是亮灯数量（定义亮灯为 $1$ ，灭灯为 $0$）。

```cpp
int cntLight(int u,int d) {  
    if (u == 0 || d < 1 || d > n) {  
        return 0;  
    }  
    auto &vec = pos[d];  
    int l = lower_bound(vec.begin(),vec.end(),dfn[u]) - vec.begin();  
    int r = upper_bound(vec.begin(),vec.end(),out[u]) - vec.begin();  
    return t.query(base[d] + r) - t.query(base[d]+l);  
}
```

### 实现全部功能

```cpp
int querySum(int x,int y) {  
    if (y%2) {  
        return 0;  
    }  
    if (y == 0) {  
        return light[x];  
    }  
    int k = y/2;  
    if (k >= dep[x]) {  
        return 0;  
    }  
    int a = find(x,k);  
    int b = find(x,k-1);  
    return cntLight(a,dep[x]) - cntLight(b,dep[x]);  
}
```

## 维护第三种和第一种操作

对于回溯操作，我们可以维护一棵操作树，让第三种操作继承第 $x$ 次操作的状态。

接下来DFS操作树，进入结点时执行修改或者查询操作，加下来访问子结点，如果进行了修改，则在退出当前结点的时候撤销结点的修改操作。

第一种操作只需要简单反转即可。

```cpp
void DFS2(int u) {  
    if (op[u] == 1) {  
        t.add(id[X[u]],light[X[u]] ? -1 : 1);  
        light[X[u]] = !light[X[u]];  
    }  
    else if (op[u] == 2) {  
        ans[u] = querySum(X[u],Y[u]);  
    }  
    for (auto v : opT[u]) {  
        DFS2(v);  
    }  
    if (op[u] == 1) {  
        t.add(id[X[u]],light[X[u]] ? -1 : 1);  
        light[X[u]] = !light[X[u]];  
    }  
}
```

![[7394.cpp]]
