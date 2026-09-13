#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n,m;
const int N = 2e5+10;
ll h[N];

struct segment_tree {
    ll rt[N*4];
    ll lazy[N*4];
    void pushdown(int x,int l,int r) {
        if (!lazy[x]) return;
        rt[2*x] += lazy[x];
        rt[2*x+1] += lazy[x];
        lazy[2*x] += lazy[x];
        lazy[2*x+1] += lazy[x];
        lazy[x] = 0;
    }
    void build(int x = 1,int l = 1,int r = n) {
        if (l == r) {
            rt[x] = h[l];
            return;
        }
        int mid = (l+r)/2;
        build(x*2,l,mid);
        build(x*2+1,mid+1,r);
        rt[x] = max(rt[x*2],rt[x*2+1]);
    }
    void mergeP(int pos,ll val,int x = 1,int l = 1,int r = n) {
        if (l == r) {
            if (rt[x] < val) rt[x] = val;
            return;
        }
        pushdown(x,l,r);
        int mid = (l+r)/2;
        if (pos <= mid) mergeP(pos,val,x*2,l,mid);
        else mergeP (pos,val,x*2+1,mid+1,r);
        rt[x] = max(rt[x*2],rt[x*2+1]);
    }
    ll query(int ql,int qr,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) return rt[x];
        pushdown(x,l,r);
        int mid = (l+r)/2;
        ll ans = -0x3f3f3f3f;
        if (ql <= mid) ans = max(ans,query(ql,qr,x*2,l,mid));
        if (mid < qr) ans = max(ans,query(ql,qr,x*2+1,mid+1,r));
        return ans;
    }
}t;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> m;
    for (int i = 1 ; i <= n ; i++) cin >> h[i];
    t.build();
    while (m--) {
        char c; int a,b;
        cin >> c >> a >> b;
        if (c == 'Q') {
            cout << t.query(a,b) << '\n';
        }
        else {
            if (h[a] < b) t.mergeP(a,b);
        }
    }
}
