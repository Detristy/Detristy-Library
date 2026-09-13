#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 1e5+10;
int n,m,root,MOD;
int val[N];
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
    int lazy[N*4];
    void pushdown(int x,int l,int r) {
        if (!lazy[x]) return;
        int mid = (l+r)/2;
        tree[x * 2] = (tree[x * 2] + (mid - l + 1) * lazy[x]) % MOD;
        tree[x * 2 + 1] = (tree[x * 2 + 1] + (r - mid) * lazy[x]) % MOD;
        lazy[x * 2] = (lazy[x * 2] + lazy[x]) % MOD;
        lazy[x * 2 + 1] = (lazy[x * 2 + 1] + lazy[x]) % MOD;
        lazy[x] = 0;
    }
    void build(int x = 1,int l = 1,int r = n) {
        if (l == r) {
            tree[x] = val[seg[l]] % MOD;
            return;
        }
        int mid = (l+r)/2;
        build(x*2,l,mid);
        build(x*2+1,mid+1,r);
        tree[x] = (tree[2*x] + tree[2*x+1]) % MOD;
    }
    void mergeS(int ql,int qr,int val,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) {
            tree[x] = (tree[x] + (r-l+1) * val) % MOD;
            lazy[x] = (lazy[x] + val) % MOD;
            return;
        }
        pushdown(x,l,r);
        int mid = (l+r)/2;
        if (ql <= mid) mergeS(ql,qr,val,x*2,l,mid);
        if (mid < qr) mergeS(ql,qr,val,x*2+1,mid+1,r);
        tree[x] = (tree[x*2] + tree[x*2+1]) % MOD;
    }
    int query(int ql,int qr,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) return tree[x] % MOD;
        pushdown(x,l,r);
        int mid = (l+r)/2;
        int ans = 0;
        if (ql <= mid) ans = (ans + query(ql,qr,x*2,l,mid)) % MOD;
        if (mid < qr) ans = (ans + query(ql,qr,x*2+1,mid+1,r)) % MOD;
        return ans;
    }
}T;

void pathAdd(int u,int v,int val) {
    while (top[u] != top[v]) {
        if (dep[top[u]] >= dep[top[v]]) {
            T.mergeS(dfn[top[u]],dfn[u],val);
            u = father[top[u]];
        }
        else {
            T.mergeS(dfn[top[v]],dfn[v],val);
            v = father[top[v]];
        }
    }
    T.mergeS(min(dfn[u],dfn[v]),max(dfn[u],dfn[v]),val);
}

void subTreeAdd(int u,int val) {
    T.mergeS(dfn[u],dfn[u]+siz[u]-1,val);
}

int pathQ(int u,int v) {
    int ans = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] >= dep[top[v]]) {
            ans = (ans + T.query(dfn[top[u]],dfn[u])) % MOD;
            u = father[top[u]];
        }
        else {
            ans = (ans + T.query(dfn[top[v]],dfn[v])) % MOD;
            v = father[top[v]];
        }
    }
    ans = (ans + T.query(min(dfn[u],dfn[v]),max(dfn[u],dfn[v]))) % MOD;
    return ans;
}

int subTreeQ(int u) {
    return T.query(dfn[u],dfn[u]+siz[u]-1);
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
    cin >> n >> m >> root >> MOD;
    for (int i = 1 ; i <= n ; i++) cin >> val[i];
    for (int i = 1 ; i < n ; i++) {
        int u,v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    DFS1(root,0);
    DFS2(root,root);
    T.build();
    for (int i = 1 ; i <= m ; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int x,y,z; cin >> x >> y >> z;
            pathAdd(x,y,z);
        }
        if (op == 2) {
            int x,y; cin >> x >> y;
            cout << pathQ(x,y) << endl;
        }
        if (op == 3) {
            int x,z; cin >> x >> z;
            subTreeAdd(x,z);
        }
        if (op == 4) {
            int x; cin >> x;
            cout << subTreeQ(x) << endl;
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
