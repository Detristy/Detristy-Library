#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

constexpr int N = 1e5+10;
constexpr int B = 350;
int n,q;
int a[N],f[B][N],g[B][N];

void solve() {
    cin >> n >> q;
    int b = sqrt(n);
    for (int i = 1 ; i <= n ; i++) cin >> a[i];
    for (int i = 1 ; i <= b ; i++) {
        for (int j = n ; j >= 1 ; j--) {
            if (i + j > n) f[i][j] = a[j];
            else f[i][j] = a[j] + f[i][i+j];
        }
    }
    for (int i = 1 ; i <= b ; i++) {
        for (int j = n ; j >= 1 ; j--) {
            if (i + j > n) g[i][j] = f[i][j];
            else g[i][j] = f[i][j] + g[i][i+j];
        }
    }
    while (q--) {
        int s,d,k;
        cin >> s >> d >> k;
        if (d <= b) {
            if (s+k*d <= n) {
                cout << g[d][s] - g[d][s+k*d] - k*f[d][s+k*d] << " ";
            }
            else {
                cout << g[d][s] << " ";
            }
        }
        else {
            int ans = 0;
            for (int i = 1 ; i <= k ; i++) {
                ans += a[s+(i-1)*d] * i;
            }
            cout << ans << " ";
        }
    }
    cout << endl;
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
