#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

void solve() {
    int n;
    cin >> n;
    vector<int> a(n+1,0);
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
    }
    int init = 0,final = 0;
    for (int i = 1 ; i <= n ; i++) {
        init += i * a[i];
    }
    vector<int> cnt1(n+1,0);
    for (int i = 1 ; i <= n ; i++) {
        cnt1[a[i]]++;
    }
    vector<int> cnt(n+2,0);
    cnt[n] = cnt1[n];
    for (int i = n ; i >= 1 ; i--) {
        cnt[i] = cnt[i+1] + cnt1[i];
        final += cnt[i] * (2*n-cnt[i]+1)/2;
    }
    int ans = final - init;
    int mx = 0;
    for (int i = 1 ; i <= n ; i++) {
        mx = max(mx,i-n+cnt[a[i]]-1);
    }
    ans += mx;
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