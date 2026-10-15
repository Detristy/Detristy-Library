#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define INF 0x3f3f3f3f3f3f3f3f
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 1e5+10;
constexpr int MOD = 1e8-3;
int n;
int a[N],b[N];
int libA[N],libB[N];
int rk[N];

struct BIT {
    int t[N];
    int lowbit(int x){
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

void solve(int CASE) {
    cin >> n;
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
        libA[i] = a[i];
    }
    for (int i = 1 ; i <= n ; i++) {
        cin >> b[i];
        libB[i] = b[i];
    }
    sort(libA+1,libA+1+n);
    sort(libB+1,libB+1+n);
    for (int i = 1 ; i <= n ; i++) {
        a[i] = lower_bound(libA+1,libA+1+n,a[i]) - libA + 1;
        b[i] = lower_bound(libB+1,libB+1+n,b[i]) - libB + 1;
    }
    for (int i = 1 ; i <= n ; i++) {
        rk[a[i]] = i;
    }
    for (int i = 1 ; i <= n ; i++) {
        b[i] = rk[b[i]];
    }
    int ans = 0;
    for (int i = 1 ; i <= n ; i++) {
        t.add(b[i],1);
        ans = (ans + i - t.query(b[i])) % MOD;
    }
    cout << ans << endl;
}

signed main() {
    Detristy;
    int DETRISTY = 1,Det = 1;
    //cin >> DETRISTY;
    while (Det <= DETRISTY) {
        solve(Det++);
    }
    return 0;
}