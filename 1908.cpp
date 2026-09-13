#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
int a[500010], b[500010];

struct BIT {
    int t[500010];
    int lowbit(int x) {
        return x & -x;
    }
    void add(int x,int val) {
        for (;x<=n;x += lowbit(x)) t[x] += val;
    }
    ll query(int x) {
        ll ans = 0;
        for (;x;x -= lowbit(x)) ans += t[x];
        return ans;
    }
}t;

int main() {
    cin >> n;
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i]; b[i] = a[i];
    }
    sort(b+1,b+1+n);
    int pend = unique(b+1,b+1+n) - (b+1);
    ll cnt = 0;
    for (int i = 1 ; i <= n ; i++) {
        int val = lower_bound(b+1,b+1+pend,a[i]) - b;
        cnt += (i - 1 - t.query(val));
        t.add(val,1);
    }
    cout << cnt << endl;
}
