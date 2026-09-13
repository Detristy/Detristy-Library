#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

void solve() {
    int n; cin >> n;
    vector<int> a(n+1);
    bool ok = true;
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
        if (a[i] < i) {
            ok = false;
        }
    }
    if (!ok) {
        cout << -1 << endl;
        return;
    }
    vector<int> b(n+1);
    b[n] = a[n];
    for (int i = n-1 ; i >= 1 ; i--) {
        b[i] = min(a[i],b[i+1]-1);
    }
    int s = 0;
    int suma = 0;
    int sumt = 0;
    for (int i = 1 ; i <= n ; i++) {
        int t = min(b[i],s+i);
        suma += a[i];
        sumt += t;
        s += a[i] - t;
    }
    int ans = n + suma - sumt;
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