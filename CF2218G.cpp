#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int MOD = 676767677;

void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> b(n+1,0);
    vector<int> cnt(m+1,0);
    vector<int> pre(m+1,0);
    for (int i = 1 ; i <= n ; i++) {
        cin >> b[i];
        cnt[b[i]]++;
    }
    int ans = 1;
    pre[0] = cnt[0];
    for (int i = 1 ; i < m ; i++) pre[i] = pre[i-1] + cnt[i];
    for (int i = 1 ; i <= n ; i++) {
        if (b[i] > 0) {
            int time = 1e9;
            if (i > 1) time = min(time,b[i-1]+1);
            if (i < n) time = min(time,b[i+1]+1);
            if (b[i] > time) {
                ans = ans * cnt[b[i]-1] % MOD;
            }
            else if (b[i] == time) {
                ans = ans * pre[b[i]-1] % MOD;
            }
            else {
                ans = 0;
            }
        }
    }
    ans %= MOD;
    cout << ans << endl;
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