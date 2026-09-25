#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 110;
int V,n;
vector<int> g[N];
int dp[N][N][2];

void DFS(int u,int fa) {
    for (auto v : g[u]) {
        if (v == fa) continue;
        DFS(v,u);
        for (int i = n; i >= 0 ; i--) {
            for (int j = 0 ; j < i ; j++) {
                dp[u][i][0] = max(dp[u][i][0],dp[u][i-j-1][1] + dp[v][j][0]);
                if (i-j-2 >= 0) {
                    dp[u][i][0] = max(dp[u][i][0],dp[u][i-j-2][0] + dp[v][j][1]);
                    dp[u][i][1] = max(dp[u][i][1],dp[u][i-j-2][1] + dp[v][j][1]);
                }
            }
        }
    }
}

void solve() {
    cin >> V >> n;
    for (int i = 1 ; i < V ; i++) {
        int x,y;
        cin >> x >> y;
        x++; y++;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    for (int i = 1 ; i <= V ; i++) {
        dp[i][0][1] = dp[i][0][0] = 1;
    }
    DFS(1,0);
    int ans = -1e9;
    for (int i = 0 ; i <= n ; i++) {
        ans = max({ans,dp[1][i][0],dp[1][i][1]});
    }
    cout << ans << endl;
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