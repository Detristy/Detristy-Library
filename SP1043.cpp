#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n,m;
constexpr int N = 5e4+10;
int a[N];

struct SegmentTree {
    struct node {
        ll sum,mxpre,mxsuf,mxsum;
    }t[N*4];
    void build(int x = 1,int l = 1,int r = n) {
        if (l == r) {
            t[x] = {a[l],a[l],a[l],a[l]};
            return;
        }
        int mid = (l+r)/2;
        build(x*2,l,mid);
        build(x*2+1,mid+1,r);
        t[x].sum = t[x*2].sum + t[x*2+1].sum;
        t[x].mxpre = max(t[x*2].mxpre, t[x*2].sum + t[x*2+1].mxpre);
        t[x].mxsuf = max(t[x*2+1].sum + t[x*2].mxsuf , t[x*2+1].mxsuf);
        t[x].mxsum = max(max(t[x*2].mxsum , t[x*2+1].mxsum),t[x*2].mxsuf+t[x*2+1].mxpre);
    }
    node query(int ql,int qr,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) return t[x];
        int mid = (l+r)/2;

        if (ql > mid) return query(ql,qr,x*2+1,mid+1,r);
        if (qr <= mid) return query(ql,qr,x*2,l,mid);
        
        node R = query(ql,qr,x*2+1,mid+1,r);
        node L = query(ql,qr,x*2,l,mid);

        node p;
        p.sum = L.sum + R.sum;
        p.mxpre = max(L.mxpre,L.sum+R.mxpre);
        p.mxsuf = max(R.sum+L.mxsuf,R.mxsuf);
        p.mxsum = max(max(L.mxsum,R.mxsum),L.mxsuf+R.mxpre);
        return p;
    }
}t;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>n;
    for (int i = 1;i <= n;i ++) cin>>a[i];
    t.build();
    cin>>m;
    while (m--) {
        int l,r;
        cin>>l>>r;
        cout << t.query(l,r).mxsum << "\n";
    }
    return 0;
}