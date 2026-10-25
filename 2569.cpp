#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define INF 0x3f3f3f3f3f3f3f3f
#define TEST cout << "END HERE" << endl;
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 2e6+10;
int L[N],R[N];
stack<int> st;
int n;
int a[N];

void solve(int CASE) {
    cin >> n;
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
        while (!st.empty() && a[st.top()] >= a[i]) {
            int cur = st.top();
            st.pop();
            L[cur] = st.empty() ? -1 : st.top();
            R[cur] = i;
        }
        st.push(i);
    }
    while (!st.empty()) {
        int cur = st.top();
        st.pop();
        L[cur] = st.empty() ? -1 : st.top();
        R[cur] = -1;
    }
    int mx = 0;
    for (int i = 1 ; i <= n ; i++) {
        int r = R[i] == -1 ? n : R[i]-1;
        int l = L[i] == -1 ? 1 : L[i]+1;
        mx = max(mx,a[i]*(r-l+1));
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