#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n;

void solve() {
    cin >> n;
    vector<int> v(2*n+1);
    vector<int> ri(n+1,0);
    for (int i = 1 ; i <= 2*n ; i++) {
        cin >> v[i];
        ri[v[i]] = i; //确定区间右端点的位置
    }
    vector<int> dp(2*n+2,0);
    dp[2*n] = 1;
    for (int i = 2*n ; i >= 1 ; i--) {
        dp[i] = dp[i+1] + 1;
        if (ri[v[i]] > i) {
            dp[i] = max(dp[i],dp[ri[v[i]]+1] + (ri[v[i]] - i + 1) * (ri[v[i]] - i + 1));
        }
    }
    cout << dp[1] << endl;
}


signed main() {
    Detristy;
    int DETRISTY = 1;
    cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
    return 0;
}
