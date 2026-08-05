#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> a(n+1);
    vector<int> b(m+1);
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
    }
    for (int i = 1 ; i <= m ; i++) {
        cin >> b[i];
    }
    if (n < 2*m) {
        cout << "No" << endl;
        return;
    }
    sort(a.begin()+1,a.end());
    sort(b.begin()+1,b.end());
    bool flag = true;
    for (int i = 1 ; i <= m ; i++) {
        if (a[i] > b[i]) {
            flag = false;
            break;
        }
        if (a[n-m+i] < b[i]) {
            flag = false;
            break;
        }
    }
    if (flag) cout << "Yes" << endl;
    else cout << "No" << endl;
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