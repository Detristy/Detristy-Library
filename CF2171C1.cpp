//注意力做法

#include<bits/stdc++.h>
using namespace std;
#define int long long

constexpr int N = 2e5+10;
int n,a[N],b[N],ansa,ansb;

void solve() {
    cin >> n;
    ansa = ansb = 0;
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
        ansa ^= a[i];
    }
    for (int i = 1 ; i <= n ; i++) {
        cin >> b[i];
        ansb ^= b[i];
    }
    if (ansa == ansb) cout << "Tie\n";
    else {
        int i = n;
        for (; i >= 1 ; i--) {
            if (a[i] != b[i]) break;
        }
        if (i%2) cout << "Ajisai\n";
        else cout << "Mai\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T = 1;
    cin >> T;
    while (T--) solve();
    return 0;
}