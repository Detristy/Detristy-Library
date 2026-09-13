#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> a[500010];
int pre[2000][2000];

void solve() {
    int n,k,q;
    cin >> n >> k >> q;
    memset(pre,0,sizeof(pre));
    for (int i = 1 ; i <= k ; i++) {
        a[i].push_back(0);
        for (int j = 1 ; j <= n ; j++) {
            int x;
            cin >> x;
            a[i].push_back(x);
            a[i][j] += a[i][j-1];
        }
    }
    if (n > k) {
        while (q--) {
            int l,r;
            cin >> l >> r;
            int ans = 0;
            for (int i = 1 ; i <= k ; i++) {
                ans = max(ans,a[i][r]-a[i][l-1]);
            }
            cout << ans << endl;
        }
    }
    else {
        for (int l = 1 ; l <= n ; l++) {
            for (int r = 1 ; r <= n ; r++) {
                for (int i = 1 ; i <= k ; i++) {
                    pre[l][r] = max(pre[l][r],a[i][r]-a[i][l-1]);
                }
            }
        }
        while (q--) {
            int l,r;
            cin >> l >> r;
            cout << pre[l][r] << endl;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    //cin >> T;
    while (T--) solve();
}