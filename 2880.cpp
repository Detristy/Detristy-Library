#include <bits/stdc++.h>
#include <pstl/algorithm_fwd.h>
using namespace std;
typedef long long ll;

int n,q;
const int N = 5e4+10;
ll h[N];

struct segment_tree {
    ll mx[N*4],mn[N*4];

    void build(int x = 1,int l = 1,int r = n) {
        if (l == r) {
            mx[x] = mn[x] = h[l];
            return;
        }
        ll mid = (l+r)/2;
        build(x*2,l,mid);
        build(x*2+1,mid+1,r);
        mx[x] = max(mx[x*2], mx[x*2+1]);
        mn[x] = min(mn[x*2], mn[x*2+1]);
    }
    ll queryMax(int ql,int qr,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) return mx[x];
        ll mid = (l+r)/2;
        ll ans = -0x3f3f3f3f;
        if (ql <= mid) ans = max(ans,queryMax(ql,qr,x*2,l,mid));
        if (mid < qr) ans = max(ans,queryMax(ql,qr,x*2+1,mid+1,r));
        return ans;
    }
    ll queryMin(int ql,int qr,int x = 1,int l = 1,int r = n) {
        if (ql <= l && r <= qr) return mn[x];
        ll mid = (l+r)/2;
        ll ans = 0x3f3f3f3f;
        if (ql <= mid) ans = min(ans,queryMin(ql,qr,x*2,l,mid));
        if (mid < qr) ans = min(ans,queryMin(ql,qr,x*2+1,mid+1,r));
        return ans;
    }
}t;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> q;
    for (int i = 1 ; i <= n ; i++) cin >> h[i];
    t.build();
    while (q--) {
        int a,b;
        cin >> a >> b;
        cout << t.queryMax(a,b)-t.queryMin(a,b) << "\n";
    }
}
