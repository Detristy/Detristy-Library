#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n,q,m;
const int N = 1e5+10;
ll a[N];

struct segment_tree {
    ll rt[N*4];
    ll lm[N*4],la[N*4];

    void pushdown(int x,int l,int r) {
        if (lm[x] == 1 && !la[x]) return;
        int mid = (l+r)/2;
        rt[x*2] = lm[x]*rt[x*2]+(mid-l+1)*la[x];
        rt[x*2+1] = lm[x]*rt[x*2+1]+(r-mid)*la[x];
        rt[x*2] %= m;
        rt[x*2+1] %= m;

        lm[x*2] *= lm[x];
        lm[x*2+1] *= lm[x];
        lm[x*2] %= m;
        lm[x*2+1] %= m;

        la[x*2] *= lm[x];
        la[x*2+1] *= lm[x];
        la[x*2] += la[x];
        la[x*2+1] += la[x];
        la[x*2] %= m;
        la[x*2+1] %= m;

        lm[x] = 1;
        la[x] = 0;
    }
    void build(int x = 1,int l = 1,int r = n) {
        lm[x]=1;
        if (l == r) {
            rt[x] = a[l];
            return;
        }
        ll mid = (l+r)/2;
        build(x*2,l,mid);
        build(x*2+1,mid+1,r);
        rt[x] = rt[x*2] + rt[x*2+1];
        rt[x] %= m;
    }
    void mergeS_Add(int ql,int qr,ll val,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) {
            rt[x] += (r-l+1) * val, rt[x] %= m;
            la[x] += val, la[x] %= m;
            return;
        }
        pushdown(x,l,r);
        ll mid = (l+r)/2;
        if (ql <= mid) mergeS_Add(ql,qr,val,x*2,l,mid);
        if (mid < qr) mergeS_Add(ql,qr,val,x*2+1,mid+1,r);
        rt[x] = rt[x*2] + rt[x*2+1];
        rt[x] %= m;
    }
    void mergeS_Mul(int ql,int qr,ll val,int x = 1 ,int l = 1,int r = n) {
        if (ql <= l && r <= qr) {
            rt[x] *= val, rt[x] %= m;
            la[x] *= val, la[x] %= m;
            lm[x] *= val, lm[x] %= m;
            return;
        }
        pushdown(x,l,r);
        ll mid = (l+r)/2;
        if (ql <= mid) mergeS_Mul(ql,qr,val,x*2,l,mid);
        if (mid < qr) mergeS_Mul(ql,qr,val,x*2+1,mid+1,r);
        rt[x] = rt[x*2] + rt[x*2+1];
        rt[x] %= m;
    }
    ll query(int ql,int qr,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) return rt[x];
        pushdown(x,l,r);
        ll mid = (l+r)/2;
        ll ans = 0;
        if (ql <= mid) ans += query(ql,qr,x*2,l,mid);
        if (mid < qr) ans += query(ql,qr,x*2+1,mid+1,r);
        return ans%m;
    }
}t;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> q >> m;
    for (int i = 1 ; i <= n ; i++) cin >> a[i];
    t.build();
    while (q--) {
        ll op,x,y,k;
        cin >> op >> x >> y;
        if (op == 1) {
            cin >> k;
            t.mergeS_Mul(x,y,k);
        }
        else if (op == 2) {
            cin >> k;
            t.mergeS_Add(x,y,k);
        }
        else if (op == 3) {
            cout << t.query(x,y) << "\n";
        }
    }
}