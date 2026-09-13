#include <algorithm>
#include <iostream>
using namespace std;
#define int long long
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

constexpr int N = 4e5;
int n;
int s[410],f[410];
int dp[2*N+10];

void solve() {
    cin >> n;
    for (int i = 1 ; i <= n ; i++) {
        cin >> s[i] >> f[i];
    }
    for (int i = 0 ; i <= 2*N ; i++) dp[i] = -1e9;
    dp[N] = 0;
    for (int i = 1 ; i <= n ; i++) {
        if (s[i] >= 0) {
            for (int j = 2*N ; j >= s[i] ; j--) {
                dp[j] = max(dp[j],dp[j-s[i]]+f[i]);
            }
        }
        else {
            for (int j = 0 ; j <= 2*N+s[i] ; j++) {
                dp[j] = max(dp[j],dp[j-s[i]]+f[i]);
            }
        }
    }
    int ans = 0;
    for (int i = N ; i <= 2*N ; i++) {
        if (dp[i]>=0) ans = max(ans,i-N+dp[i]);
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
