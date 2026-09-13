#include <bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int N = 5e5+10;
const int M = 20;

vector<int> g[N];
int f[N][M+1];
int dep[N];
int n,m;

void dfs(int u,int fa) {
    dep[u] = dep[fa] + 1;
    f[u][0] = fa;
    for (int i = 1 ; i <= M ; ++i) {
        f[u][i] = f[f[u][i-1]][i-1];
    }
    for (auto v : g[u]) if (v != fa) dfs(v,u);
}

int LCA(int u,int v) {
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

int dist(int u,int v) {
    return dep[u] + dep[v] - 2 * dep[LCA(u,v)];
}

void solve() {
    cin >> n >> m;
    for (int i = 1 ; i < n ; i++) {
        int u,v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1,0);
    for (int i = 1 ; i <= m ; i++) {
        int x,y,z;
        cin >> x >> y >> z;
        int lca1 = LCA(x,y),
        lca2 = LCA(x,z),
        lca3 = LCA(y,z);
        //找三个lca深度最深的一个
        int lca = lca1;
        if (dep[lca2] >= dep[lca]) lca = lca2;
        if (dep[lca3] >= dep[lca]) lca = lca3;
        int ans = dist(x,lca) + dist(y,lca) + dist(z,lca);
        cout << lca << " " << ans << endl;
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