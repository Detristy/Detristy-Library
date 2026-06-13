---
tags:
  - 算法
  - 数据结构
  - 图论
  - 生成树
---
# 1. Prim
Prim算法适用于稠密图，因为Prim的复杂度基本维持在 $O(n^2)$ ，而面对稠密图，Kruskal的复杂度会到 $O(n^2logn)$ ，此时Prim是占优势的。

Prim的大致步骤如下：

首先我们初始化，我们假设所有的点都是与我们要找的最小生成树是不连通的，即距离最小生成树的根节点无穷远 `dist[i] = INF`
特殊地，根节点距离自己为 0，在接下来的遍历中，我们也使用距离为 0 来描述节点在我们要找的最小生成树里

接着我们从根节点开始遍历，每一次遍历我们要完成几项任务：

1. 定义我们此时所在的节点为 $now$
2. 我们通过邻接表遍历所有和 $now$ 相邻的节点 $u$，查找有没有离树更近的节点，假设从 $now$ 到 $u$ 的边的边权为 $w$
    1. 我们要判断这个节点是否在树里，如果在树里 `dist[u]==0` ，显然我们就不用找这个节点，直接跳过
    2. 我们还要判断原来的距离和现在的距离的大小关系：如果 `dist[u]`（原来的距离）比现在的边权（$w$）还短，那我明显是要距离更小的那个，所以也不需要更新距离了，直接跳过
    除去了跳过的，剩下的就是我们要查找的点，我们记录 u 和最小生成树间的距离就是此时 $u$ 和 $now$ 两点间边的边权，接着我们记录一下 u 的父节点此时是 $now$
3. 我们接下来要连线，找一个还没拉进最小生成树并且距离最近的点
    我们从根节点开始扫描整张图的节点 $i$ ，定义我们最终要找的目标节点是 $next$ ，赋值为 0
    1. 如果点已经在最小生成树里，明显不需要再拉进来了，跳过
    2. 如果 $next$ 此时不为 0，并且 `dis[i] ≥ dist[next]` ，说明点 $i$ 不是最近的，至少比 $next$ 距离要远，跳过
    假如 i 通过了上面两轮筛选，那么我们假定 $next$ 就是此时的 $i$，接着我们继续筛
    这样能保证在遍历完全图之后，$next$ 就是我们要找的距离最小生成树最近的点，我们拉进来，即 `dist[next] = 0`，代表 $next$ 入树
4. 接下来我们更新 $now = next$ ，即代表接下来从 $next$开始搜索节点，接着加上边权即可。

#### 代码实现
```cpp
#include <bits/stdc++.h>  
#define int long long  
  
using namespace std;  
  
int n,m;  
int sum,cnt;  
vector<pair<int,int>> g[5005];  
int d[5005],f[5005];  
  
void Main() {  
    memset(d,0x3f,sizeof d);  
    d[1]=0;  
    cin>>n>>m;  
    for(int i = 1;i <= m;i ++)  
    {  
        int x,y,z;  
        cin>>x>>y>>z;  
        g[x].push_back({y,z});  
        g[y].push_back({x,z});  
    }  
    int now = 1;  
    for(int i = 1;i < n;i ++)  
    {  
        for(auto [y,z] : g[now])  
        {  
            if(!d[y] || d[y] <= z)continue;  
            d[y]=z;  
            f[y]=i;  
        }  
        int next = 0;  
        for(int i = 1;i <= n;i ++)  
        {  
            if(!d[i] || (next&&d[i]>=d[next]))continue;  
            next=i;          
        }  
        now=next;  
        sum+=d[now];  
        d[now]=0;  
    }  
    if(sum>0x3f3f3f3f3f3f3f3f)cout<<"orz";  
    else cout<<sum;  
}  
  
signed main(){  
    ios::sync_with_stdio(false);  
    cin.tie(nullptr);  
    cout.tie(nullptr);  
    int T = 1;  
//    cin>>T;  
    while(T--)Main();  
    return 0;  
}
```