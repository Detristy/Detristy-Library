#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define INF 0x3f3f3f3f3f3f3f3f
#define TEST cout << "END HERE" << endl;
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

void solve(int CASE) {
    int n;
    cin >> n;
    vector<int> a(n+1,0);
    vector<int> b(n+1,0);
    int sumA = 0,sumB = 0;
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
        sumA ^= a[i];
    }
    for (int i = 1 ; i <= n ; i++) {
        cin >> b[i];
        sumB ^= b[i];
    }
    int x = sumA ^ sumB;
    if (!x) {
        cout << "Tie" << endl;
        return;
    }
    int k = 0;
    while ((1 << (k+1)) <= x) {
        k++;
    }
    for (int i = n ; i >= 1 ; i--) {
        if (((a[i] ^ b[i]) >> k) & 1) {
            if (i%2) {
                cout << "Ajisai" << endl;
            }
            else {
                cout << "Mai" << endl;
            }
            break;
        }
    }
}

signed main() {
    Detristy
    int DETRISTY = 1,Det = 1;
    cin >> DETRISTY;
    while (Det <= DETRISTY) {
        solve(Det++);
    }
    return 0;
}