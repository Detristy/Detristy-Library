#include <bits/stdc++.h>
using namespace std;
#define int long long

int n;
struct point {
    int x,y;
};
point a[200010];

void solve() {
    cin >> n;
    for (int i = 0 ; i < n ; i++) {
        cin >> a[i].x >> a[i].y;
    }
    if (n < 4) {
        cout << "No\n";
        return;
    }
    bool nega = false,posi = false;
    for (int i = 0 ; i < n ; i++) {
        point p1 = {a[i].x,a[i].y};
        point p2 = {a[(i+1)%n].x,a[(i+1)%n].y};
        point p3 = {a[(i+2)%n].x,a[(i+2)%n].y};
        int cross = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
        if (cross > 0) posi = true;
        if (cross < 0) nega = true;
    }
    if (nega && posi) {
        cout << "Yes\n";
    }
    else
        cout << "No\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T = 1;
    //cin >> T;
    while (T--) solve();
}
