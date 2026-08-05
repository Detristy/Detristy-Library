#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

constexpr int N = 1e6+10;
constexpr int B = 1e3;
int n,q;
int a[1000010];
vector<int> block[N/B+10];
int lazy[N/B+10];

int query(int l,int r,int val) {
    int bl = l/B;
    int br = min(n,r/B);
    int cnt = 0;
    if (bl == br) {
        for (int i = l ; i <= r ; i++) {
            if (a[i] + lazy[bl] >= val) cnt++;
        }
        return cnt;
    }
    for (int i = l ; i < (bl+1)*B ; i++) {
        if (a[i] + lazy[bl] >= val) cnt++;
    }
    for (int i = bl+1 ; i < br ; i++) {
        auto &v = block[i];
        int pos = lower_bound(v.begin(),v.end(),val-lazy[i])-v.begin();
        cnt += v.size()-pos;
    }
    for (int i = br*B ; i <= r ; i++) {
        if (a[i] + lazy[bl] >= val) cnt++;
    }
    return cnt;
}

void update(int l,int r,int val) {
    int bl = l/B;
    int br = min(n, r/B);
    if (bl == br) {
        for (int i = l ; i <= r ; i++) {
            a[i] += val;
        }
        sort(block[bl].begin(),block[bl].end());
        return;
    }
    for (int i = l ; i < (bl+1)*B ; i++) {
        a[i] += val;
    }
    sort(block[bl].begin(),block[bl].end());
    for (int i = bl+1 ; i < br ; i++) {
        lazy[i] += val;
    }
    for (int i = br*B ; i <= r ; i++) {
        a[i] += val;
    }
    sort(block[br].begin(),block[br].end());
}

void solve() {
    cin >> n >> q;
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
        block[i/B].push_back(a[i]);
    }
    for (int i = 0 ; i <= n/B ; i++) {
        sort(block[i].begin(), block[i].end());
    }
    while (q--) {
        char op;
        cin >> op;
        if (op == 'M') {
            int l,r,w;
            cin >> l >> r >> w;
            update(l,r,w);
        }
        else {
            int l,r,c;
            cin >> l >> r >> c;
            cout << query(l,r,c) << endl;
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
    return 0;
}
