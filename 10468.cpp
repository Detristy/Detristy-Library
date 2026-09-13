#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

constexpr ull BASE = 499;
int m;
ull pw[1000010];
ull ha[1000010];

ull getHash(int l,int r) {
    return ha[r]-ha[l-1]*pw[r-l+1];
}

void solve() {
    string s;
    cin >> s;
    int len = s.length();
    pw[0] = 1;
    for (int i = 1 ; i <= len ; i++) {
        pw[i] = pw[i-1] * BASE;
    }
    for (int i = 1 ; i <= len ; i++) {
        ha[i] = ha[i-1] * BASE + (s[i-1]-'a'+1);
    }
    cin >> m;
    for (int i = 1 ; i <= m ; i++) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        if (getHash(l1,r1) == getHash(l2,r2)) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
    }
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    //cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
}
