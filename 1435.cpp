#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

string s;
int dp[1010][1010];

void solve() {
    cin >> s;
    int n = s.length();
    for (int i = 1 ; i <= n ; i++) {
        dp[i][i] = 0;
    }
    for (int len = 2 ; len <= n ; len++) {
        for (int i = 1 ; i <= n-len+1 ; i++) {
            int j = i + len - 1;
            if (s[i-1] == s[j-1] && len <= 3) {
                dp[i][j] = 0;
            }
            else if (s[i-1] == s[j-1] && len > 3) {
                dp[i][j] = dp[i+1][j-1];
            }
            if (s[i-1] != s[j-1]) {
                dp[i][j] = min(dp[i+1][j], dp[i][j-1]) + 1;
            }
        }
    }
    cout << dp[1][n] << endl;
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    //cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
}
