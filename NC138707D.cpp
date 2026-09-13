#include <bits/stdc++.h>
using namespace std;
#define int long long

int n,m;
char mp[1010][1010];
int sx,sy;
int tx,ty;
int d[1010][1010][2];

int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};

void solve() {
    cin >> n >> m;
    for (int i = 1 ; i <= n ; i++) {
        for (int j = 1 ; j <= m ; j++) {
            cin >> mp[i][j];
            if (mp[i][j] == 'S') {
                sx = i; sy = j;
            }
            if (mp[i][j] == 'T') {
                tx = i; ty = j;
            }
            d[i][j][1] = d[i][j][0] = 1e9;
        }
    }
    queue<tuple<int,int,int>> q;
    q.push({sx,sy,0});
    d[sx][sy][0] = 0;
    while (!q.empty()) {
        auto [x,y,tri] = q.front();
        q.pop();
        for (int i = 0 ; i < 4 ; i++) {
            int xx = x + dx[i];
            int yy = y + dy[i];
            if (xx <= 0 || xx > n || yy <= 0 || yy > m) {
                continue;
            }
            if (mp[xx][yy] == '#' && !tri) {
                if (d[xx][yy][1] > d[x][y][0] + 1) {
                    d[xx][yy][1] = d[x][y][0] + 1;
                    q.push({xx,yy,1});
                }
            }
            if (mp[xx][yy] != '#') {
                if (d[xx][yy][tri] > d[x][y][tri] + 1) {
                    d[xx][yy][tri] = d[x][y][tri] + 1;
                    q.push({xx,yy,tri});
                }
            }
        }
    }
    int ans = min(d[tx][ty][0],d[tx][ty][1]) ;
    cout << (ans == 1e9 ? -1 : ans) << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T = 1;
    //cin >> T;
    while (T--) solve();
    return 0;
}