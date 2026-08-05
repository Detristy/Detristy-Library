#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n;
int v[2010],sum[2010];
int dp[2010][2010];

void solve() {
    cin >> n;
    for (int i = 1 ; i <= n ; i++) {
        cin >> v[i];
        sum[i] = sum[i-1] + v[i];
        dp[i][i] = v[i];
    }
    for (int len = 2 ; len <= n ; len++) {
        for (int i = 1 ; i <= n - len + 1 ; i++) {
            int j = i + len - 1;
            dp[i][j] = max(dp[i][j] , max(v[i]+dp[i+1][j]+sum[j]-sum[i] , v[j]+dp[i][j-1]+sum[j-1]-sum[i-1]));
        }
    }
    cout << dp[1][n] << endl;
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    //cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
}
