#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define INF 0x3f3f3f3f3f3f3f3f
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 1e5+10;
int n;

struct person {
    int v,w;
}a[N];

bool check(int x) {
    vector<int> low;
    vector<int> high;
    for (int i = 1 ; i <= n ; i++) {
        if (a[i].v < x) low.push_back(a[i].w);
        else high.push_back(a[i].v + a[i].w - x);
    }
    if (low.size() > high.size()) return false;
    sort(low.begin(),low.end(),greater<int>());
    sort(high.begin(),high.end(),greater<int>());
    for (int i = 0 ; i < low.size() ; i++){
        if (low[i] > high[i])
            return false;
    }
    return true;
}

void solve(int CASE) {
    cin >> n;
    int mx = 0;
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i].v >> a[i].w;
        mx = max(mx,a[i].v);
    }
    int l = 0,r = mx;
    int ans = -1;
    while (l <= r) {
        int mid = (l+r) >> 1;
        if (check(mid)) {
            ans = mid;
            l = mid+1;
        }
        else r = mid-1;
    }
    cout << ans << endl;
}

signed main() {
    Detristy;
    int DETRISTY = 1,Det = 1;
    cin >> DETRISTY;
    while (Det <= DETRISTY) {
        solve(Det++);
    }
    return 0;
}