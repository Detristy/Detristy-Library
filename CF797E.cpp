#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n,q;
int a[100010],dp[100010][410];

void solve() {
    cin >> n;
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
    }
    int b = sqrt(n);
    for (int i = n ; i >= 1 ; i--) {
        for (int k = 1 ; k <= b ; k++) {
            if (i + a[i] + k > n) dp[i][k] = 1;
            else dp[i][k] = dp[i+a[i]+k][k] + 1;
        }
    }
    cin >> q;
    while (q--) {
        int p,k;
        cin >> p >> k;
        if (k <= b) {
            cout << dp[p][k] << endl;
        }
        else {
            int cnt = 0;
            while (p <= n) {
                p = p + a[p] + k;
                cnt++;
            }
            cout << cnt << endl;
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
    return 0;
}
