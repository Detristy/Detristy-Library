#include <bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 1e5+10;
int n,t,o;
int a[N];

struct segment_tree {
    int mask[N*4];
    int lazy[N*4];

    void pushdown(int x,int l,int r) {
        if (!lazy[x]) return;

        mask[x*2] = lazy[x];
        mask[x*2+1] = lazy[x];

        lazy[x*2] = lazy[x];
        lazy[x*2+1] = lazy[x];
        lazy[x] = 0;
    }
    void build(int x = 1,int l = 1,int r = n) {
        lazy[x] = 0;
        if (l == r) {
            mask[x] = 1;
            return;
        }
        int mid = (l+r)/2;
        build(x*2,l,mid);
        build(x*2+1,mid+1,r);
        mask[x] = mask[x*2] | mask[x*2+1];
    }
    void mergeS(int ql,int qr,int val,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) {
            mask[x] = val;
            lazy[x] = val;
            return;
        }
        pushdown(x,l,r);
        int mid = (l+r)/2;
        if (ql <= mid) mergeS(ql,qr,val,x*2,l,mid);
        if (mid < qr) mergeS(ql,qr,val,x*2+1,mid+1,r);
        mask[x] = mask[x*2] | mask[x*2+1];
    }
    int query(int ql,int qr,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) return mask[x];
        pushdown(x,l,r);
        int mid = (l+r)/2;
        int ans = 0;
        if (ql <= mid) ans |= query(ql,qr,x*2,l,mid);
        if (mid < qr) ans |= query(ql,qr,x*2+1,mid+1,r);
        return ans;
    }
}tree;

void solve() {
    cin >> n >> t >> o;
    tree.build();
    for (int i = 1 ; i <= o ; i++) {
        char op;
        cin >> op;
        if (op == 'C') {
            int l,r,color;
            cin >> l >> r >> color;
            if (l > r) swap(l,r);
            tree.mergeS(l,r,1<<(color-1));
        }
        else if (op == 'P') {
            int l,r;
            cin >> l >> r;
            if (l > r) swap(l,r);
            int msk = tree.query(l,r);
            int ans = 0;
            while (msk) {
                if (msk % 2) ans++;
                msk /= 2;
            }
            cout << ans << endl;
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