#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define INF 0x3f3f3f3f3f3f3f3f
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 110;
vector<pair<int,int>> g[N];
int n,p;
int c[N];
int U[N];
int deg[N];

void solve(int CASE) {
    cin >> n >> p;
    for (int i = 1 ; i <= n ; i++) {
        cin >> c[i] >> U[i];
    }
    for (int i = 1 ; i <= p ; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        g[u].push_back({v,w});
        deg[v]++;
    }
    queue<int> q;
    for (int i = 1 ; i <= n ; i++) {
        if (!deg[i]) {
            q.push(i);
        }
        else {
            c[i] -= U[i];
        }
    }
    vector<pair<int,int>> ans;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        //c[u] -= U[u];
        if (g[u].empty()) {
            if (c[u] > 0) {
                ans.push_back({u,c[u]});
            }
            continue;
        }
        for (auto &[v,w] : g[u]) {
            if (c[u] > 0) c[v] += w * c[u];
            deg[v]--;
            if (!deg[v]) {
                q.push(v);
            }
        }
    }
    if (ans.empty()) {
        cout << "NULL" << endl;
    }
    else {
        sort(ans.begin(),ans.end());
        for (auto &[u,val] : ans) {
            cout << u << " " << val << endl;
        }
    }
}

signed main() {
    Detristy;
    int DETRISTY = 1,Det = 1;
    //cin >> DETRISTY;
    while (Det <= DETRISTY) {
        solve(Det++);
    }
    return 0;
}