#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
#define int long long
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int s,n,d;
int a[12],b[12];
int dp[10005];

void solve() {
    cin >> s >> n >> d;
    for (int i = 1 ; i <= d ; i++) {
        cin >> a[i] >> b[i];
        a[i] /= 1000;
    }
    int ans = s;
    for (int i = 1 ; i <= n ; i++) {
        memset(dp,0,sizeof(dp));
        for (int j = 1 ; j <= d ; j++) {
            for (int k = a[j] ; k <= ans/1000 ; k++) {
                dp[k] = max(dp[k], dp[k-a[j]] + b[j]);
            }
        }
        ans += dp[ans/1000];
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
