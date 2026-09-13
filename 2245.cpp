#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

constexpr int N = 2e5+10;
constexpr int M = 20;
int n,m,q;
int fath[N];

int nodeCnt;
int val[N];

int f[N][M+10];
int dep[N];

struct Edge {
    int u,v,w;
};

vector<Edge> edges;
vector<int> g[N];

bool cmp(Edge e1,Edge e2) {
    return e1.w < e2.w;
}

int find(int x) {
    return x == fath[x] ? x : fath[x] = find(fath[x]);
}

void dfs(int u,int fa) {
    dep[u] = dep[fa]+1;
    f[u][0] = fa;
    for (int i = 1 ; i <= M ; i++) {
        f[u][i] = f[f[u][i-1]][i-1];
    }
    for (auto v : g[u]) {
        dfs(v,u);
    }
}

int lca(int u,int v) {
    if (dep[u] < dep[v]) swap(u,v);
    for (int i = M ; i >= 0 ; i--) {
        if (dep[f[u][i]] >= dep[v]) {
            u = f[u][i];
        }
    }
    if (u == v) return u;
    for (int i = M ; i >= 0 ; i--) {
        if (f[u][i] != f[v][i]) {
            u = f[u][i];
            v = f[v][i];
        }
    }
    return f[u][0];
}

void reKruskal() {
    sort(edges.begin(), edges.end(), cmp);
    nodeCnt = n;
    for (auto [u,v,w] : edges) {
        if (find(u) != find(v)) {
            nodeCnt++;
            val[nodeCnt] = w;
            int fu = find(u);
            int fv = find(v);
            fath[fu] = fath[fv] = nodeCnt;
            g[nodeCnt].push_back(fu);
            g[nodeCnt].push_back(fv);
        }
        if (nodeCnt == 2*n-1) return;
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 1 ; i <= 2*n ; i++) {
        fath[i] = i;
    }
    for (int i = 1 ; i <= m ; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        edges.push_back({u,v,w});
    }
    reKruskal();
    for (int i = 1 ; i <= nodeCnt ; i++) {
        if (fath[i] == i && dep[i] == 0) {
            dfs(i,0);
        }
    }
    cin >> q;
    while (q--) {
        int a,b;
        cin >> a >> b;
        if (find(a) != find(b)) {
            cout << "impossible" << endl;
        }
        else cout << val[lca(a,b)] << endl;
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
