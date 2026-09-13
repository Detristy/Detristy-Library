#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

void solve() {
    int n; cin >> n;
    string s1,s2; cin >> s1 >> s2;
    int cnt11 = 0, cnt12 = 0, cnt21 = 0, cnt22 = 0;
    vector<int> v11,v12,v21,v22;
    for (int i = 0; i < n; i++) {
        if (s1[i] == '1') {
            if (i%2) cnt11++,v11.push_back(i);
            else cnt12++,v12.push_back(i);
        }
        if (s2[i] == '1') {
            if (i%2) cnt21++,v21.push_back(i);
            else cnt22++,v22.push_back(i);
        }
    }
    if (!(cnt11 == cnt21 && cnt12 == cnt22)) {
        cout << -1 << endl;
        return;
    }
    int dis = 0;
    for (int i = 0 ; i < v11.size(); i++) {
        dis += abs(v11[i] - v21[i]);
    }
    for (int i = 0 ; i < v12.size(); i++) {
        dis += abs(v12[i] - v22[i]);
    }
    cout << dis/2 << endl;
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
