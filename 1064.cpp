#include <bits/stdc++.h>
using namespace std;
#define int long long
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n,m;
int price[70],val[70],fa[70];
int mp[70][3],mv[70][3];
int cnt[70],dp[32010];

void solve(){
    cin >> n >> m;
    for (int i = 1 ; i <= m ; i++) {
        int v,p;
        cin >> v >> p >> fa[i];
        if (!fa[i]) {
            price[i] = v;
            val[i] = v*p;
        }
        else {
            cnt[fa[i]]++;
            mp[fa[i]][cnt[fa[i]]] = v;
            mv[fa[i]][cnt[fa[i]]] = v*p;
        }
    }
    for (int i = 1 ; i <= m ; i++) {
        if (fa[i]) continue;
        for (int j = n ; j >= price[i] ; j--) {
            dp[j] = max(dp[j],dp[j-price[i]]+val[i]);
            if (cnt[i] >= 1 && j >= price[i] + mp[i][1]) {
                dp[j] = max(dp[j],dp[j-price[i]-mp[i][1]]+val[i]+mv[i][1]);
            }
            if (cnt[i] >= 2 && j >= price[i] + mp[i][2]) {
                dp[j] = max(dp[j],dp[j-price[i]-mp[i][2]]+val[i]+mv[i][2]);
            }
            if (cnt[i] >= 2 && j >= price[i] + mp[i][1] + mp[i][2]) {
                dp[j] = max(dp[j],dp[j-price[i]-mp[i][1]-mp[i][2]]+val[i]+mv[i][1]+mv[i][2]);
            }
        }
    }
    cout << dp[n] << endl;
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    //cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
}
