#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

void solve() {
    int n,k;
    cin >> n >> k;
    if (k%2) {
        cout << -1 << endl;
        return;
    }
    if (3*k <= 4*n) cout << 3 << endl;
    else cout << -1 << endl;
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