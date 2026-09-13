#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

void solve() {
    int n; cin >> n;
    vector<int> b(n+1);
    map<int,int> freq;
    for (int i = 1 ; i <= n ; i++) {
        cin >> b[i];
        freq[b[i]]++;
    }
    if (!freq.count(0)) {
        cout << -1 << endl;
        return;
    }
    map<int,int> ans;
    int preVal = 0,preFreq = 0,pre = 0;
    bool ok = true;
    for (auto [val,fre] : freq) {
        if (val != 0) {
            int delta = val - preVal;
            if (delta % preFreq) {
                ok = false;
                break;
            }
            int a = delta / preFreq;
            if (a <= pre) {
                ok = false;
                break;
            }
            ans[preVal] = a;
            pre = a;
        }
        preVal = val;
        preFreq = fre;
    }
    if (!ok) {
        cout << -1 << endl;
        return;
    }
    ans[preVal] = pre+1;
    for (int i = 1 ; i <= n ; i++) {
        cout << ans[b[i]] << " ";
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