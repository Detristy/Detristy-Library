#include <bits/stdc++.h>
using namespace std;
typedef long double ll;

int n,m;
const int N = 1e5+10;
double a[N];

struct segmentTree {
    double t[N*4];
    double lazy[N*4];
    double sq[N*4];

    void pushdown(int x,int l,int r) {
        if (!lazy[x]) return;
        int mid = (l+r)/2;
        //区间平方和的逻辑，记得要写在 t[x] 的更新前面
        sq[x*2] += 2 * t[x*2] * lazy[x] + (mid - l + 1) * lazy[x] * lazy[x];
        sq[x*2+1] += 2 * t[x*2+1] * lazy[x] + (r - mid) * lazy[x] * lazy[x];
        
        t[x*2] += (mid - l + 1) * lazy[x];
        t[x*2+1] += (r-mid) * lazy[x];
        
        lazy[x*2] += lazy[x];
        lazy[x*2+1] += lazy[x];
        lazy[x] = 0;
    }
    void build(int x = 1,int l = 1,int r = n) {
        if (l == r) {
            t[x] = a[l];
            sq[x] = a[l] * a[l]; //sq的初始化
            return;
        }
        int mid = (l + r)/2;
        build(x*2,l,mid);
        build(x*2+1,mid+1,r);
        t[x] = t[x*2] + t[x*2+1];
        sq[x] = sq[x*2] + sq[x*2+1];
    }
    void mergeS(int ql,int qr,double val,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) {
            sq[x] += 2 * val * t[x] + (r - l + 1) * val * val; //区间修改
            t[x] += (r-l+1) * val;
            lazy[x] += val;
            return;
        }
        pushdown(x,l,r);
        int mid = (l + r)/2;
        if (ql <= mid) mergeS(ql,qr,val,x*2,l,mid);
        if (mid < qr) mergeS(ql,qr,val,x*2+1,mid+1,r);
        t[x] = t[x*2] + t[x*2+1];
        sq[x] = sq[x*2] + sq[x*2+1];
    }
    double querySum(int ql,int qr,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) {
            return t[x];
        }
        pushdown(x,l,r);
        int mid = (l + r)/2;
        double ans = 0;
        if (ql <= mid) ans += querySum(ql,qr,x*2,l,mid);
        if (mid < qr) ans += querySum(ql,qr,x*2+1,mid+1,r);
        return ans;
    }
    double querySq(int ql,int qr,int x = 1,int l = 1, int r = n) {
        if (ql <= l && r <= qr) return sq[x];
        pushdown(x,l,r);
        int mid = (l + r)/2;
        double ans = 0;
        if (ql <= mid) ans += querySq(ql,qr,x*2,l,mid);
        if (mid < qr) ans += querySq(ql,qr,x*2+1,mid+1,r);
        return ans;
    }
}t;

int main(){
    cin >> n >> m;
    for (int i = 1 ; i <= n ; i++) cin >> a[i];
    t.build();
    while (m--) {
        int op,l,r;
        cin >> op >> l >> r;
        if (op == 1) {
            double k; cin >> k;
            t.mergeS(l,r,k);
        }
        if (op == 2) {
            double len = (double)(r - l + 1);
            cout << fixed << setprecision(4) << t.querySum(l,r) / len << '\n';
        }
        if (op == 3) {
            double len = (double)(r - l + 1);
            double tmp = t.querySum(l,r)/len;
            double sum = t.querySq(l,r)/len - tmp * tmp;
            cout << fixed << setprecision(4) << sum << '\n';
        }
    }
}