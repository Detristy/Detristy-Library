#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define TEST cout << "TEST" << endl;
#define Detristy ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

constexpr int N = 310;
int n,m,q;
int mp[N][N];

struct BIT {
    int t[110][N][N];
    int lowbit(int x) {
        return x & -x;
    }
    void add(int color,int x,int y,int val) {
        for (;x <= n; x += lowbit(x)) {
            for (int j = y ; j <= m ; j += lowbit(j)) {
                t[color][x][j] += val;
            }
        }
    }
    int sum(int color,int x,int y) {
        int ans = 0;
        for (;x;x -= lowbit(x)) {
            for (int j = y ; j; j-= lowbit(j)) {
                ans += t[color][x][j];
            }
        }
        return ans;
    }
    int query(int color,int x1,int x2,int y1,int y2) {
        return sum(color,x2,y2)
        -sum(color,x2,y1-1)
        -sum(color,x1-1,y2)
        +sum(color,x1-1,y1-1);
    }
}T;

void solve(const int CASE) {
    cin >> n >> m;
    for (int i = 1 ; i <= n ; i++) {
        for (int j = 1 ; j <= m ; j++) {
            cin >> mp[i][j];
            T.add(mp[i][j],i,j,1);
        }
    }
    cin >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x,y,c;
            cin >> x >> y >> c;
            T.add(mp[x][y],x,y,-1);
            T.add(c,x,y,1);
            mp[x][y] = c;
        }
        else {
            int x1,x2,y1,y2,c;
            cin >> x1 >> x2 >> y1 >> y2 >> c;
            cout << T.query(c,x1,x2,y1,y2) << endl;
        }
    }
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