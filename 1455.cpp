#include <bits/stdc++.h>
using namespace std;
#define int long long
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

constexpr int N = 1e4+10;
int n,m,w,c[N],d[N],fa[N],dp[N];

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void solve() {
    cin >> n >> m >> w;
    for (int i = 1 ; i <= n ; i++) {
        fa[i] = i;
        cin >> c[i] >> d[i];
    }
    for (int i = 1 ; i <= m ; i++) {
        int u,v;
        cin >> u >> v;
        if (find(u) != find(v)) fa[find(u)] = find(v);
    }
    for (int i = 1 ; i <= n ; i++) {
        if (i == fa[i]) continue;
        d[find(i)] += d[i]; d[i] = 0;
        c[find(i)] += c[i]; c[i] = 0;
    }
    for (int i = 1 ; i <= n ; i++) {
        for (int j = w; j >= c[i] ; j--) {
            dp[j] = max(dp[j],dp[j-c[i]]+d[i]);
        }
    }
    int ans = 0;
    for (int i = 1 ; i <= w ; i++) {
        ans = max(ans,dp[i]);
    }
    cout << ans << '\n';
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    //cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
}
