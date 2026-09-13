#include <bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int N = 5e5+10;
const int M = 20;

vector<pair<int,int>> g[N];
pair<int,int> ed[N];
int disPt[N];
int f[N][M+1];
int disRt[N];
int dep[N];
int diff[N];
int lca[N];
int dfn[N];
int val[N];
int n,m;
int tot;

void dfs(int u,int fa,int d) {
    dep[u] = dep[fa] + 1;
    disRt[u] = disRt[fa] + d;
    val[u] = d;
    dfn[++tot] = u;
    f[u][0] = fa;
    for (int i = 1 ; i <= M ; ++i) {
        f[u][i] = f[f[u][i-1]][i-1];
    }
    for (auto [v,w] : g[u])
        if (v != fa)
            dfs(v,u,w);
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

bool check(int x) {
    int cnt = 0;
    int mxLen = 0;
    for (int i = 1 ; i <= n ; i++) diff[i] = 0;
    for (int i = 1 ; i <= m ; i++) {
        if (disPt[i] <= x) continue;
        int u = ed[i].first;
        int v = ed[i].second;
        cnt++;
        mxLen = max(mxLen,disPt[i]);
        diff[u]++;
        diff[v]++;
        diff[lca[i]] -= 2;
    }
    if (!cnt) return true;
    int mxw = 0;
    for (int i = n ; i >= 1 ; i--) {
        int u = dfn[i];
        diff[f[u][0]] += diff[u];
        if (diff[u] == cnt) {
            mxw = max(mxw,val[u]);
        }
    }
    if (mxLen - mxw <= x) return true;
    return false;
}

int dist(int u,int v,int lca) {
    return disRt[u] + disRt[v] - 2 * disRt[lca];
}

void solve() {
    cin >> n >> m;
    for (int i = 1 ; i < n ; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }
    int mx = 0;
    dfs(1,0,0);
    for (int i = 1 ; i <= m ; i++) {
        cin >> ed[i].first >> ed[i].second;
        lca[i] = LCA(ed[i].first,ed[i].second);
        disPt[i] = dist(ed[i].first,ed[i].second,lca[i]);
        mx = max(mx,disPt[i]);
    }
    int l = 0,r = mx,ans = 0;
    while (l <= r) {
        int mid = (l+r)/2;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    cout << ans << endl;
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