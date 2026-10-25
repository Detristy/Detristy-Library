#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define INF 0x3f3f3f3f3f3f3f3f
#define TEST cout << "END HERE" << endl;
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 1e6+10;
int a[N];
stack<int> st;
int n;
int ans = 0;

void solve(int CASE) {
    cin >> n;
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
    }
    for (int i = 1 ; i <= n ; i++) {
        while (!st.empty() && a[i] < st.top()) {
            st.pop();
        }
        if (!a[i] || (!st.empty() && a[i] == st.top())) continue;
        st.push(a[i]);
        ans++;
    }
    cout << ans << endl;
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