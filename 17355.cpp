#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define INF 0x3f3f3f3f3f3f3f3f
#define TEST cout << "END HERE" << endl;
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

void solve(int CASE) {
    string s; cin >> s;
    int n = s.length();
    vector<int> a(n+1,0);
    for (int i = 1 ; i <= n ; i++) {
        a[i] = s[i-1] - '0';
    }
    stack<int> st;
    vector<int> L(n+1,0);
    vector<int> R(n+1,0);
    for (int i = 1 ; i <= n ; i++) {
        while (!st.empty() && a[st.top()] <= a[i]) {
            int cur = st.top();
            st.pop();
            L[cur] = st.empty() ? 0 : st.top();
            R[cur] = i;
        }
        st.push(i);
    }
    while (!st.empty()) {
        int cur = st.top();
        st.pop();
        L[cur] = st.empty() ? 0 : st.top();
        R[cur] = n+1;
    }
    int mom = 0;
    int son = n*(n+1)/2;
    for (int i = 1 ; i <= n ; i++) {
        mom += a[i]*(i-L[i])*(R[i]-i);
    }
    //cout << mom << " " << son << endl;
    if (mom % son == 0) {
        cout << mom/son << endl;
        return;
    }
    int gcd1 = gcd(mom,son);
    mom /= gcd1;
    son /= gcd1;
    //cout << mom << " " << son << endl;
    if (mom > son) {
        cout << mom/son << ' ' << mom%son << '/' << son << endl;
    }
    else {
        cout << mom << '/' << son << endl;
    }
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