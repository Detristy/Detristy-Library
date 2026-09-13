#include <bits/stdc++.h>
using namespace std;
#define int long long
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

constexpr int N = 1e6+10;
int n,m,C;
int dp[N];

void solve(){
    cin >> n >> m >> C;
    for (int i = 1 ; i <= n ; i++) {
        int v,w,d;
        cin >> v >> w >> d;
        for (int j = 1 ; j <= d ; d -= j ,j *= 2) {
            for (int k = C ; k >= j*v ; k--) {
                dp[k] = max(dp[k], dp[k-j*v] + j*w);
            }
        }
        for (int k = C ; k >= d*v ; k--) {
            dp[k] = max(dp[k], dp[k-d*v] + d*w);
        }
    }
    for (int i = 1 ;  i <= m ; i++) {
        int a,b,c;
        cin >> a >> b >> c;
        for (int j = C ; j >= 0 ; j--) {
            for (int k = 0 ; k <= j ; k++) {
                dp[j] = max(dp[j],dp[j-k]+(a*k*k + b*k + c));
            }
        }
    }
    cout << dp[C] << endl;
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    //cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
}
