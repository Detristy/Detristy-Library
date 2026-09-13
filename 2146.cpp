#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 1e5+10;
constexpr int MOD = 998244353;
int n,q;
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
    bool has_tag[N*4];
    void pushdown(int x,int l,int r) {
        if (!has_tag[x]) return;
        int mid = (l+r)/2;
        tree[x*2] = (mid-l+1) * lazy[x];
        tree[x*2+1] = (r-mid) * lazy[x];
        lazy[x*2] = lazy[x];
        lazy[x*2+1] = lazy[x];
        has_tag[x*2] = has_tag[x*2+1] = true;
        has_tag[x] = false;
    }
    void build(int x = 1,int l = 1,int r = n) {
        if (l == r) {
            tree[x] = 0;
            return;
        }
        int mid = (l+r)/2;
        build(x*2,l,mid);
        build(x*2+1,mid+1,r);
        tree[x] = tree[2*x] + tree[2*x+1];
    }
    void mergeS(int ql,int qr,int val,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) {
            tree[x] = (r-l+1)*val;
            lazy[x] = val;
            has_tag[x] = true;
            return;
        }
        pushdown(x,l,r);
        int mid = (l+r)/2;
        if (ql <= mid) mergeS(ql,qr,val,x*2,l,mid);
        if (mid < qr) mergeS(ql,qr,val,x*2+1,mid+1,r);
        tree[x] = (tree[x*2] + tree[x*2+1])  ;
    }
    int query(int ql,int qr,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) return tree[x]  ;
        pushdown(x,l,r);
        int mid = (l+r)/2;
        int ans = 0;
        if (ql <= mid) ans += query(ql,qr,x*2,l,mid);
        if (mid < qr) ans += query(ql,qr,x*2+1,mid+1,r);
        return ans;
    }
}T;

void pathChange(int u,int v,int val) {
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

void subTreeChange(int u,int val) {
    T.mergeS(dfn[u],dfn[u]+siz[u]-1,val);
}

int pathQ(int u,int v) {
    int ans = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] >= dep[top[v]]) {
            ans = (ans + T.query(dfn[top[u]],dfn[u]))  ;
            u = father[top[u]];
        }
        else {
            ans = (ans + T.query(dfn[top[v]],dfn[v]))  ;
            v = father[top[v]];
        }
    }
    ans = (ans + T.query(min(dfn[u],dfn[v]),max(dfn[u],dfn[v])))  ;
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
    cin >> n;
    for (int i = 2 ; i <= n ; i++) {
        int v; cin >> v; v++;
        g[i].push_back(v),g[v].push_back(i);
    }
    DFS1(1,0),DFS2(1,1);
    T.build();
    cin >> q;
    while (q--) {
        string op; int x; cin >> op >> x; x++;
        if (op == "install") {
            int pre = subTreeQ(1);
            pathChange(1,x,1);
            cout << abs(pre-subTreeQ(1)) << endl;
        }
        else if (op == "uninstall") {
            int pre = subTreeQ(1);
            subTreeChange(x,0);
            cout << abs(pre-subTreeQ(1)) << endl;
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
