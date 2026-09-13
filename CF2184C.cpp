#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

map<int,int> mp;
int n,k;

void dfs(int x,int step) {
    if (mp[x]) return;
    mp[x] = step;
    if (x == k || x == 1) return;
    dfs(x/2,step+1);
    if (x%2) dfs(x/2+1,step+1);
}

void solve() {
    mp.clear();
    cin >> n >> k;
    if (n == k) {
        cout << 0 << endl;
        return;
    }
    dfs(n,0);
    if (mp[k]) cout << mp[k] << endl;
    else cout << -1 << endl;
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