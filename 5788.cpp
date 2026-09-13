#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

constexpr int N = 3e6+10;
int stk[N];
int top = 0;

void solve() {
    int n;
    cin >> n;
    vector<int> v(n+1);
    for (int i = 1 ; i <= n ; i++) {
        cin >> v[i];
    }
    vector<int> res(n+1,0);
    for (int i = 1 ; i <= n ; i++) {
        while (top > 0 && v[i] > v[stk[top]]) {
            int tp = stk[top--];
            res[tp] = i;
        }
        stk[++top] = i;
    }
    for (int i = 1 ; i <= n ; i++) {
        cout << res[i] << " ";
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