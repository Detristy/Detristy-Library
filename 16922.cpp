#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n;
int a[8010], b[8010];

struct BIT {
    int t[8010];
    int lowbit(int x) {
        return x & -x;
    }
    void add(int x,int val) {
        for (;x<=n;x += lowbit(x)) t[x] += val;
    }
    int query(int x) {
        int ans = 0;
        for (;x;x -= lowbit(x)) ans += t[x];
        return ans;
    }
}t;

void solve() {
    cin >> n;
    memset(b,0,sizeof(b));
    memset(a,0,sizeof(a));
    memset(t.t,0,sizeof(t.t));
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b+1,b+1+n);
    int cnt = 0;
    for (int i = 1 ; i <= n ; i++) {
        int val = lower_bound(b+1,b+1+n,a[i]) - b;
        cnt += (i - 1 - t.query(val));
        t.add(val,1);
    }
    vector<vector<int>> dp1(n+1,vector<int>(n+1,0));
    vector<vector<int>> dp2(n+1,vector<int>(n+1,0));
    for (int len = 2 ; len <= n ; len++) {
        for (int l = 1 ; l <= n-len+1 ; l++) {
            int r = l+len-1;
            dp1[l][r] = dp1[l+1][r] + dp1[l][r-1] - dp1[l+1][r-1] + (a[l] == a[r] ? 1 : 0);
            dp2[l][r] = dp2[l+1][r] + dp2[l][r-1] - dp2[l+1][r-1] + (a[l] > a[r] ? 1 : 0);
        }
    }
    int mx = cnt;
    for (int l = 1 ; l <= n ; l++) {
        for (int r = 1 ; r <= n ; r++) {
            if (r > l) {
                mx = max(mx, cnt + (r-l+1)*(r-l)/2 - dp1[l][r] - 2 * dp2[l][r]);
            }
        }
    }
    cout << mx << endl;
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