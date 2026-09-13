#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

void solve() {
    int n;
    cin >> n;
    if (n == 1 || n == 2) {
        cout << -1 << endl;
    }
    else {
        int tmp = n/3;
        if (n%2 != tmp%2) {
            tmp--;
        }
        if (tmp <= 0) cout << -1 << endl;
        else cout << tmp << endl;
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