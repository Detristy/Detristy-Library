#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 11000010;
int p[N*2];
int n;

int manacher(string s) {
    int mx = 0;
    n = s.length()*2+1;
    string t = "";
    for (char c : s) {
        t += '#';
        t += c;
    }
    t += "#";
    for (int i = 0,c = 0,r = 0,len ; i < n ; i++) {
        len = r > i ? min(p[2*c-i] , r-i) : 1;
        while (i+len < n && i-len >= 0 && t[i+len] == t[i-len]) len++;
        if (i + len > r) r = i + len, c = i;
        p[i] = len;
        mx = max(len,mx);

    }
    return mx-1;
}

void solve(const int CASE) {
    string s;
    cin >> s;
    cout << manacher(s) << endl;
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