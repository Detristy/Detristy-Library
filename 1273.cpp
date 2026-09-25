#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 3010;
int n,m;
vector<pair<int,int>> g[N];
int siz[3010];
int dp[3010][3010];

void dfs(int u) {
    for (auto [v,w] : g[u]) {
        dfs(v);
        for (int i = siz[v]+siz[u] ; i >= 1 ; i--) {
            for (int j = 1 ; j <= min(siz[v],i) ; j++) {
                dp[u][i] = max(dp[u][i],dp[u][i-j]+dp[v][j]-w);
            }
        }
        siz[u] += siz[v];
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 1 ; i <= n-m ; i++) {
        int k;
        cin >> k;
        for (int j = 1 ; j <= k ; j++) {
            int a,c;
            cin >> a >> c;
            g[i].push_back({a,c});
        }
    }
    for (int i = 1 ; i <= 3000 ; i++) {
        for (int j = 1 ; j <= 3000 ; j++) {
            dp[i][j] = -1e9;
        }
    }
    for (int i = n-m+1 ; i <= n ; i++) {
        cin >> dp[i][1];
        siz[i] = 1;
        dp[i][0] = 0;
    }
    dfs(1);
    for (int i = m ; i >= 0 ; i--) {
        if (dp[1][i] >= 0) {
            cout << i << endl;
            break;
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