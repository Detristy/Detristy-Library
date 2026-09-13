#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 1e5+10;
constexpr int MOD = 998244353;
int n,q;
int w[N];
vector<int> g[N];
int father[N];
int dep[N];
int siz[N];
int son[N];
int top[N];
int dfn[N],cntDfn = 0;
int seg[N];

struct segmentTree {
    int tree[N*4];
    int mx[N*4];
    void build(int x = 1,int l = 1,int r = n) {
        if (l == r) {
            tree[x] = w[seg[l]];
            mx[x] = w[seg[l]];
            return;
        }
        int mid = (l+r)/2;
        build(x*2,l,mid);
        build(x*2+1,mid+1,r);
        tree[x] = tree[2*x] + tree[2*x+1];
        mx[x] = max(mx[x*2],mx[x*2+1]);
    }
    void mergeP(int pos,int val,int x = 1,int l = 1,int r = n) {
        if (l == r) {
            tree[x] = val;
            mx[x] = val;
            return;
        }
        int mid = (l+r)/2;
        if (pos <= mid) mergeP(pos,val,x*2,l,mid);
        else mergeP(pos,val,x*2+1,mid+1,r);
        tree[x] = tree[x*2] + tree[x*2+1];
        mx[x] = max(mx[x*2],mx[x*2+1]);
    }
    int querySUM(int ql,int qr,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) return tree[x];
        int mid = (l+r)/2;
        int ans = 0;
        if (ql <= mid) ans = (ans + querySUM(ql,qr,x*2,l,mid))  ;
        if (mid < qr) ans = (ans + querySUM(ql,qr,x*2+1,mid+1,r))  ;
        return ans;
    }
    int queryMAX(int ql,int qr,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) return mx[x];
        int mid = (l+r)/2;
        int ans = -1e18;
        if (ql <= mid) ans = max(ans, queryMAX(ql,qr,x*2,l,mid))  ;
        if (mid < qr) ans = max(ans, queryMAX(ql,qr,x*2+1,mid+1,r))  ;
        return ans;
    }
}T;

void pointChange(int u,int v) { T.mergeP(dfn[u],v); }

int pathSum(int u,int v) {
    int ans = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] >= dep[top[v]]) {
            ans = ans+T.querySUM(dfn[top[u]],dfn[u]);
            u = father[top[u]];
        }
        else {
            ans = ans+T.querySUM(dfn[top[v]],dfn[v]);
            v = father[top[v]];
        }
    }
    ans = ans+T.querySUM(min(dfn[u],dfn[v]),max(dfn[u],dfn[v]));
    return ans;
}

int pathMax(int u,int v) {
    int ans = -1e18;
    while (top[u] != top[v]) {
        if (dep[top[u]] >= dep[top[v]]) {
            ans = max(ans , T.queryMAX(dfn[top[u]],dfn[u]))  ;
            u = father[top[u]];
        }
        else {
            ans = max(ans , T.queryMAX(dfn[top[v]],dfn[v]))  ;
            v = father[top[v]];
        }
    }
    ans = max(ans ,T.queryMAX(min(dfn[u],dfn[v]),max(dfn[u],dfn[v])))  ;
    return ans;
}

void DFS1(int u,int fa) {
    father[u] = fa;
    dep[u] = dep[fa] + 1;
    siz[u] = 1;
    for (auto v : g[u]) {
        if (v == fa) continue;
        DFS1(v,u);
    }
    for (auto v : g[u]) {
        if (v == fa) continue;
        siz[u] += siz[v];
        if (son[u] == 0 || siz[v] > siz[son[u]]) son[u] = v;
    }
}

void DFS2(int u,int tp) {
    top[u] = tp;
    dfn[u] = ++cntDfn;
    seg[cntDfn] = u;
    if (son[u] == 0) return;
    DFS2(son[u],tp);
    for (auto v : g[u]) {
        if (v == father[u] || v == son[u]) continue;
        DFS2(v,v);
    }
}

void solve() {
    cin >> n;
    for (int i = 1 ; i < n ; i++) {
        int u,v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1 ; i <= n ; i++) cin >> w[i];
    DFS1(1,0); DFS2(1,1);
    T.build();
    cin >> q;
    while (q--) {
        string op; cin >> op;
        if (op == "CHANGE") {
            int u,t; cin >> u >> t;
            pointChange(u,t);
        }
        else if (op == "QMAX") {
            int u,v; cin >> u >> v;
            cout << pathMax(u,v) << endl;
        }
        else if (op == "QSUM") {
            int u,v; cin >> u >> v;
            cout << pathSum(u,v) << endl;
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
