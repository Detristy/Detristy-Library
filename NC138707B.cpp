#include <bits/stdc++.h>
using namespace std;
#define int long long

int n;
int a[200010];
int b[200010];

void solve() {
    cin >> n;
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
    }
    bool all_0 = true;
    for (int i = 3 ; i <= n ; i++) {
        b[i] = abs(a[i] - 2*a[i-1] + a[i-2]);
        if (b[i] != 0) all_0 = false;
    }
    if (all_0) {
        cout << -1 << endl;
        return;
    }
    int res = b[3];
    for (int i = 3 ; i <= n ; i++) {
        res = gcd(res, b[i]);
    }
    cout << res << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T = 1;
    //cin >> T;
    while (T--) solve();
    return 0;
}