#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n,m;

struct BIT {
    int t[500010];
    int lowbit(int x) {
        return x & -x;
    }
    void add(int x,int y) {
        for (; x <= n ; x += lowbit(x)) t[x] += y;
    }
    int query(int x) {
        int ans = 0;
        for (; x ; x -= lowbit(x)) ans += t[x];
        return ans;
    }
}t;

void solve() {
    cin >> n >> m;
    for (int i = 1 ; i <= n ; i++) {
        int k; cin >> k;
        t.add(i,k);
    }
    for (int i = 1 ; i <= m ; i++) {
        int op,x,y;
        cin >> op >> x >> y;
        if (op == 1) t.add(x,y);
        else cout << t.query(y) - t.query(x-1) << endl;
    }

}

signed main() {
    Detristy;
    int DETRISTY = 1;
    //cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
}
