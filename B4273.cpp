#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define INF 0x3f3f3f3f3f3f3f3f
#define TEST cout << "END HERE" << endl;
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 1e6+10;
int a[N];
int stk[N];
int L[N],R[N];
int n,top;

void solve(int CASE) {
    cin >> n;
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
    }
    for (int i = 1 ; i <= n ; i++) {
        while (top && a[i] <= a[stk[top]]) {
            L[stk[top]] = (top ? stk[top-1] : top);
            R[stk[top--]] = i;
        }
        stk[++top] = i;
    }
    while (top) {
        L[stk[top]] = (top ? stk[top-1] : top);
        R[stk[top--]] = n+1;
    }
    int mx = 0;
    for (int i = 1 ; i<= n ; i++) {
        mx = max(mx,a[i]*(R[i] - L[i] - 1));
    }
    cout << mx << endl;
}

signed main() {
    Detristy
    int DETRISTY = 1,Det = 1;
    //cin >> DETRISTY;
    while (Det <= DETRISTY) {
        solve(Det++);
    }
    return 0;
}