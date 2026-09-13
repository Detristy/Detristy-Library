#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n,m;
unordered_map<char,int> mp;
int dp[2010][2010];

void solve() {
    memset(dp,0x3f,sizeof(dp));
    cin >> n >> m;
    string s; cin >> s;
    for (int i = 1 ; i <= n ; i++) {
        char c; int a,b;
        cin >> c >> a >> b;
        mp[c] = min(a,b);
    }
    for (int i = 1 ; i <= m ; i++) {
        dp[i][i] = dp[i][i-1] = 0;
    }
    for (int len = 2 ; len <= m ; len++) {
        for (int i = 1 ; i <= m-len+1 ; i++) {
            int j = i + len - 1;
            if (s[i-1] == s[j-1]) {
                dp[i][j] = dp[i+1][j-1];
            }
            else {
                dp[i][j] = min(dp[i+1][j]+mp[s[i-1]], dp[i][j-1]+mp[s[j-1]]);
            }
        }
    }
    cout << dp[1][m] << endl;
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    //cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
}
