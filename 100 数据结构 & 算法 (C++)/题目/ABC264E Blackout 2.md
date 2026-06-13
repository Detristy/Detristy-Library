---
tags:
  - 并查集
Difficulty:
  - Green
---

# 链接

原题：
https://atcoder.jp/contests/abc264/tasks/abc264_e

洛谷：
https://www.luogu.com.cn/problem/AT_abc264_e

# 分析

## 简要分析

一道[[102-7 并查集]]题。

本题的核心操作为删边，然而并查集天然支持加边而不便于支持删边。注意到切断过程恰为合并过程的逆过程，故可采用**离线处理**的思路：先确定所有切断操作完成后的最终状态，再按时间逆序逐条将被切断的边重新加入并查集，并在每一步统计当前通电城市的数量；最后将结果反向输出即可。

## 详细推导

首先观察到一条性质：对于任意一座城市，只要其所在连通分量中存在至少一座发电站，则该城市必然处于通电状态。由此可见，所有发电站在连通性意义下彼此等价，故可将其统一抽象为一个虚拟结点，约定其编号为 $n+1$。

读入全部询问后，对其中所涉及的每一条边打上"被切断"的标记。

接下来进入并查集的构建阶段。约定如下记号：

- $\mathit{siz}[i]$ 表示以 $i$ 为根的连通分量中所含**城市**的数量。初始时每座城市自成一个连通分量，即对任意 $i \in [1, n]$，有 $\mathit{siz}[i] = 1$。
- $\mathit{cnt}$ 表示当前处于通电状态的城市总数。

遍历所有未被标记的边 $(u, v)$，分别求出 $u, v$ 所在连通分量的根 $f_u, f_v$。当 $f_u \neq f_v$ 时，依据两端的属性进行分类讨论：

1. $f_u, f_v$ 中恰有一者为发电站结点（即 $n+1$），另一者为城市。此时被合并的整个城市侧连通分量将随之通电，故应执行 $\mathit{cnt} \mathrel{+}= \mathit{siz}[\text{城市侧根}]$。
2. 两端的根均为发电站或均为城市。此情形下不会产生新的通电城市。

完成上述判定后，再将 $u, v$ 所在的两个连通分量合并。

> [!faq] 合并操作的注意点
> 合并时应将**编号较小**的根并入**编号较大**的根。如此可保证编号最大的结点 $n+1$（即发电站）始终作为其所在连通分量的根，便于后续判定连通分量的属性。具体实现上仅需在合并前增加一行 `if (u < v) swap(u, v);`。
>
> 此外，合并时务必同步更新 $\mathit{siz}$ 数组：`siz[u] += siz[v];`。

执行至此，$\mathit{cnt}$ 即为所有标记边均被切断后的通电城市数量。

随后按询问的逆序，将被切断的边逐条加回并查集。**在加入每条边之前**先记录当前的 $\mathit{cnt}$ 作为该次询问的答案，加入操作的处理逻辑与上文完全一致。由于答案是按倒序生成的，最终输出时需将其反转。

# 代码

合并部分的逻辑存在重复，实际编码中可将其封装为函数以提升可读性。

```cpp
#include<bits/stdc++.h>  
using namespace std;    
#define int long long    
    
constexpr int N = 5e5+10;    
int n,m,q,e;    
int fa[N],del[N],siz[N];    
pair<int,int> ed[N];    
bool vis[N];    
    
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }  
    
void solve() {    
    cin >> n >> m >> e;    
    for (int i = 1 ; i <= n+m ; i++) fa[i] = i;    
    for (int i = 1 ; i <= n ; i++) siz[i] = 1;    
    for (int i = 1 ; i <= e ; i++) {    
        int u,v;    
        cin >> u >> v;    
        if (u > n) u = n+1;    
        if (v > n) v = n+1;    
        ed[i]={u,v};    
    }    
    cin >> q;    
    for (int i = 1 ; i <= q ; i++) {    
        cin >> del[i];    
        vis[del[i]] = true;    
    }    
    int cnt = 0;    
    for (int i = 1 ; i <= e ; i++) {    
        if (!vis[i]) {    
            auto [u,v] = ed[i];    
            if (find(u) != find(v)) {    
                u = find(u); v = find(v);  
                if (u > n && v <= n) cnt += siz[v];  
                if (v > n && u <= n) cnt += siz[u];  
                if (u < v) swap(u,v);    
                fa[v] = u;    
                siz[u] += siz[v];    
            }    
        }    
    }    
    vector<int> ans;    
    for (int i = q ; i >= 1 ; i --) {    
        ans.push_back(cnt);    
        auto [u,v] = ed[del[i]];    
        if (find(u) != find(v)) {    
            u = find(u);    
            v = find(v);    
            if (u > n && v <= n) cnt += siz[v];  
            if (v > n && u <= n) cnt += siz[u];  
            if (u < v) swap(u,v);    
            fa[v] = u;    
            siz[u] += siz[v];    
        }    
    }    
    reverse(ans.begin(),ans.end());    
    for (auto x : ans) cout << x << '\n';    
}    
    
signed main() {    
    ios::sync_with_stdio(false);    
    cin.tie(NULL);    
    
    int T = 1;    
    //cin >> T;    
	while (T--) solve();    
    return 0;    
}
```
