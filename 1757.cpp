#include <bits/stdc++.h>
using namespace std;
#define int long long
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int m,n;
int a[1010],b[1010],dp[1010];
int cnt[105],g[105][1005];

void solve() {
    cin >> m >> n;
    int t = 1;
    for (int i = 1 ; i <= n ; i++) {
        int c;
        cin >> a[i] >> b[i] >> c;
        t = max(t,c);
        cnt[c]++;
        g[c][cnt[c]] = i;
    }
    for (int i = 1 ; i <= t ; i++) {
        for (int j = m ; j >= 0 ; j--) {
            for (int k = 1 ; k <= cnt[i] ; k++) {
                if (j >= a[g[i][k]]) {
                    dp[j] = max(dp[j],dp[j-a[g[i][k]]]+b[g[i][k]]);
                }
            }
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
