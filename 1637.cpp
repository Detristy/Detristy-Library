#include <bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 1e5+10;
int n;
int a[N],b[N],l[N],r[N];

struct BIT {
    int tree[N];
    int lowbit(int x) {
        return x & -x;
    }
    void add(int x,int val) {
        for (; x <= N ; x += lowbit(x)) tree[x] += val;
    }
    int query(int x) {
        int ans = 0;
        for (; x ; x -= lowbit(x)) ans += tree[x];
        return ans;
    }
}t;

void solve() {
    cin >> n;
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
    }
    for (int i = 1 ; i <= n ; i++) {
        l[i] += t.query(a[i]-1);
        t.add(a[i],1);
    }
    memset(t.tree,0,sizeof(t.tree));
    for (int i = n ; i >= 1 ; i--) {
        r[i] += n - i - t.query(a[i]);
        t.add(a[i],1);
    }
    int ans = 0;
    for (int i = 1 ; i <= n ; i++) ans += l[i] * r[i];
    cout << ans << endl;
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