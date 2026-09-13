#include <bits/stdc++.h>
using namespace std;
#define int long long

int n,m;
priority_queue<int,vector<int>,greater<int>> q;
int deg[1010];
vector<int> res;
vector<int> g[1010];

void solve() {
    for (int i = 0 ; i <= n ; i++) {
        deg[i] = 0;
        g[i].clear();
    }
    res.clear();
    cin >> n >> m;
    for (int i = 1 ; i <= m ; i++) {
        int u,v;
        cin >> u >> v;
        g[u].push_back(v);
        deg[v]++;
    }
    for (int i = 1 ; i <= n ; i++) {
        if (!deg[i]) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.top();
        res.push_back(u);
        q.pop();
        for (auto v : g[u]) {
            deg[v]--;
            if (!deg[v]) {
                q.push(v);
            }
        }
    }
    if (res.size() != n) cout << "No" << endl;
    else {
        cout << "Yes" << endl;
        for (int i = 0 ; i < n ; i++) cout << res[i] << " ";
        cout << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T = 1;
    cin >> T;
    while (T--) solve();
    return 0;
}