#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

struct comp {
    int mn,mx;
};

void solve() {
    int n;
    cin >> n;
    vector<int> p(n);
    stack<comp> st;
    for (int i = 0 ; i < n ; i++) {
        cin >> p[i];
    }
    set<pair<int,int>> edge;
    for (auto x : p) {
        comp cur = {x,x};
        while (!st.empty() && st.top().mn < cur.mx) {
            comp top = st.top();
            st.pop();
            edge.insert({cur.mx,top.mn});
            cur.mn = min(cur.mn,top.mn);
            cur.mx = max(cur.mx,top.mx);
        }
        st.push(cur);
    }
    if (st.size() == 1) {
        cout << "Yes" << endl;
        for (auto x : edge) {
            cout << x.first << " " << x.second << endl;
        }
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