---
tags:
  - 算法
  - 数据结构
  - 图论
  - 全源最短路
---

# 1. Johnson
Johnson是一种能够求出无负环图上任意两点间最短路径的算法。

和 Floyd 类似，用于解决全源最短路，那么对于 $n$ 个点跑 Bellman-Ford 时间复杂度是 $O(n^2m)$ 。

那么我们注意到 [[105-2 最短路-Dijkstra| Dijkstra]] 比 Bellman-Ford 更快，假如我们对每一个点跑 优化后的 Dijkstra，那么时间复杂度可以被压到 $O(nmlogm)$ 。

但是问题来了，Dijkstra 处理不了负权边，因此我们要对边权进行预处理使其非负。

我们容易想到给所有的边都加一个正数 $x$ 使边权非负，那么我们只需要在计算的时候减去 $kx$（$k$ 为边数）即可得到实际的路径。

但是很明显这样计算会有 Bug，因为对于一条边数很多的路径（数量为 $k$ ），将边权同时加 $x$ 的代价 $kx$ 是巨大的，这会导致边数更小的路径更具有数量优势。

Johnson算法是这样解决的：

1. 建立一个超级原点，编号为 $0$，从这个点向其他所有点连一条边权为 $0$的边 。
2. 接下来用Bellman-Ford求点 $0$ 到其他所有点 $i$ 的最短路，记为 $h_i$ 。
3. 假如存在一条 $u$ 到 $v$ 的边权为 $w$ 的边，那么我们将边的边权设置为 $w+h_{u}-h_{v}$ 。

此时我们就能保证每条边的边权为正，就可以对每个点跑 Dijkstra 了。

时间复杂度是严格的 $O(nmlogm)$ 。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n,m;
vector<pair<int,int>> g[3005];
ll h[3005],d[3005];
bool vis[3005];
queue<int> q1;
priority_queue<pair<int,int>> q2;
bool has_negative_ring = false;

void spfa() {
    for (int i = 1 ; i <= n  ; i++) {
        q1.push(i);
        vis[i] = true;
    }
    int cnt = 0;
    while (!q1.empty()) {
        cnt++;
        if (cnt > 5e6) {
            has_negative_ring = true;
            return;
        }
        int x = q1.front();
        q1.pop();
        vis[x] = false;
        for (auto [y,w] : g[x]) {
            if (h[y] <= h[x] + w) continue;
            h[y] = h[x] + w;
            if (vis[y]) continue;
            q1.push(y);
            vis[y] = true;
        }
    }
}

void dijk(int start) {
    memset(vis,0,sizeof vis);
    memset(d,0x3f,sizeof d);
    d[start] = 0;
    q2.push({0ll,start});
    while(!q2.empty()) {
        auto [nd,x] = q2.top();
        q2.pop();
        if (vis[x]) continue;
        vis[x] = true;
        for (auto [y,w] : g[x]) {
            if (vis[y] || d[y] <= d[x] + w + h[x] - h[y]) continue;
            d[y] = d[x] + w + h[x] - h[y];
            q2.push({-d[y],y});
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1 ; i <= m ; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        g[u].push_back({v,w});
    }
    spfa();
    if (has_negative_ring) {
        cout << -1 << endl;
        return 0;
    }
    for (int i = 1 ; i <= n ; i++) {
        dijk(i);
        ll ans = 0;
        for (int j = 1; j <= n ; j++) {
            ans += j * min((ll)1e9,d[j]-h[i]+h[j]);
        }
        cout << ans << endl;
    }
}
```