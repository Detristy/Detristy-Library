#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

void solve() {
    int n;
    cin >> n;
    vector<int> v(n+1);
    for (int i = 1 ; i <= n ; i++) {
        cin >> v[i];
        v[i] %= 4;
    }
    set<int> s3;
    set<int> s2;
    set<int> s1;
    set<int> s0;
    for (int i = 1 ; i <= n ; i++) {
        if (v[i] == 0) s0.insert(i);
        if (v[i] == 1) s1.insert(i);
        if (v[i] == 2) s2.insert(i);
        if (v[i] == 3) s3.insert(i);
    }
    int sz1 = s1.size(), sz2 = s2.size(), sz3 = s3.size();
    if (abs(sz1-sz3) > 2*sz2) {
        cout << -1 << endl;
        return;
    }
    for (auto i : s0) {
        cout << i << " ";
    }
    while (!s1.empty() && !s3.empty()) {
        auto it = s3.begin();
        cout << *it << " ";
        s3.erase(it);
        it = s1.begin();
        cout << *it << " ";
        s1.erase(it);
    }
    if (!s1.empty()) {
        while (!s1.empty()) {
            auto it = s2.begin();
            cout << *it << " ";
            s2.erase(it);
            it = s1.begin();
            cout << *it << " ";
            s1.erase(it);
            it = s1.begin();
            cout << *it << " ";
            s1.erase(it);
        }
    }
    if (!s3.empty()) {
        while (!s3.empty()) {
            auto it = s3.begin();
            cout << *it << " ";
            s3.erase(it);
            it = s3.begin();
            cout << *it << " ";
            s3.erase(it);
            it = s2.begin();
            cout << *it << " ";
            s2.erase(it);
        }
    }
    if (!s2.empty()) {
        for (auto i : s2) {
            cout << i << " ";
        }
    }
    cout << endl;
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