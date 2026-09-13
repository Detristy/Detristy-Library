#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

void solve() {
    int n; cin >> n;
    vector<int> a(n+1,0);
    for (int i = 1 ; i <= n ; i++) cin >> a[i];
    int mx = -1e9;
    for (int i = 1 ; i <= n ; i++) {
        for (int j = 1 ; j <= n ; j++) {
            if (i != j) {
                mx = max(mx,a[i] ^ a[j]);
            }
        }
    }
    cout << mx << endl;
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