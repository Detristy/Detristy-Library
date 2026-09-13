#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

struct edge {
    int u,v,w;
};

int fa[200010];

bool cmp(edge a,edge b) {
    return a.w < b.w;
}

bool cmp2(pair<int,int> a,pair<int,int> b) {
    return a.second < b.second;
}

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    vector<edge> ed;
    vector<int> a(k+1);
    unordered_set<int> spe; //存被标记的点
    vector<pair<int,int>> g[n+1]; //邻接表方便排序
    for (int i = 1 ; i <= k ; i++) {
        cin >> a[i];
        spe.insert(a[i]);
    }
    for (int i = 1 ; i <= n ; i++) fa[i] = i;
    for (int i = 1; i <= m ; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        if (u == v) continue;
        ed.push_back({u,v,w});
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }
    if (n == 2) {
        int res = -1;
        for (auto [u,v,w] : ed) {
            if (res == -1) res = w;
            if (w < res) res = w;
        }
        cout << res << endl;
        return;
    }
    if (n == k) {
        cout << -1 << endl;
        return;
    }
    for (int i = 1 ; i <= n ; i++) {
        sort(g[i].begin(),g[i].end(),cmp2);
    }
    sort(ed.begin(),ed.end(),cmp);
    int total = 0;
    int cnt = 0;
    for (auto &e : ed) {
        if (find(e.u) != find(e.v) && !spe.count(e.u) && !spe.count(e.v)) {
            fa[find(e.u)] = find(e.v);
            cnt++;
            total += e.w;
            if (cnt == n-1-k) break;
        }
    }
    for (auto u : spe) {
        bool able = false;
        for (auto [v,w] : g[u]) {
            if (!spe.count(v) && find(u) != find(v)) {
                fa[find(u)] = find(v);
                cnt++;
                total += w;
                able = true;
                break;
            }
        }
        if (!able) {
            cout << -1 << endl;
            return;
        }
    }
    if (cnt != n-1) cout << -1 << endl;
    else cout << total << endl;
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
    return 0;
}
