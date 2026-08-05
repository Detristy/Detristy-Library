#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
#define int long long
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n,h,mx=5e3;
int p[105],c[105];
int dp[55010];

void solve() {
    cin >> n >> h;
    for (int i = 1 ; i <= n ; i++){
        cin >> p[i] >> c[i];
    }
    for (int i = 1 ; i <= h+mx ; i++) dp[i] = 1e9;
    for (int i = 1 ; i <= n ; i++) {
        for (int j = p[i] ; j <= h+mx ; j++) {
            dp[j] = min(dp[j],dp[j-p[i]]+c[i]);
        }
    }
    int ans = 1e9;
    for (int i = h ; i <= h+mx ; i++) {
        ans = min(ans,dp[i]);
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
}
