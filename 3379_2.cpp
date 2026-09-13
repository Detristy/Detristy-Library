#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 5e5+10;
constexpr int M = 20;
int n,m,s;
vector<int> g[N];
int dep[N];
int f[N][M+5];
int dfn[N*2],euler = 0;
int first[N];
int lg2[N*2];
int rmq[N*2][M+5];

void dfs(int u,int fa) {
    dep[u] = dep[fa] + 1;
    first[u] = ++euler;
    rmq[first[u]][0] = u;
    for (auto v : g[u]) {
        if (v != fa) {
            dfs(v,u);
            rmq[++euler][0] = u;
        }
    }
}

int getUp(int u,int v) {
    return dep[u] < dep[v] ? u : v;
}

void buildRmq(int rt) {
    dfs(rt,0);
    lg2[1] = 0;
    for (int i = 2 ; i <= euler ; i++) {
        lg2[i] = lg2[i/2] + 1;
    }
    for (int pre = 0,cur = 1 ; cur <= lg2[euler] ; pre++ , cur++) {
        for (int i = 1 ; i + (1 << cur) - 1 <= euler; i++) {
            rmq[i][cur] = getUp(rmq[i][pre],rmq[i+(1 << pre)][pre]);
        }
    }
}

int LCA(int x,int y) {
    x = first[x];
    y = first[y];
    if (x > y) swap(x,y);
    int k = lg2[y-x+1];
    return getUp(rmq[x][k],rmq[y-(1<<k)+1][k]);
}

void solve() {
    cin >> n >> m >> s;
    for (int i = 1 ; i < n ; i++) {
        int x,y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    buildRmq(s);
    for (int i = 1 ; i <= m ; i++) {
        int x,y;
        cin >> x >> y;
        cout << LCA(x,y) << endl;
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