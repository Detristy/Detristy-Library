#include <bits/stdc++.h>
using namespace std;
#define int long long

int n;
int a[110];

void solve() {
    cin >> n;
    for (int i = 1 ; i <= n ; i++) cin >> a[i];
    int res = a[n]-a[1];
    for (int i = 2 ; i <= n ; i++) {
        res = gcd(res,abs(a[i]-a[1]));
    }
    vector<int> v;
    if (res > 1) v.push_back(res);
    for (int i = 2 ; i*i <= res ; i++) {
        if (res % i == 0) {
            v.push_back(i);
            if (res/i != i) v.push_back(res/i);
        }
    }
    if (!v.size()) {
        cout << -1 << endl;
        return;
    }
    sort(v.begin(), v.end());
    for (auto i : v) {
        cout << i << ' ';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T = 1;
    //cin >> T;
    while (T--) solve();
    return 0;
}