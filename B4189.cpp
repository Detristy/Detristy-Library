#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define INF 0x3f3f3f3f3f3f3f3f
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 1e5+10;
vector<int> g[N];
int a[N];
int d[N];
int n,ans;

void update(int u) {
    for (int i = 1 ; i*i <= a[u] ; i++) {
        if (!(a[u] % i)) {
            d[i] ++;
            if (a[u]/i != i) d[a[u]/i]++;
        }
    }
}

void DFS(int u,int fa) {
    int s = 0;
    update(u);
    for (auto v : g[u]) {
        if (v == fa) continue;
        int tmp = d[a[u]];
        DFS(v,u);
        int v_i = d[a[u]] - tmp;
        ans += v_i * (s+1);
        s += v_i;
    }
}

void solve(int CASE) {
    cin >> n;
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
    }
    for (int i = 1 ; i < n ; i++) {
        int u,v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    DFS(1,0);
    cout << ans*2 + n << endl;
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