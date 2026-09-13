#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

constexpr int N = 1e5+10;
int stk[N];
int a[N],s[N];
int top = 0;

void solve() {
    int n; cin >> n;
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
        s[i] = s[i-1] + a[i];
    }
    int ans = 0;
    for (int i = 1 ; i <= n+1 ; i++) {
        while (top && a[i] < a[stk[top]]) {
            int tp = stk[top--];
            int sum = s[i-1] - s[stk[top]];
            ans = max(ans, sum*a[tp]);
        }
        stk[++top] = i;
    }
    cout << ans << endl;
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