#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 5e4+10;
int n;
vector<int> g[N];
int dp[N][2];

void DFS(int u,int fa) {
    for (auto v : g[u]) {
        if (v == fa) continue;
        DFS(v,u);
        dp[u][1] += dp[v][0];
        dp[u][0] += max(dp[v][0],dp[v][1]);
    }
}

void solve() {
    cin >> n;
    for (int i = 1 ; i < n ; i++) {
        int u,v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1 ; i <= n ; i++) {
        dp[i][1] = 1;
    }
    DFS(1,0);
    cout << max(dp[1][1],dp[1][0]);
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