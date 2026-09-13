#include <bits/stdc++.h>
using namespace std;
#define int long long

int n,k;
int cnt[2005],dp[10][105][2005];
vector<int> v;

int cnt_one(int x) {
    int ans = 0;
    while (x) {
        if (x&1) ans++;
        x /= 2;
    }
    return ans;
}

void solve() {
    cin >> n >> k;
    for (int i = 0 ; i < 1<<n ; i++) {
        if (!(i & i<<1)) {
            v.push_back(i);
            cnt[v.size()-1] = cnt_one(i);
        }
    }
    for (int i = 0 ; i < v.size() ; i++) {
        if (cnt[i] <= k) dp[1][cnt[i]][i] = 1;
    }
    for (int i = 2 ; i <= n ; i++) {
        for (int j = 0 ; j <= k ; j++) {
            for (int l = 0 ; l < v.size() ; l++) {
                int s1 = v[l];
                if (cnt[l] > j) continue;
                for (int r = 0 ; r < v.size(); r++) {
                    int s2 = v[r];
                    if (!(s1 & s2) && !(s1 & s2<<1) && !(s1 & s2>>1)) {
                        dp[i][j][l] += dp[i-1][j-cnt[l]][r];
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0 ; i < v.size() ; i++) {
        ans += dp[n][k][i];
    }
    cout << ans << endl;
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