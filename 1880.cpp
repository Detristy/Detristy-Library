#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n;
int a[210],sum[210];
int dpmn[210][210],dpmx[210][210];

void solve() {
    cin >> n;
    memset(dpmn,0x3f,sizeof(dpmn));
    memset(dpmx,0,sizeof(dpmx));
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
        a[n+i] = a[i];
    }
    for (int i = 1 ; i <= 2*n ; i++) {
        sum[i] = sum[i-1] + a[i];
        dpmn[i][i] = dpmx[i][i] = 0;
    }
    for (int len = 2 ; len <= n ; len++) {
        for (int i = 1 ; i <= 2*n-len+1 ; i++) {
            int j = i + len - 1;
            for (int k = i ; k < j ; k++) {
                dpmn[i][j] = min(dpmn[i][j],dpmn[i][k] + dpmn[k+1][j] + sum[j] - sum[i-1]);
                dpmx[i][j] = max(dpmx[i][j],dpmx[i][k] + dpmx[k+1][j] + sum[j] - sum[i-1]);
            }
        }
    }
    int mx = 0,mn = 1e9;
    for (int i = 1 ; i <= n ; i++) {
        mx = max(mx,dpmx[i][i+n-1]);
        mn = min(mn,dpmn[i][i+n-1]);
    }
    cout << mn << endl;
    cout << mx << endl;
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    //cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
}
