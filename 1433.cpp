#include <bits/stdc++.h>
using namespace std;
#define int long long
#define db double

int n;
db x[20],y[20];
db dis[20][20];
db dp[1 << 16][16];

db dist(db x1,db y1,db x2,db y2) {
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

void solve() {
    cin >> n;
    for (int i = 1 ; i <= n ; i++) {
        cin >> x[i] >> y[i];
    }
    for (int i = 0 ; i <= n ; i++) {
        for (int j = 0 ; j <= n ; j++) {
            dis[i][j] = dist(x[i],y[i],x[j],y[j]);
        }
    }
    for (int i = 0 ; i < (1 << n) ; i++) {
        for (int j = 1 ; j <= n ; j++) {
            dp[i][j] = 1e9;
        }
    }
    for (int i = 1 ; i <= n ; i++) {
        dp[1 << (i-1)][i] = dis[0][i];
    }
    for (int i = 1 ; i < (1 << n) ; i++) {
        for (int j = 1 ; j <= n ; j++) {
            if (!(i & (1 << (j-1)))) continue;
            if (dp[i][j] == 1e9) continue;
            for (int k = 1 ; k <= n ; k++) {
                if (i & (1<<(k-1))) continue;
                int nxt = i | (1<<(k-1));
                dp[nxt][k] = min(dp[nxt][k], dp[i][j] + dis[j][k]);
            }
        }
    }
    db ans = 1e9;
    for (int i = 1 ; i <= n ; i++) {
        ans = min(ans,dp[(1<<n)-1][i]);
    }
    cout << fixed << setprecision(2) << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T = 1;
    //cin >> T;
    while (T--) solve();
    return 0;
}