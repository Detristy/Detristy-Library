#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n,m;
constexpr int N = 5e5+10;
ll a[N],d[N];

struct segmentTree {
    ll t[N*4],g[N*4];
    void build(int x = 1,int l = 1,int r = n) {
        if (l == r) {
            t[x] = d[l];
            g[x] = d[l];
            return;
        }
        int mid = (l+r)/2;
        build(x*2,l,mid);
        build(x*2+1,mid+1,r);
        t[x] = t[x*2] + t[x*2+1];
        g[x] = __gcd(g[x*2],g[x*2+1]);
    }
    void merge(int pos,ll val,int x = 1,int l = 1,int r = n) {
        if (l == r) {
            t[x] += val;
            g[x] += val;
            return;
        }
        int mid = (l+r)/2;
        if (pos <= mid) merge(pos,val,x*2,l,mid) ;
        else merge(pos,val,x*2+1,mid+1,r);
        t[x] = t[x*2] + t[x*2+1];
        g[x] = __gcd(g[x*2],g[x*2+1]);
    }
    ll queryG(int ql,int qr,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) return g[x];
        int mid = (l+r)/2;
        ll ans = 0;
        if (ql <= mid) ans = queryG(ql,qr,x*2,l,mid);
        if (mid < qr) ans = __gcd(ans,queryG(ql,qr,x*2+1,mid+1,r));
        return ans;
    }
    ll querySum(int ql,int qr,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) return t[x];
        int mid = (l+r)/2;
        ll ans = 0;
        if (ql <= mid) ans += querySum(ql,qr,x*2,l,mid);
        if (mid < qr) ans += querySum(ql,qr,x*2+1,mid+1,r);
        return ans;
    }
}st;

int main() {
    cin >> n >> m;
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
        d[i] = a[i] - a[i-1];
    }
    st.build();
    while (m--) {
        char op; int l,r;
        cin >> op >> l >> r;
        if (op == 'C') {
            ll v; cin >> v;
            st.merge(l,v);
            if (r+1 <= n) st.merge(r+1,-v);
        }
        else {
            cout << abs(__gcd(st.querySum(1,l),st.queryG(l+1,r))) << '\n';
        }
    }
}