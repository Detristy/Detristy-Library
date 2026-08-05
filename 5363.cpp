#include <bits/stdc++.h>
using namespace std;
#define int long long
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n,m;
int k[1010],c[1010];
int dp[300010];

void solve(){
    cin >> n >> m;
    int tot = 0;
    for (int i = 1 ; i <= n ; i++) {
        cin >> k[i];
    }
    for (int i = 1 ; i <= n ; i++) {
        cin >> c[i];
        tot += k[i]*c[i];
    }
    dp[0] = 1;
    for (int i = 1 ; i <= n ; i++) {
        for (int j = tot; j >= 0 ; j--){
            for (int p = 1 ; p <= k[i] && p*c[i] <= j ; p++) {
                dp[j] = max(dp[j],dp[j - p*c[i]]*p);
            }
        }
    }
    for (int i = 1 ; i <= tot ; i++) {
        if (dp[i] >= m) {
            cout << i << endl;
            return;
        }
    }
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    //cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
}
