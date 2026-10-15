#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define INF 0x3f3f3f3f3f3f3f3f
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 3e5+10;
int n;
int a[N];

struct BIT {
    int t[N];
    int lowbit(int x){
        return x & -x;
    }
    void add(int x,int val) {
        for (;x<=n;x += lowbit(x)) t[x] += val;
    }
    int query(int x) {
        int ans = 0;
        for (;x;x -= lowbit(x)) ans += t[x];
        return ans;
    }
}t;

void solve(int CASE) {
    cin >> n;
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
        a[i]++;
    }
    int cnt = 0;
    for (int i = 1 ; i <= n ; i++) {
        cnt += i-1-t.query(a[i]);
        t.add(a[i],1);
    }
    cout << cnt << endl;
    for (int i = 1 ; i < n ; i++) {
        cnt = cnt + n - 2 * a[i] + 1;
        cout << cnt << endl;
    }

}

signed main() {
    Detristy;
    int DETRISTY = 1,Det = 1;
    //cin >> DETRISTY;
    while (Det <= DETRISTY) {
        solve(Det++);
    }
    return 0;
}