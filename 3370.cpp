#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

constexpr ull Base = 131;
ull hashList[10010];
int n;

ull getHash(string s) {
    ull res = 0;
    for (char c : s) res = res*Base + c;
    return res;
}

void solve() {
    cin >> n;
    for (int i = 1 ; i <= n ; i++) {
        string s; cin >> s;
        hashList[i] = getHash(s);
    }
    sort(hashList+1, hashList + n+1);
    int ans = unique(hashList, hashList + n + 1) - hashList - 1;
    cout << ans << endl;
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    //cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
}
