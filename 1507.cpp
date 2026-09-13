#include <iostream>
using namespace std;
#define int long long
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int H,T,n;
int h[405],t[405],kal[405];
int dp[405][405];

void solve() {
    cin >> H >> T >> n;
    for (int i = 1 ; i <= n ; i++) {
        cin >> h[i] >> t[i] >> kal[i];
    }
    for (int i = 1 ; i <= n ; i++) {
        for (int j = H ; j >= h[i] ; j--) {
            for (int k = T ; k >= t[i] ; k--) {
                dp[j][k] = max(dp[j][k], dp[j - h[i]][k - t[i]] + kal[i]);
            }
        }
    }
    cout << dp[H][T] << endl;
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    //cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
}
