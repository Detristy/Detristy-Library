#include <iostream>
using namespace std;
#define int long long
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int tot,m;
int dp[1100];

void solve() {
    cin >> tot >> m;
    for (int i = 1 ; i <= m ; i++) {
        int t,w;
        cin >> t >> w;
        for (int j = tot ; j >= t ; j--) {
            dp[j] = max(dp[j],dp[j-t]+w);
        }
    }
    cout << dp[tot] << endl;
}

signed main() {
    Detristy;
    int T = 1;
    //cin >> T;
    while (T--) {
        solve();
    }
}
