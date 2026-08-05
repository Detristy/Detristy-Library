#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

constexpr ull BASE = 499;
string s,t;
char stk[1000010];
ull pw[1000010];
ull ha[1000010];
int top;

void solve() {
    cin >> s >> t;
    int len_s = s.length();
    int len_t = t.length();
    pw[0] = 1;
    for (int i = 1 ; i <= len_s ; i++) {
        pw[i] = pw[i-1] * BASE;
    }
    ull hat = 0;
    for (int i = 0 ; i < len_t ; i++) {
        hat = hat*BASE + t[i]-'a'+1;
    }
    for (int i = 1 ; i <= len_s ; i++) {
        stk[++top] = s[i-1];
        ha[top] = ha[top-1] * BASE + s[i-1]-'a'+1;
        if (top >= len_t) {
            ull nw = ha[top]-ha[top-len_t]*pw[len_t];
            if (nw == hat) {
                top -= len_t;
            }
        }
    }
    for (int i = 1 ; i <= top ; i++) {
        cout << stk[i];
    }
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    //cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
}
