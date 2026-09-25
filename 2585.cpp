#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 5e5+10;
string s;
int cnt = 0,nw = 0;
int tree[N][3];
int mx[N][3];
int mn[N][3];

int DFS1() {
    int u = ++cnt;
    char ty = s[nw++];
    if (ty == '1') {
        tree[u][0] = DFS1();
    }
    if (ty == '2') {
        tree[u][0] = DFS1();
        tree[u][1] = DFS1();
    }
    return u;
}

void DFS2(int rt) {
    if (s[rt-1] == '0') {
        mx[rt][0] = 1;
        mn[rt][0] = 1;
        return;
    }

    int lChild = tree[rt][0];
    int rChild = tree[rt][1];
    DFS2(lChild);
    if (s[rt-1] == '1') {
        mx[rt][0] = max(mx[lChild][1],mx[lChild][2]) + 1;
        mx[rt][1] = max(mx[lChild][0],mx[lChild][2]);
        mx[rt][2] = max(mx[lChild][0],mx[lChild][1]);

        mn[rt][0] = min(mn[lChild][1],mn[lChild][2]) + 1;
        mn[rt][1] = min(mn[lChild][0],mn[lChild][2]);
        mn[rt][2] = min(mn[lChild][0],mn[lChild][1]);
    }
    else {
        DFS2(rChild);
        mx[rt][0] = max(mx[lChild][1]+mx[rChild][2],mx[lChild][2]+mx[rChild][1]) + 1;
        mx[rt][1] = max(mx[lChild][0]+mx[rChild][2],mx[lChild][2]+mx[rChild][0]);
        mx[rt][2] = max(mx[lChild][0]+mx[rChild][1],mx[lChild][1]+mx[rChild][0]);

        mn[rt][0] = min(mn[lChild][1]+mn[rChild][2],mn[lChild][2]+mn[rChild][1]) + 1;
        mn[rt][1] = min(mn[lChild][0]+mn[rChild][2],mn[lChild][2]+mn[rChild][0]);
        mn[rt][2] = min(mn[lChild][0]+mn[rChild][1],mn[lChild][1]+mn[rChild][0]);
    }
}

void solve() {
    cin >> s;
    int root = DFS1();
    DFS2(1);
    cout << max({mx[1][0],mx[1][1],mx[1][2]}) << ' ' << min({mn[1][0],mn[1][1],mn[1][2]}) << endl;
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    //cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
    return 0;
}