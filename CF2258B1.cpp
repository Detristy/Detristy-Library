#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

void solve() {
    int n,m; cin >> n >> m;
    int mn = 1e9,mx = 0;
    vector<int> a(n+1);
    vector<int> cnt(m+1,0);
    vector<int> pre(m+1,0);
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    for (int i = 1 ; i <= m ; i++) pre[i] = pre[i-1] + cnt[i];
    int ans = n;
    for (int i = 1 ; i <= m ; i++) {
        ans = max(ans,n-pre[i-1]+(2*i <= m ? cnt[2*i] : 0));
    }
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