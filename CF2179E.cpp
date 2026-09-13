#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

void solve() {
    int n,x,y;
    cin >> n >> x >> y;
    string s; cin >> s;
    vector<int> p(n+1,0);
    bool has1 = false,has0 = false;
    int sumA = 0,sumB = 0,tot = 0;
    for (int i = 1 ; i <= n ; i++) {
        cin >> p[i];
        tot += p[i];
    }
    if (x + y < tot) {
        cout << "NO" << endl;
        return;
    }
    for (int i = 1 ; i <= n ; i++) {
        if (s[i-1] == '0') {
            has0 = true;
            sumA += p[i]/2 + 1;
        }
        else {
            has1 = true;
            sumB += p[i]/2 + 1;
        }
    }
    if (has1 && has0) {
        if (x >= sumA && y >= sumB) {
            cout << "YES" << endl;
            return;
        }
        cout << "NO" << endl;
        return;
    }
    if (has0) {
        if (x >= sumA && y <= x-n) {
            cout << "YES" << endl;
            return;
        }
        cout << "NO" << endl;
        return;
    }
    if (has1) {
        if (y >= sumB && x <= y-n) {
            cout << "YES" << endl;
            return;
        }
        cout << "NO" << endl;
        return;
    }
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
