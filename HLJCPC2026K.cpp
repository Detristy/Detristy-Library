#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> a(2*n+2);
    for (int i = 1 ; i <= n ; i++) {
        a[i] = i;
        a[n+i] = i;
    }
    if (m > n/2) m = n/2;
    for (int i = m+1 ; i <= n+m ; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
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