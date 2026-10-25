#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define INF 0x3f3f3f3f3f3f3f3f
#define TEST cout << "END HERE" << endl;
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 1010;
int n,t;
int mp[N][N];

void solve(int CASE) {
    cin >> n >> t;
    for (int i = 1 ; i <= n ; i++) {
        for (int j = 1 ; j <= n ; j++) {
            mp[i][j] = 1;
        }
    }
    for (int i = 1 ; i <= t ; i++) {
        int x,y;
        cin >> x >> y;
        mp[x][y] = 0;
    }

    // for (int i = 1 ; i <= n ; i++) {
    //     for (int j = 1 ; j <= n ; j++) {
    //         cout << mp[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    int ans = 0;
    for (int i = 1 ; i <= n ; i++) {
        stack<int> st;
        vector<int> L(n+1,0);
        vector<int> R(n+1,0);
        for (int j = 1 ; j <= n ; j++) {
            if (mp[i][j] != 0) {
                mp[i][j] += mp[i-1][j];
            }
        }
        for (int j = 1 ; j <= n ; j++) {
            int h = mp[i][j];
            while (!st.empty() && mp[i][st.top()] >= h) {
                int cur = st.top();
                st.pop();
                L[cur] = st.empty() ? -1 : st.top();
                R[cur] = j;
            }
            st.push(j);
        }
        while (!st.empty()) {
            int cur = st.top();
            st.pop();
            L[cur] = st.empty() ? -1 : st.top();
            R[cur] = -1;
        }
        for (int j = 1 ; j <= n ; j++) {
            int l = (L[j] == -1 ? 0 : L[j]);
            int r = (R[j] == -1 ? n+1 : R[j]);
            //cout << "l " << l << " r " << r << endl;
            int d = r-l-1;
            int a = min(mp[i][j],d);
            ans = max(ans,a);
            //cout << ans << endl;
        }
    }
    cout << ans << endl;
}

signed main() {
    Detristy
    int DETRISTY = 1,Det = 1;
    //cin >> DETRISTY;
    while (Det <= DETRISTY) {
        solve(Det++);
    }
    return 0;
}