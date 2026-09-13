#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

const int N = 2e5+10;
int n,k;

struct segment_tree {
    int lazy[N*4];
    int mx[N*4];
    void pushdown(int x,int l,int r) {
        if (!lazy[x]) return;
        lazy[x*2] += lazy[x];
        lazy[x*2+1] += lazy[x];
        mx[x*2] += lazy[x];
        mx[x*2+1] += lazy[x];
        lazy[x] = 0;
    }
    void build(int x = 1,int l = 1,int r = n) {
        lazy[x] = 0;
        if (l == r) {
            mx[x] = 0;
            return;
        }
        int mid = (l+r)/2;
        build(x*2,l,mid);
        build(x*2+1,mid+1,r);
        mx[x] = max(mx[x*2],mx[x*2+1]);
    }
    void mergeS(int ql,int qr,int val,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) {
            lazy[x] += val;
            mx[x] += val;
            return;
        }
        pushdown(x,l,r);
        int mid = (l+r)/2;
        if (ql <= mid) mergeS(ql,qr,val,x*2,l,mid);
        if (mid < qr) mergeS(ql,qr,val,x*2+1,mid+1,r);
        mx[x] = max(mx[x*2],mx[x*2+1]);
    }
}t;

void solve() {
    cin >> n >> k;
    t.build();
    vector<pair<int,int>> v(n+1);
    for (int i = 1 ; i <= n ; i++) {
        cin >> v[i].first >> v[i].second;
    }
    int mxlen = 0;
    int l = 1,r = 1;
    for (; r <= n ; r++) {
        t.mergeS(v[r].first,v[r].second,1);
        while (t.mx[1] > k) {
            t.mergeS(v[l].first,v[l].second,-1);
            l++;
        }
        mxlen = max(mxlen,r-l+1);
    }
    cout << mxlen << endl;
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
    return 0;
}