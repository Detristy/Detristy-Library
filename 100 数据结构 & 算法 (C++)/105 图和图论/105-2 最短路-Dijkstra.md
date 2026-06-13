---
tags:
  - 算法
  - 数据结构
  - 图论
  - 单源最短路
aliases:
  - 迪杰斯特拉
---
# 1. 朴素 Dijkstra
Dijkstra用于解决单源最短路的问题。

我们假设 $root$ 连接着 $u$ 和 $v$，$u$ 连接着 $v$。从给定的节点 $root$ 出发，遍历邻接表，记录维护边权，并找边权最短的一个节点，假设是节点 $u$ 。
接下来我们继续从 $u$ 开始找，如果我们发现 $root$ 经过 $u$ 到 $v$ 的距离比 $root$ 直接去 $v$ 更短，我们就更新这个最短的距离。

```cpp
int x = s;
    for (int i = 1 ; i < n ; i++) {
        for (auto it: g[i]) {
            int y = it.first;
            int w = it.second;
            if (vis[y] || dis[y] <= dis[x] + w) continue;
            dis[y] = dis[x] + w;
        }
        /*
        我们从距离根节点最短那个点开始遍历，
        但是我们要找到距离根节点最短的那个点
        */
        int to = 0;
        for (int j = 1 ; j <= n ; j++) {
            if (vis[j]) continue;
            if (to && dis[to] <= dis[j]) continue;
            to = j;
        }
        x = to;
        vis[x] = true;
    }
```

# 2. 堆优化 Dijkstra
观察朴素 Dijkstra 算法，我们可以在取最小值这个部分做文章：

```cpp
		int to = 0;
        for (int j = 1 ; j <= n ; j++) {
            if (vis[j]) continue;
            if (to && dis[to] <= dis[j]) continue;
            to = j;
        }
```

考虑使用[[103-4B 优先队列|优先队列]]，此时能够保证每一次选择的都是距离最短的那个点作为扩散源，而优先队列默认用的是大根堆，我们要用的是小根堆，解决这个问题的方法是将点推入队列的时候，将距离取负，这样就能保证距离的绝对值是从小到大排序了。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n,m,s;
const int N = 1e5+10;
vector<pair<int,int>> g[N];
int dis[N];
bool vis[N];
priority_queue<pair<int,int>> q;

int main() {
    memset(dis,0x3f,sizeof(dis));
    cin >> n >> m >> s;
    dis[s] = 0;
    for (int i = 1 ; i <= m ; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        g[u].push_back({v,w});
    }
    q.push({0,s});
    while (!q.empty()) {
        auto it = q.top();
        q.pop();
        int nd = it.first; //nd : negative_distance
        int x = it.second;
        vis[x] = true;
        for (auto i : g[x]) {
            int y = i.first;
            int w = i.second;
            if (vis[y] || dis[y] <= dis[x] + w) continue;
            dis[y] = dis[x] + w;
            q.push({-dis[y],y});
        }
    }
    for (int i = 1 ; i <= n ; i++) {
        if (dis[i] > 1e10) cout << ((1ll<<31)-1)<<' ';
        else cout << dis[i] << ' ';
    }
    return 0;
}
```

```cpp
void Dijkstra(){
	q.push({0,s});
	while (!q.empty()) {
        auto [nd,x] = q.top();
        q.pop();
        vis[x] = true;
        for (auto [y,w] : g[x]) {
            if (vis[y] || dis[y] <= dis[x] + w) continue;
            dis[y] = dis[x] + w;
            q.push({-dis[y],y});
        }
    }
}
```