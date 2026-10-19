#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define INF 0x3f3f3f3f3f3f3f3f
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 1e6+10;
int n,m;
int a[N];
int lazy[N];

void solve(int CASE) {
    cin >> n >> m;
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
    }
    int b = sqrt(n);
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x,y; cin >> x >> y;
            if (x > b) {
                int idx = x;
                while (idx <= n) {
                    a[idx] += y;
                    idx += x;
                }
            }
            else {
                lazy[x] += y;
            }
        }
        else if (op == 2) {
            int j;
            cin >> j;
            if (!j){
                cout << 0 << endl;
                continue;
            }
            int ans = a[j];
            for (int i = 1 ; i <= b ; i++) {
                if (j % i == 0) {
                    ans += lazy[i];
                }
            }
            cout << ans << endl;
        }
    }
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