#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

void solve() {
    int n;
    cin >> n;
    vector<int> p(n);
    stack<pair<int, int>> st;
    for (int i = 0 ; i < n ; i++) {
        cin >> p[i];
    }
    for (auto x : p) {
        int curmn = x, curmx = x;
        while (!st.empty() && st.top().first < curmx) {
            int topmn = st.top().first;
            int topmx = st.top().second;
            st.pop();
            curmn = min(topmn, curmn);
            curmx = max(topmx, curmx);
        }
        st.push({curmn, curmx});
    }
    if (st.size() == 1) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
    return 0;
}