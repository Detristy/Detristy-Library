#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 3e5+10;
constexpr int M = 20;
constexpr int K = 50;
constexpr int MOD = 998244353;
int n,m;
vector<int> g[N];
int dep[N];
int f[N][M+10];
int sumD[N][K+10];

void dfs(int u,int fa) {
    dep[u] = dep[fa] + 1;
    f[u][0] = fa;
    for (int i = 1 ; i <= M ; ++i) {
        f[u][i] = f[f[u][i-1]][i-1];
    }
    int pow = 1;
    for (int i = 1 ; i <= K ; i++) {
        pow = (pow * (dep[u]-1)) % MOD;
        sumD[u][i] = (sumD[fa][i] + pow) % MOD;
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

void solve() {
    cin >> n;
    for (int i = 1 ; i < n ; i++) {
        int u,v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1,0);
    cin >> m;
    for (int i = 1 ; i <= m ; i++) {
        int u,v,k;
        cin >> u >> v >> k;
        int lca = LCA(u,v);
        int ans = ((sumD[u][k] + sumD[v][k] - sumD[lca][k] - sumD[f[lca][0]][k]) % MOD + MOD) % MOD;
        cout << ans << endl;
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
