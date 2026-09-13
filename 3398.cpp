#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 1e5+10;
constexpr int M = 20;
int n,q;
vector<int> g[N];
int dep[N];
int f[N][M+5];
int diff[N];

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
    return dep[u]+dep[v]-2*dep[LCA(u,v)];
}

void solve() {
    cin >> n >> q;
    for (int i = 1; i < n ; i++) {
        int x,y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs(1,0);
    for (int i = 1 ; i <= q ; i++) {
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        int lca1 = LCA(a,b);
        int lca2 = LCA(c,d);
        bool flag = false;
        if (dist(lca2,a)+dist(lca2,b) == dist(a,b)) flag =true;
        if (dist(lca1,c)+dist(lca1,d) == dist(c,d)) flag = true;

        if (flag) cout << "Y" << endl;
        else cout << "N" << endl;
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
