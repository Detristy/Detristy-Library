#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n,m;
int a[500010];

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
        cin >> a[i];
        t.add(i,a[i]-a[i-1]);
    }
    for (int i = 1 ; i <= m ; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int x,y,k;
            cin >> x >> y >> k;
            t.add(x,k);
            t.add(y+1,-k);
        }
        else {
            int x;
            cin >> x;
            cout << t.query(x) << endl;
        }
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
