#include <bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 1e6+10;
int a[N];
int n,q;

struct SegmentTree {
    int t[N*4];
    int mx[N*4];
    int lazyAdd[N*4];
    int lazyCover[N*4];
    bool hasCover[N*4];
    void pushdown(int x,int l,int r) {
        int mid = (l+r)/2;
        if (hasCover[x]) {
            t[x*2] = (mid-l+1) * lazyCover[x];
            t[x*2+1] = (r-mid) * lazyCover[x];

            mx[x*2] = lazyCover[x];
            mx[x*2+1] = lazyCover[x];

            lazyCover[x*2] = lazyCover[x];
            lazyCover[x*2+1] = lazyCover[x];

            lazyAdd[x*2] = 0;
            lazyAdd[x*2+1] = 0;

            hasCover[x*2] = true;
            hasCover[x*2+1] = true;

            hasCover[x] = false;
            lazyCover[x] = 0;
        }
        if (lazyAdd[x]) {
            t[x*2] += (mid-l+1) * lazyAdd[x];
            t[x*2+1] += (r-mid) * lazyAdd[x];

            mx[x*2] += lazyAdd[x];
            mx[x*2+1] += lazyAdd[x];

            if (hasCover[x*2]) lazyCover[x*2] += lazyAdd[x];
            else lazyAdd[x*2] += lazyAdd[x];

            if (hasCover[x*2+1]) lazyCover[x*2+1] += lazyAdd[x];
            else lazyAdd[x*2+1] += lazyAdd[x];

            lazyAdd[x] = 0;
        }
    }
    void build(int x = 1, int l = 1, int r = n) {
        lazyCover[x] = 0;
        lazyAdd[x] = 0;
        hasCover[x] = false;
        if (l == r) {
            t[x] = a[l];
            mx[x] = a[l];
            return;
        }
        int mid = (l+r) /2;
        build(x*2,l,mid);
        build(x*2+1,mid+1,r);
        t[x] = t[2*x] + t[2*x+1];
        mx[x] = max(mx[2*x],mx[2*x+1]);
    }
    void mergeSAdd(int ql,int qr,int val,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) {
            t[x] += (r-l+1) * val;
            mx[x] += val;
            if (hasCover[x]) {
                lazyCover[x] += val;
            }
            else {
                lazyAdd[x] += val;
            }
            return;
        }
        pushdown(x,l,r);
        int mid = (l+r)/2;
        if (ql <= mid) mergeSAdd(ql,qr,val,x*2,l,mid);
        if (mid < qr) mergeSAdd(ql,qr,val,x*2+1,mid+1,r);
        t[x] = t[x*2] + t[2*x+1];
        mx[x] = max(mx[2*x],mx[2*x+1]);
    }
    void mergeSCov(int ql,int qr,int val,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) {
            t[x] = (r-l+1) * val;
            mx[x] = val;
            hasCover[x] = true;
            lazyCover[x] = val;
            lazyAdd[x] = 0;
            return;
        }
        pushdown(x,l,r);
        int mid = (l+r)/2;
        if (ql <= mid) mergeSCov(ql,qr,val,x*2,l,mid);
        if (mid < qr) mergeSCov(ql,qr,val,x*2+1,mid+1,r);
        t[x] = t[x*2] + t[2*x+1];
        mx[x] = max(mx[2*x],mx[2*x+1]);
    }
    int queryMax(int ql,int qr,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) return mx[x];
        pushdown(x,l,r);
        int mid = (l+r)/2;
        int ans = -1e18;
        if (ql <= mid) ans = max(ans,queryMax(ql,qr,x*2,l,mid));
        if (mid < qr) ans = max(ans,queryMax(ql,qr,x*2+1,mid+1,r));
        return ans;
    }
}t;

void solve() {
    cin >> n >> q;
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
    }
    t.build();
    for (int i = 1 ; i <= q ; i++) {
        int op; cin >> op;
        if (op == 1) {
            int l,r,x;
            cin >> l >> r >> x;
            t.mergeSCov(l,r,x);
        }
        else if (op == 2) {
            int l,r,x;
            cin >> l >> r >> x;
            t.mergeSAdd(l,r,x);
        }
        else if (op == 3) {
            int l,r;
            cin >> l >> r;
            cout << t.queryMax(l,r) << "\n";
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