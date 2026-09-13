#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

constexpr ull BASE = 499;
int n;
string s[2010];
ull ha[2010];
unordered_map<ull,int> mp;
void solve() {
    cin >> n;
    for (int i = 1 ; i <= n ; i++) {
        cin >> s[i];
    }
    sort(s+1,s+n+1);
    for (int i = 1 ; i <= n ; i++) {
        int dp = 1;
        for (int j = 0 ; j < s[i].length() ; j++) {
            ha[i] = ha[i]*BASE + s[i][j] - 'a' + 1;
            if (mp.count(ha[i])) {
                dp = max(dp,mp[ha[i]]+1);
            }
        }
        mp[ha[i]] = dp;
    }
    int ans = 0;
    for (auto [a,b] : mp) {
        ans = max(ans,b);
    }
    cout << ans << '\n';
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    //cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
}
