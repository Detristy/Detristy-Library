#include <algorithm>
#include <iostream>
using namespace std;
#define int long long
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

struct it {
    int v,p;
}it [105];

int n,w;
int dp[105][305];

bool cmp(struct it a,struct it b) {
    return a.v < b.v;
}

void solve() {
    cin >> n >> w;
    for (int i = 1 ; i <= n ; i++) cin >> it[i].v >> it[i].p;
    sort(it+1,it+n+1,cmp);
    int ans = -1;
    for (int i = 1 ; i <= n ; i++) {
        int val = it[i].v,cnt = 0,idx = n;
        for (int j = i; j <= n ; j++) {
            if (it[j].v <= val+3) cnt++;
            if (it[j].v > val+3) {
                idx = j-1;
                break;
            }
        }
        for (int j = 0 ; j <= 100 ; j++) {
            for (int k = 0 ; k <= 300 ; k++) dp[j][k] = -1e9;
        }
        dp[0][0] = 0;
        for (int j = i ; j <= idx ; j++) {
            int delta = it[j].v-val;
            for (int k = cnt ; k >= 1 ; k--) {
                for (int q = 300 ; q >= delta ; q--) {
                    dp[k][q] = max(dp[k][q],dp[k-1][q-delta]+it[j].p);
                }
            }
        }
        for (int j = 0 ; j <= cnt ; j++) {
            for (int k = 0 ; k <= 300 ; k++) {
                if (val*j+k <= w) ans = max(ans,dp[j][k]);
            }
        }
    }
    cout << ans << '\n';
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    //cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
}
