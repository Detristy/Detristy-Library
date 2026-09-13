#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 1e5+10;
constexpr int M = 20;
int n,m;
bool isG[N];
vector<int> g[N];
int dep[N];
int f[N][M+5];
int cntG[N],cntH[N];

void dfs(int u,int fa) {
    dep[u] = dep[fa] + 1;
    f[u][0] = fa;
    for (int i = 1 ; i <= M ; ++i) {
        f[u][i] = f[f[u][i-1]][i-1];
    }
    for (auto v : g[u]) if (v != fa) dfs(v,u);
}

void dfs2(int u,int fa) {
    if (isG[u]) cntG[u]++;
    else cntH[u]++;

    cntG[u] += cntG[fa];
    cntH[u] += cntH[fa];

    for (auto v : g[u]) {
        if (v != fa) dfs2(v,u);
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


void solve() {
    cin >> n >> m;
    for (int i = 1 ; i <= n ; i++) {
        char c;
        cin >> c;
        if (c == 'G') isG[i] = true;
        else isG[i] = false;
    }
    for (int i = 1 ; i < n ; i++) {
        int u,v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1,0);
    dfs2(1,0);
    for (int i = 1 ; i <= m ; i++) {
        int a,b; char c;
        cin >> a >> b >> c;
        if (c == 'G') {
            if (cntG[a] + cntG[b] - 2 * cntG[lca(a,b)] + (isG[lca(a,b)] ? 1 : 0) > 0) cout << 1;
            else cout << 0;
        }
        else if (c == 'H') {
            if (cntH[a] + cntH[b] - 2 * cntH[lca(a,b)] + (isG[lca(a,b)] ? 0 : 1)> 0) cout << 1;
            else cout << 0;
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
