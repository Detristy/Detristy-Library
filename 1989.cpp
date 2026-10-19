#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define INF 0x3f3f3f3f3f3f3f3f
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 1e5+10;
int n,m,ans;
int deg[N];
vector<pair<int,int>> edge;
vector<int> g[N];
int tag[N];

void solve(int CASE) {
    cin >> n >> m;
    for (int i = 1 ; i <= m ; i++) {
        int u,v;
        cin >> u >> v;
        edge.push_back({u,v});
        deg[u]++;
        deg[v]++;
    }
    for (auto [u,v] : edge) {
        if (deg[u] > deg[v] || deg[u] == deg[v] && u > v) {
            swap(u,v);
        }
        g[u].push_back(v);
    }
    for (int u = 1 ; u <= n ; u++) {
        for (auto w : g[u]) {
            tag[w] = u;
        }
        for (auto v : g[u]) {
            for (auto w : g[v]) {
                if (tag[w] == u) {
                    ans++;
                }
            }
        }
    }
    cout << ans << endl;
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