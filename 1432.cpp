#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

constexpr int N = 1e5+10;
int a[N];
int n,m;

struct segment_tree {
    int rt[N*4];
    int lazy[N*4];

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
        lazy[x] = 0;
        if (l == r) {
            rt[x] = a[l] - a[l-1];
            return;
        }
        int mid = (l+r)/2;
        build(x*2,l,mid);
        build(x*2+1,mid+1,r);
        rt[x] = rt[x*2] + rt[x*2+1];
    }
    void mergeS(int ql,int qr,int val,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) {
            rt[x] += (r-l+1) * val;
            lazy[x] += val;
            return;
        }
        pushdown(x,l,r);
        int mid = (l+r)/2;
        if (ql <= mid) mergeS(ql,qr,val,x*2,l,mid);
        if (mid < qr) mergeS(ql,qr,val,x*2+1,mid+1,r);
        rt[x] = rt[x*2] + rt[x*2+1];
    }
    int query(int ql,int qr,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) return rt[x];
        pushdown(x,l,r);
        int mid = (l+r)/2;
        int ans = 0;
        if (ql <= mid) ans += query(ql,qr,x*2,l,mid);
        if (mid < qr) ans += query(ql,qr,x*2+1,mid+1,r);
        return ans;
    }
}t;

void solve() {
    cin >> n >> m;
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
    }
    t.build();
    for (int i = 1 ; i <= m ; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int l,r,k,d;
            cin >> l >> r >> k >> d;
            t.mergeS(l,l,k);
            if (l+1 <= r) t.mergeS(l+1,r,d);
            if (r+1 <= n) {
                int sum = k + (r-l)*d;
                t.mergeS(r+1,r+1,-sum);
            }
        }
        else if (op == 2) {
            int x;
            cin >> x;
            cout << t.query(1,x) << endl;
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
    return 0;
}