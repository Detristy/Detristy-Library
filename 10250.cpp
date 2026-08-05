#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int a[70];

void solve() {
    int n;
    cin >> n;
    a[0] = 1;
    a[1] = 1;
    a[2] = 2;
    for (int i = 3 ; i <= n ; i++) {
        a[i] = a[i-1] + a[i-2] + a[i-3];
    }
    cout << a[n] << endl;
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    //cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
    return 0;
}
