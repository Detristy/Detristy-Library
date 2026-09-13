#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve() {
    int x,y;
    cin >> x >> y;
    y = min(x,y);
    int ans = 0;
    for (int l = 1 ,r ; l <= y; l = r+1) {
        int v = x/l;
        if (!v) break;
        r = min(y,x/v);
        ans += v * (r-l+1);
    }
    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    //cin >> T;
    while (T--) solve();
}