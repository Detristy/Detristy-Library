#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

constexpr ll MOD = 1e9+7;
constexpr int N = 1e5+10;
int n,m;
ll b[N];

ll qpow(ll b,int p = MOD - 2,int m = MOD) {
    b %= m;
    ll s = 1 % m;
    for (;p;p >>= 1,b = (b * b) % m) {
        if (p & 1) s = s * b % m;
    }
    return s;
}

struct segmentTree {
    ll t[N*4];
    ll sq[N*4];
    void build(int x = 1,int l = 1,int r = n) {
        if (l == r) {
            t[x] = b[l];
            sq[x] = b[l] * b[l] % MOD;
            return;
        }
        int mid = (l+r)/2;
        build(x*2,l,mid);
        build(x*2+1,mid+1,r);
        t[x] = (t[x*2] + t[x*2+1]) % MOD;
        sq[x] = (sq[x*2] + sq[x*2+1]) % MOD;
    }
    void mergeP(int pos,ll val,int x = 1,int l = 1,int r = n) {
        if (l == r) {
            t[x] = val;
            sq[x] = (ll)(val * val) % MOD;
            return;
        }
        int mid = (l+r)/2;
        if (pos <= mid) mergeP(pos,val,x*2,l,mid);
        else mergeP(pos,val,x*2+1,mid+1,r);
        t[x] = (t[x*2] + t[x*2+1]) % MOD;
        sq[x] = (sq[x*2] + sq[x*2+1]) % MOD;
    }
    ll querySum(int ql,int qr,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) return t[x];
        int mid = (l+r)/2;
        ll ans = 0;
        if (ql <= mid) ans = (ans + querySum(ql,qr,x*2,l,mid)) % MOD;
        if (mid < qr) ans = (ans + querySum(ql,qr,x*2+1,mid+1,r)) % MOD;
        return ans % MOD;
    }
    ll querySq(int ql,int qr,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) return sq[x];
        int mid = (l+r)/2;
        ll ans = 0;
        if (ql <= mid) ans += querySq(ql,qr,x*2,l,mid);
        if (mid < qr) ans += querySq(ql,qr,x*2+1,mid+1,r);
        return ans % MOD;
    }
}t;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> m;
    for (int i = 1 ; i <= n ; i++) cin >> b[i];
    t.build();
    while (m--) {
        ll c,x,y;
        cin >> c >> x >> y;
        if (c == 1) {
            t.mergeP(x,y);
        }
        if (c == 2) {
            int len = y - x + 1;
            ll s = t.querySum(x,y) % MOD;
            ll s2 = t.querySq(x,y) % MOD;
            ll invN = qpow(len) % MOD;
            ll ans = (s2 * invN % MOD - (s * invN % MOD) * (s * invN % MOD) % MOD + MOD) % MOD;
            cout << ans << '\n';
        }
    }
}