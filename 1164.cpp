#include <iostream>
using namespace std;
#define int long long
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n,m;
int a[10010],dp[10010];

void solve() {
    cin >> n >> m;
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
    }
    dp[0] = 1;
    for (int i = 1 ; i <= n ; i++) {
        for (int j = m ; j >= a[i] ; j--) {
            dp[j] = dp[j] + dp[j-a[i]];
        }
    }
    cout << dp[m] << endl;
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    //cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
}
