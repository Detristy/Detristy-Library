#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define INF 0x3f3f3f3f3f3f3f3f
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 1e5+10;
vector<int> pri;
bool notPrime[N];
int phi[N];
int n;

void pre(int x) {
    phi[1] = 1;
    for (int i = 2 ; i <= x ; i++) {
        if (!notPrime[i]) {
            pri.push_back(i);
            phi[i] = i-1;
        }
        for (int p : pri) {
            if (i*p > x) break;
            notPrime[i*p] = true;
            if (!(i%p)) {
                phi[i*p] = phi[i] * p;
                break;
            }
            phi[i*p] = phi[i] * phi[p];
        }
    }
}

void solve(int CASE) {
    cin >> n;
    pre(n);
    int ans = 0;
    for (int i = 1 ; i <= n ; i++) {
        ans += phi[i]*(n/i)*(n/i);
    }
    cout << ans << endl;
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