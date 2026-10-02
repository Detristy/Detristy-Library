#include <bits/stdc++.h>
using namespace std;
//#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 1e6+10;
constexpr int M = 20;
int n,q;
vector<int> g[N];
vector<int> pos[N];
int father[N];
int dep[N];
int siz[N];
int son[N];
int top[N];
int dfn[N],cntDfn = 0;
int seg[N];

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
    pos[dep[u]].push_back(dfn[u]);
    seg[cntDfn] = u;
    if (son[u] == 0) return;
    DFS2(son[u],tp);
    for (auto v : g[u]) {
        if (v == father[u] || v == son[u]) continue;
        DFS2(v,v);
    }
}

int kFather(int u,int k) {
    if (k >= dep[u]) return 0;
    int target = dep[u] - k;
    while (dep[top[u]] > target) {
        u = father[top[u]];
    }
    return seg[dfn[u]-(dep[u]-target)];
}

void solve(const int CASE) {
    cin >> n >> q;
    for (int i = 1 ; i < n ; i++) {
        int x;
        cin >> x;
        g[x].push_back(i+1);
        g[i+1].push_back(x);
    }
    DFS1(1,0);
    DFS2(1,0);
    while (q--) {
        int u,k;
        cin >> u >> k;
        int kFa = kFather(u,k);
        if (!kFa) {
            cout << 0 << " ";
            continue;
        }
        int l = dfn[kFa],r = dfn[kFa] + siz[kFa] -1;
        auto &v = pos[dep[u]];
        int ans = upper_bound(v.begin(),v.end(),r)-lower_bound(v.begin(),v.end(),l)-1;
        cout << ans << " ";
    }
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    //cin >> DETRISTY;
    int i = 1;
    while (i <= DETRISTY) {
        solve(i++);
    }
    return 0;
}