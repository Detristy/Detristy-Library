#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n;
int a[210],dp[210][210];

void solve() {
    cin >> n;
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
        a[n+i] = a[i];
    }
    for (int len = 1 ; len <= n ; len++) {
        for (int i = 1 ; i <= 2*n-len ; i++) {
            int j = i + len;
            for (int k = i ; k < j ; k++) {
                dp[i][j] = max(dp[i][j], dp[i][k]+dp[k+1][j]+a[i]*a[k+1]*a[j+1] );
            }
        }
    }
    int ans = 0;
    for (int i = 1 ; i <= n ; i++) {
        ans = max(ans,dp[i][i+n-1]);
    }
    cout << ans;
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    //cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
}
