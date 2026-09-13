#include <bits/stdc++.h>
#include <pstl/algorithm_fwd.h>
using namespace std;
typedef long long ll;

int n,m;
const int N = 1e5+10;
ll a[N];

struct segment_tree {
    ll rt[N*4];
    ll lazy[N*4];

    void pushdown(int x,int l,int r) {
        if (!lazy[x]) return;
        int mid = (l+r)/2;
        rt[x*2] += (mid-l+1)*lazy[x];
        rt[x*2+1] += (r-mid)*lazy[x];
        lazy[x*2] += lazy[x];
        lazy[x*2+1] += lazy[x];
        lazy[x] = 0;
    }
    void build(int x = 1,int l = 1,int r = n) {
        if (l == r) {
            rt[x] = a[l];
            return;
        }
        ll mid = (l+r)/2;
        build(x*2,l,mid);
        build(x*2+1,mid+1,r);
        rt[x] = rt[x*2] + rt[x*2+1];
    }
    void mergeP(int pos,ll val,int x = 1,int l = 1,int r = n) {
        if (l == r) {
            rt[x] = val;
            return;
        }
        pushdown(x,l,r);
        ll mid = (l+r)/2;
        if (pos <= mid) mergeP(pos,val,x*2,l,mid);
        else mergeP(pos,val,x*2+1,mid+1,r);
        rt[x] = rt[x*2] + rt[x*2+1];
    }
    void mergeS(int ql,int qr,ll val,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) {
            rt[x] += (r-l+1) * val;
            lazy[x] += val;
            return;
        }
        pushdown(x,l,r);
        ll mid = (l+r)/2;
        if (ql <= mid) mergeS(ql,qr,val,x*2,l,mid);
        if (mid < qr) mergeS(ql,qr,val,x*2+1,mid+1,r);
        rt[x] = rt[x*2] + rt[x*2+1];
    }
    ll query(int ql,int qr,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) return rt[x];
        pushdown(x,l,r);
        ll mid = (l+r)/2;
        ll ans = 0;
        if (ql <= mid) ans += query(ql,qr,x*2,l,mid);
        if (mid < qr) ans += query(ql,qr,x*2+1,mid+1,r);
        return ans;
    }
}t;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> m;
    for (int i = 1 ; i <= n ; i++) cin >> a[i];
    t.build();
    while (m--) {
        ll op,x,y,k;
        cin >> op >> x >> y;
        if (op == 1) {
            cin >> k;
            t.mergeS(x,y,k);
        }
        else {
            cout << t.query(x,y) << '\n';
        }
    }
}