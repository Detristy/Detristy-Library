#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define TEST cout << "TEST" << endl;
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 1e5+10;
constexpr int M = 20;
int n,m;
vector<int> g[N];
vector<int> opT[N];
vector<int> pos[N];
int dep[N];
int dfn[N],cnt,dfnToNd[N];
int f[N][M+10];

int op[N];
int X[N],Y[N];
bool light[N];
int ans[N];

int out[N]; //DFS序子树右端点
int id[N]; //树状数组下标
int rk[N];
int base[N]; //每层初始

struct BIT {
    int t[N];
    int lowbit(int x) {
        return x & -x;
    }
    void add(int x,int val) {
        for (; x <= n ; x += lowbit(x)) {
            t[x] += val;
        }
    }
    int query(int x) {
        int ans = 0;
        for (; x ; x -= lowbit(x)) {
            ans += t[x];
        }
        return ans;
    }
}t;

void DFS(int u,int fa) {
    dfn[u] = ++cnt;
    dfnToNd[cnt] = u;
    dep[u] = dep[fa] + 1;

    pos[dep[u]].push_back(dfn[u]);
    rk[u] = pos[dep[u]].size();

    f[u][0] = fa;
    for (int i = 1 ; i <= M ; ++i) {
        f[u][i] = f[f[u][i-1]][i-1];
    }
    for (auto v : g[u]) {
        if (v != fa) {
            DFS(v,u);
        }
    }
    out[u] = cnt;
}

int find(int u,int k) {
    for (int i = 0 ; i <= M ; i++) {
        if ((k >> i) & 1) {
            u = f[u][i];
        }
    }
    return u;
}

int cntLight(int u,int d) {
    if (u == 0 || d < 1 || d > n) {
        return 0;
    }
    auto &vec = pos[d];
    int l = lower_bound(vec.begin(),vec.end(),dfn[u]) - vec.begin();
    int r = upper_bound(vec.begin(),vec.end(),out[u]) - vec.begin();
    return t.query(base[d] + r) - t.query(base[d]+l);
}

int querySum(int x,int y) {
    if (y%2) {
        return 0;
    }
    if (y == 0) {
        return light[x];
    }
    int k = y/2;
    if (k >= dep[x]) {
        return 0;
    }
    int a = find(x,k);
    int b = find(x,k-1);
    return cntLight(a,dep[x]) - cntLight(b,dep[x]);
}

void DFS2(int u) {
    if (op[u] == 1) {
        t.add(id[X[u]],light[X[u]] ? -1 : 1);
        light[X[u]] = !light[X[u]];
    }
    else if (op[u] == 2) {
        ans[u] = querySum(X[u],Y[u]);
    }
    for (auto v : opT[u]) {
        DFS2(v);
    }
    if (op[u] == 1) {
        t.add(id[X[u]],light[X[u]] ? -1 : 1);
        light[X[u]] = !light[X[u]];
    }
}

void solve(const int CASE) {
    cin >> n;
    for (int i = 1 ; i < n ; i++) {
        int u,v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    DFS(1,0);

    //树映射到树状数组上
    //每层按Dfn序排序
    base[1] = 0;
    for (int i = 2 ; i <= n ; i++) {
        base[i] = base[i-1] + pos[i-1].size();
    }
    for (int i = 1 ; i <= n ; i++) {
        id[i] = base[dep[i]] + rk[i];
    }

    cin >> m;
    for (int i = 1 ; i <= m ; i++) {
        cin >> op[i];
        if (op[i] == 1) {
            cin >> X[i];
            opT[i-1].push_back(i);
        }
        else if (op[i] == 2) {
            cin >> X[i] >> Y[i];
            opT[i-1].push_back(i);
        }
        else {
            cin >> X[i];
            opT[X[i]].push_back(i);
        }
    }
    DFS2(0);
    for (int i = 1 ; i <= m ; i++) {
        if (op[i] == 2) {
            cout << ans[i] << endl;
        }
    }
}

signed main() {
    Detristy;
    int DETRISTY = 1,Det = 1;
    //cin >> DETRISTY;
    while (Det <= DETRISTY) {
        solve(Det++);
    }
    return 0;
}