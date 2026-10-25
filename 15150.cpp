#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define INF 0x3f3f3f3f3f3f3f3f
#define TEST cout << "END HERE" << endl;
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 2e5+10;
int a[N];
int L[N],R[N];
stack<int> st;
int n;

void solve(int CASE) {
    cin >> n;
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
    }
    for (int i = 1 ; i <= n ; i++) {
        while (!st.empty() && a[st.top()] < a[i]) {
            int cur = st.top();
            st.pop();
            R[cur] = i;
            L[cur] = st.empty() ? -1 : st.top();
        }
        st.push(i);
    }
    while (!st.empty()) {
        int cur = st.top();
        st.pop();
        R[cur] = -1;
        L[cur] = st.empty() ? -1 : st.top();
    }
    int ans = 0;
    for (int i = 1 ; i <= n ; i++) {
        int d = INF;
        if (L[i] != -1) d = min(d,i-L[i]);
        if (R[i] != -1) d = min(d,R[i]-i);
        if (d < INF) ans += d;
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