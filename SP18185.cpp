#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

constexpr int N = 5e5+10;
constexpr int B = 720;
int n,q;
int a[500010];
vector<int> block[N/B+10];

int query(int l,int r,int val) {
    int bl = l/B;
    int br = min(n,r/B);
    int cnt = 0;
    if (bl == br) {
        for (int i = l ; i <= r ; i++) {
            if (a[i] >= val) cnt++;
        }
        return cnt;
    }
    for (int i = l ; i < (bl+1)*B ; i++) {
        if (a[i] >= val) cnt++;
    }
    for (int i = bl+1 ; i < br ; i++) {
        auto &v = block[i];
        int pos = lower_bound(v.begin(),v.end(),val)-v.begin();
        cnt += v.size()-pos;
    }
    for (int i = br*B ; i <= r ; i++) {
        if (a[i] >= val) cnt++;
    }
    return cnt;
}

void update(int pos,int val) {
    int bid = pos/B;
    auto &v = block[bid];
    v.erase(lower_bound(v.begin(),v.end(),a[pos]));
    v.insert(lower_bound(v.begin(),v.end(),val),val);
    a[pos] = val;
}

void solve() {
    cin >> n;
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
        block[i/B].push_back(a[i]);
    }
    for (int i = 0 ; i <= n/B ; i++) {
        sort(block[i].begin(), block[i].end());
    }
    cin >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 0) {
            int l,r,val;
            cin >> l >> r >> val;
            cout << query(l,r,val) << endl;
        }
        else {
            int x,val;
            cin >> x >> val;
            update(x,val);
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
