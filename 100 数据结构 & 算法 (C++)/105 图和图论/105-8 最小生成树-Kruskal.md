---
tags:
  - 算法
  - 数据结构
  - 图论
  - 生成树
---
# 1. 最小生成树
最小生成树是边权和最小的生成树，要构造一颗最小生成树，不妨考虑贪心，将边权尽可能小的边加入生成树中。

因为最小生成树涉及两点通过一边合并的过程，因此用到 [[102-7 并查集|并查集]] 进行实现会更方便一些。

# 2. Kruskal
Kruskal 算法是一种常见并且好写的最小生成树算法，由 Kruskal 发明．该算法的基本思想是从小到大加入边，属于贪心算法。

#### 方法

Kruskal找最小生成树的方法如下：

1. 贪心：把边按边权从小到大排序；
2. 遍历：从边权最小的路开始查找；
3. 判断：如果两个点联通了（属于同一个根节点）那么跳过，如果没联通那么就将两个点联通。

此外，当边的数量等于 N-1 的时候，说明所有的点都被连起来了，此时就没有必要继续遍历了。
这里需要避免出现环，而我们判两点是否联通和判边数量是否等于N-1就能够实现最终的图中没有环。

这个算法的正确性证明见 [[100Ex-3 Kruskal 算法的正确性证明]] 。

#### 复杂度

Kruskal 的复杂度在 $O(n\log n)$ - $O(n^2\log n)$ 之间。

#### 代码实现

```cpp
#include <bits/stdc++.h>  
using namespace std;  
typedef long long ll;  
  
struct edge {  
    int u,v,w;  
};  
  
int n,m;  
const int N = 3e3+10;  
int fa[N];  
vector<edge> ed;  
  
//cmp函数  
bool cmp(edge a,edge b) {  
    return a.w < b.w;  
}  
  
int find(int x) {  
    return fa[x] == x ? x : fa[x] = find(fa[x]);  
}  
  
void uni(int x,int y) {  
    int rx = find(x);  
    int ry = find(y);  
    if (rx != ry) fa[rx] = ry;  
}  
  
int main() {  
    cin >> n >> m;  
      
    //初始化  
    for (int i = 1 ; i <= m ; i++) fa[i] = i;  
      
    //输入，然后直接pushback  
    for (int i = 1; i <= m ; i++) {  
        int u,v,w;  
        cin >> u >> v >> w;  
        ed.push_back({u,v,w});  
    }  
      
    //排序之后就能从小到大找了  
    sort(ed.begin(),ed.end(),cmp);  
    ll total = 0;  
    int cnt = 0;  
    for (auto &e : ed) {  
           //如果两个点不属于同一个集合，那么将他们连起来  
        if (find(e.u) != find(e.v)) {  
            uni(e.u,e.v);  
            cnt++;  
            total += e.w;  
            if (cnt == n-1) break;  
        }  
    }  
    cout << total << endl;  
}
```

#### 链式前向星实现
```cpp
#include<bits/stdc++.h>  
#define ll long long  
#define INF INT_MAX  
using namespace std;  
const int N = 2005;  
const int M = 3005;  
int ans = 0, sum = 0;  
int n, m;  

int fa[N]; //用来存储这个点的父节点 struct node{  
    int from, to, value;  
}edge[M << 1];   

bool cmp(node x, node y){ //定义排序函数   
	return x.value < y.value;  
}  

int find(int x){ //并查集，找到x的根节点   
	if(fa[x] != x) return fa[x] = find(fa[x]);  
	    return x;  
}  

void Kruskal(){ //Kruskal   
int tot = 0;  
    sort(edge + 1, edge + 1 + m, cmp); //将边权进行排序   
for(int i = 1; i <= m; i++){  
       int ft = find(edge[i].to);  
       int ff = find(edge[i].from); //分别找到这两个点的根节点   
if(ft != ff){ //如果不相同证明相连不会有环   
tot++; //计数器加一   
fa[ft] = ff; //将这两个点合并   
ans += edge[i].value; //答案加上这个点的值   
}  
       if(tot == n) break; //如果进行了n次合并，那么退出循环，已经构造出最小生成树了。   
}  
}  

int main(){  
    cin >> n >> m;  
    for(int i = 1; i <= n; i++) fa[i] = i; //最开始这个节点的父节点就是它自己   
	for(int i = 1; i <= m; i++){  
        cin >> edge[i].from >> edge[i].to >> edge[i].value;   
    }   
    Kruskal(); //进行Kruskal算法求解   
	cout << ans << endl; //输出答案   
	return 0;  
}
```