#include <bits/stdc++.h>
using namespace std;
#define int long long
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n,W;
constexpr int N = 1e5+10;
int dp[N];

void solve(){
    cin >> n >> W;
    for (int i = 1 ; i <= n ; i++) {
        int v,w,m;
        cin >> v >> w >> m;
        for (int j = 1 ; j <= m ; m -= j,j *= 2) {
            for (int k = W ; k >= w*j ; k--) {
                dp[k] = max(dp[k],dp[k-w*j]+v*j);
            }
        }
        for (int k = W ; k >= w*m ; k--) {
            dp[k] = max(dp[k],dp[k-w*m]+v*m);
        }
    }
    cout << dp[W] << endl;
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    //cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
}
