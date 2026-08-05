#include <bits/stdc++.h>
using namespace std;
#define int long long
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int a[10],dp[1010];
int w[10]={0,1,2,3,5,10,20};

void solve(){
    for(int i = 1 ; i <= 6 ; i++) {
        cin >> a[i];
    }
    dp[0] = 1;
    for (int i = 1 ; i <= 6 ; i++) {
        for (int k = 1000 ; k >= 0 ; k--) {
            for (int j = 1 ; j <= a[i] ; j++) {
                if (k-j*w[i] >= 0 && dp[k-j*w[i]]) {
                    dp[k] = 1;
                }
            }
        }
    }
    int cnt = 0;
    for (int i = 1 ; i <= 1000 ; i++) {
        if (dp[i]) cnt++;
    }
    cout << "Total=" << cnt << endl;
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    //cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
}
