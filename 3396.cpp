#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n,m;
int a[150010];
int dp[400][400];

void solve() {
    cin >> n >> m;
    int b = sqrt(n);
    for (int i = 1 ; i <= n ; i++) cin >> a[i];
    for (int i = 1 ; i <= b ; i++) {
        for (int j = 1 ; j <= n ; j++) {
            dp[i][j%i] += a[j];
        }
    }
    while (m--) {
        char op; int x,y;
        cin >> op >> x >> y;
        if (op == 'A') {
            if (x <= b) cout << dp[x][y] << endl;
            else {
                int res = 0,idx = y;
                while (idx <= n) {
                    res += a[idx];
                    idx += x;
                }
                cout << res << endl;
            }
        }
        else {
            int delta = y - a[x];
            a[x] = y;
            for (int i = 1 ; i <= b; i++) dp[i][x%i] += delta;
        }
    }
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    //cin >> DETRISTY;
    while (DETRISTY--) solve();
    return 0;
}
