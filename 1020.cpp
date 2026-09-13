#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

constexpr int N = 1e5+10;
vector<int> v;

void solve() {
    int a;
    while (cin >> a) {
        v.push_back(a);
    }
    vector<int> dp;
    for (int x : v) {
        if (dp.empty() || x <= dp.back()) dp.push_back(x);
        else {
            int idx = upper_bound(dp.begin(), dp.end(), x,greater()) - dp.begin();
            dp[idx] = x;
        }
    }
    cout << dp.size() << endl;
    vector<int> dp2;
    for (int x : v) {
        if (dp2.empty() || x > dp2.back()) dp2.push_back(x);
        else {
            int idx = lower_bound(dp2.begin(), dp2.end(), x) - dp2.begin();
            dp2[idx] = x;
        }
    }
    cout << dp2.size() << endl;
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