---
tags:
  - 算法
  - 数据结构
  - 图论
  - 单源最短路
---
# 1. Bellman-Ford

当图中出现了负权边的时候，Dijkstra会不管用，因为Dijk本质上是贪心，就没办法处理边权为负数的情况。

#### 最短路

我们定义 `dis[u]` 是 $u$ 到起点的最短距离，对于图中的每一条边 $(u,v,w)$，我们都尝试更新 `dist[v] = min(dist[v] , dist[u] + w )` ，这对应一次松弛操作。

这样暴力解决，对于任何没有负环的图，跑完所有的边所有的点的 dist 值就一定是最终的最短路结果。

这种遍历每一个边的方法时间复杂度是 $O(NM)$ 。

#### 负环的判断

在执行BellmanFord之前，需要判断图内是否存在负权的回路（负环）。

如果存在负环，在环内绕圈会让路径无限变小，此时是不存在最短路的，即能一直执行松弛操作。
又由于对于最短路存在的图我们只需要执行 n-1 次松弛操作，那么在我们执行第 n 次循环的时候仍出现能够松弛的边，说明存在了负环。

```cpp
#include <iostream>
#include <vector>

using namespace std;

const int INF = 0x3f3f3f3f;

int n, m;
struct Edge {
    int u, v, w;
};
vector<Edge> edges(m);
vector<int> dist(n + 1, INF);

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    dist[1] = 0; //起点为1
    // 执行 n-1 次全图松弛
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (dist[edges[j].u] != INF && dist[edges[j].v] > dist[edges[j].u] + edges[j].w) {
                dist[edges[j].v] = dist[edges[j].u] + edges[j].w;
            }
        }
    }
    // 第 n 次判定
    bool has_negative_cycle = false;
    for (int j = 0; j < m; j++) {
        if (dist[edges[j].u] != INF && dist[edges[j].v] > dist[edges[j].u] + edges[j].w) {
            has_negative_cycle = true;
            break;
        }
    }
    if (has_negative_cycle) cout << "Impossible" << endl;
    else {
        // 输出 dist[n] 即可
    }
}
```

# 2. SPFA

SPFA 是 Shortest Path Faster Algorithm 的缩写。

很明显Bellman-Ford 的 $O(NM)$ 的复杂度还是太慢了，我们看看哪里还能优化。

考虑到当在循环中点 $u$ 没有被更新的时候，说明 $u$ 的邻居 $v$ 的最短路也不会变，此时我们理应不需要再去执行一次松弛操作，但是在 Bellman-Ford 中，我们实际还是执行了这个松弛操作的，造成了时间浪费。

根据这个表述，我们知道，只有这个点的最短路被更新了，才能通过这个点去更新其他与之相连的点。

那么我们考虑优化这一点，尝试维护一个队列，用于存储被更新过的点

当我们每次拿出一个点 $u$ 的时候就扫描 $u$ 的邻居 $v$，如果通过 $u$ 能让 `dist[v]` 变短，且 $v$ 不在队列里，就把 $v$ 推进队列。

这就是优化后的Bellman-Ford，即SPFA。

那么使用SPFA怎么判断负环呢？
一个点最多被推入队列 n 次，如果发现某个点入队超过 n 次，就说明有负环，因此使用SPFA的时候我们也要维护每个点的入队次数。

```cpp
int dist[N], cnt[N]; // cnt 用于记录入队次数，判断负环
bool in_que[N];     // 记录点是否已经在队列中

bool spfa(int n, int s) {
    fill(dist, dist + n + 1, INF);
    dist[s] = 0;
    queue<int> q;
    q.push(s);
    in_que[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_que[u] = false;

        for (auto& e : adj[u]) {
            if (dist[e.to] > dist[u] + e.w) {
                dist[e.to] = dist[u] + e.w;
                // 如果发现某个点入队超过 n 次，说明有负环
                if (++cnt[e.to] >= n) return false; 
                if (!in_que[e.to]) {
                    q.push(e.to);
                    in_que[e.to] = true;
                }
            }
        }
    }
    return true;
}
```

# 3. SPFA 的局限性

虽然 SPFA 能够将理论的时间复杂度压缩到 $O(kM)$ ，但是在一些特殊情况下，构造一些特殊的图就可以让 SPFA 的时间复杂度中的 k 很大，爆到 $O(NM)$ 。