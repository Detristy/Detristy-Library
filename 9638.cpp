#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

constexpr int N = 8e5+10;
constexpr int M = 20;
int n,m,q;
vector<int> g[N];
int fath[N];
int nodeCnt; 
int val[N]; //编号->边权

int f[N][M+10]; //倍增表

int leafCnt[N]; //点编号 -> 叶子个数
int edgeToTree[N]; //边 -> 树上的点

//桶
int bucketEdge[N];
int bucketP[N];
int cntp = 0;

struct Edge {
    int u,v,w,id;
};

vector<Edge> edges;

bool cmp(Edge e1,Edge e2) {
    return e1.w > e2.w;
}

int find(int x) {
    return x == fath[x] ? x : fath[x] = find(fath[x]);
}

//倍增
void dfs(int u,int fa) {
    f[u][0] = fa;
    for (int i = 1 ; i <= M ; i++) {
        f[u][i] = f[f[u][i-1]][i-1];
    }
    for (auto v : g[u]) {
        dfs(v,u);
        leafCnt[u] += leafCnt[v];
    }
}

void reKruskal() {
    sort(edges.begin(), edges.end(), cmp);
    nodeCnt = n;
    for (auto [u,v,w,id] : edges) {
        if (find(u) != find(v)) {
            nodeCnt++;
            val[nodeCnt] = w;
            int fu = find(u);
            int fv = find(v);
            fath[fu] = fath[fv] = nodeCnt;
            edgeToTree[id] = nodeCnt;
            g[nodeCnt].push_back(fu);
            g[nodeCnt].push_back(fv);
        }
        if (nodeCnt == 2*n-1) return;
    }
}

int query(int u,int limit) {
    int cur = u;
    for (int i = M ; i >= 0 ; i--) {
        if (f[cur][i] && val[f[cur][i]] >= limit) {
            cur = f[cur][i];
        }
    }
    return leafCnt[cur];
}

void solve() {
    cin >> n >> m >> q;
    for (int i = 1 ; i <= 2*n ; i++) {
        fath[i] = i;
        val[i] = 0x3f3f3f3f3f3f3f3f;
        if (i > n) leafCnt[i] = 0;
        else leafCnt[i] = 1;
    }
    for (int i = 1 ; i <= m ; i++) {
        int x,y,k;
        cin >> x >> y >> k;
        edges.push_back({x,y,k,i});
    }
    reKruskal();
    for (int i = 1 ; i <= 2*n ; i++) {
        if (fath[i] == i) {
            dfs(i,0);
        }
    }
    int limit = 0;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            limit = x;
            //处理所有修改
            for (int i = 1 ; i <= cntp ; i++) {
                val[edgeToTree[bucketEdge[i]]] = bucketP[i];
            }
            cntp = 0;
        }
        else if (op == 2) {
            int x;
            cin >> x;
            cout << query(x,limit) << endl;
        }
        else if (op == 3) {
            int x,y;
            cin >> x >> y;
            //预存所有修改
            if (val[x] != 0) {
                bucketEdge[++cntp] = x;
                bucketP[cntp] = y;
            }
        }
    }
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    //cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
    return 0;
}