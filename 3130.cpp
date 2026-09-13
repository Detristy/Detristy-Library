#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n,q;
constexpr int N = 2e5+10;
int a[N];

struct SegmentTree {
    ll t[N*4];
    ll mn[N*4];
    ll lazy[N*4];
    void pushdown(int x,int l,int r) {
        if (!lazy[x]) return;
        int mid = (l+r)/2;
        t[x*2] += (mid-l+1) * lazy[x];
        t[x*2+1] += (r-mid) * lazy[x];

        mn[x*2] += lazy[x];
        mn[x*2+1] += lazy[x];

        lazy[x*2] += lazy[x];
        lazy[x*2+1] += lazy[x];
        lazy[x] = 0;
    }
    void build(int x = 1, int l = 1, int r = n) {
        if (l == r) {
            t[x] = a[l];
            mn[x] = a[l];
            return;
        }
        int mid = (l+r) /2;
        build(x*2,l,mid);
        build(x*2+1,mid+1,r);
        t[x] = t[2*x] + t[2*x+1];
        mn[x] = min(mn[2*x],mn[2*x+1]);
    }
    void mergeS(int ql,int qr,int val,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) {
            t[x] += (ll)(r-l+1) * val;
            mn[x] += val;
            lazy[x] += val;
            return;
        }
        pushdown(x,l,r);
        int mid = (l+r)/2;
        if (ql <= mid) mergeS(ql,qr,val,x*2,l,mid);
        if (mid < qr) mergeS(ql,qr,val,x*2+1,mid+1,r);
        t[x] = t[x*2] + t[2*x+1];
        mn[x] = min(mn[2*x],mn[2*x+1]);
    }
    ll querySum(int ql,int qr,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) return t[x];
        pushdown(x,l,r);
        int mid = (l+r)/2;
        ll ans = 0;
        if (ql <= mid) ans += querySum(ql,qr,x*2,l,mid);
        if (mid < qr) ans += querySum(ql,qr,x*2+1,mid+1,r);
        return ans;
    }
    ll queryMin(int ql,int qr,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) return mn[x];
        pushdown(x,l,r);
        int mid = (l+r)/2;
        ll ans = 2e18;
        if (ql <= mid) ans = min(ans,queryMin(ql,qr,x*2,l,mid));
        if (mid < qr) ans = min(ans,queryMin(ql,qr,x*2+1,mid+1,r));
        return ans;
    }
}t;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> q;
    for (int i = 1 ; i <= n ; i++) cin >> a[i];
    t.build();
    while (q--) {
        char op; cin >> op;
        int x,y; cin >> x >> y;
        if (op == 'M') cout << t.queryMin(x,y) << '\n';
        if (op == 'P') {
            int c; cin >> c;
            t.mergeS(x,y,c);
        }
        if (op == 'S') cout << t.querySum(x,y) << '\n';
    }
    return 0;
}