#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n,m;
const int N = 2e5+10;
int h[N];

struct segment_tree {
    ll rt[N*4];
    int lazy[N*4];

    void pushdown(int x,int l,int r) {
        if (!lazy[x]) return;
        int mid = (l+r)/2;
        rt[x*2] = (mid-l+1) - rt[x*2];
        rt[x*2+1] = (r-mid) - rt[x*2+1];

        lazy[x*2] ^= 1;
        lazy[x*2+1] ^= 1;
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
        rt[x] = rt[x*2]+rt[x*2+1];
    }
    void mergeS(int ql,int qr,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) {
            rt[x] = (r-l+1) - rt[x];
            lazy[x] ^= 1;
            return;
        }
        pushdown(x,l,r);
        int mid = (l+r)/2;
        if (ql <= mid) mergeS(ql,qr,x*2,l,mid);
        if (qr > mid) mergeS(ql,qr,x*2+1,mid+1,r);
        rt[x] = rt[x*2]+rt[x*2+1];
    }
    ll query(int ql,int qr,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) return rt[x];
        pushdown(x,l,r);
        int mid = (l+r)/2;
        ll ans = 0;
        if (ql <= mid) ans += query(ql,qr,x*2,l,mid);
        if (qr > mid) ans += query(ql,qr,x*2+1,mid+1,r);
        return ans;
    }
}t;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> m;
    string s; cin >> s;
    for (int i = 0 ; i < n ; i++) h[i+1] = s[i]-'0';
    t.build();
    while (m--) {
        int op,a,b;
        cin >> op >> a >> b;
        if (op) cout << t.query(a,b) << '\n';
        else t.mergeS(a,b);
    }
}
