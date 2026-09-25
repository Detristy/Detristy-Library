#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

void solve() {
    int n;
    cin >> n;
    vector<int> a(n+1,0);
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
    }
    vector<int> sufmn(n+2,1e9);
    for (int i = n ; i >= 1 ; i--) {
        sufmn[i] = min(a[i],sufmn[i+1]);
    }
    int ans = 0;
    for (int i = 1 ; i <= n ; i++) {
        ans += a[i] - sufmn[i];
    }
    int now = 0,mn = 1e9,sum = 0;
    for (int i = n ; i >= 1 ; i--) {
        if (a[i] < mn) {
            mn = a[i];
            now = i;
        }
        sum = max(sum,now - i);
    }
    ans += sum;
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