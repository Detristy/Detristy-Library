#include<bits/stdc++.h>
using namespace std;
#define int long long

int n,q;
constexpr int N = 2e5+10;
int a[N];

//线段树板子
struct segmentTree {
    int mn[N*4];
    void build(int x = 1,int l = 1, int r = n) {
        if (l==r) {
            mn[x] = a[l];
            return;
        }
        int mid = (l+r)/2;
        build(x*2,l,mid);
        build(x*2+1,mid+1,r);
        mn[x] = min(mn[x*2],mn[x*2+1]);
    }
    void mergeP(int pos,int val,int x = 1,int l = 1,int r = n) {
        if (l == r) {
            mn[x] = val;
            return;
        }
        int mid = (l+r)/2;
        if (pos <= mid) mergeP(pos,val,x*2,l,mid);
        else mergeP(pos,val,x*2+1,mid+1,r);
        mn[x] = min(mn[x*2],mn[x*2+1]);
    }
    int query(int ql,int qr,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) return mn[x];
        int mid = (l+r)/2;
        int ans = 1e18;
        if (ql <= mid) ans = min(ans,query(ql,qr,x*2,l,mid));
        if (mid < qr) ans = min(ans, query(ql,qr,x*2+1,mid+1,r));
        return ans;
    }
}t;

void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    t.build();
    while (q--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) {
            t.mergeP(l, r);
        } else {
        //二分
            int L = 0, R = r - l,ans_d = -1;
            while (L <= R) {
                int mid = (L+R)/2;
                if (t.query(l, l + mid) >= mid) ans_d = mid,L = mid + 1;
                else R = mid - 1;
            }
            if (ans_d != -1 && t.query(l, l + ans_d) == ans_d) cout << "1\n";
            else cout << "0\n";
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T = 1;
    cin >> T;
    while (T--) solve();
    return 0;
}