#include <iostream>
using namespace std;
#define int long long
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int s;
int a[1005],dp[1005];

int sum(int x) {
    int res = 0;
    for (int i = 1 ; i <= x/2 ; i++) {
        if (!(x%i)) res+=i;
    }
    return res;
}

void solve() {
    cin >> s;
    for (int i = 1 ; i <= s ; i++) a[i] = sum(i);
    for (int i = 1 ; i <= s ; i++) {
        for (int j = s ; j >= i ; j--) {
            dp[j] = max(dp[j],dp[j-i]+a[i]);
        }
    }
    cout << dp[s] << endl;
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    //cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
}
