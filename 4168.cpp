#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define endl "\n"
#define Detristy ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

constexpr int N = 4e4+10;
constexpr int B = 210;
int n,m,last;
int a[N];
int lib[N];
int freq[B][N];
int mode[B][B];
int numCnt[N];

int block[N],bl[B],br[N];

void build() {
    int b_len = sqrt(n);
    int b_cnt = (n+b_len-1) / b_len;
    for (int i = 1 ; i <= n ; i++) {
        block[i] = (i-1) / b_len + 1;
    }
    for (int i = 1 ; i <= b_cnt ; i++) {
        bl[i] = (i-1) * b_len + 1;
        br[i] = min(n, (i*b_len));
    }
    //离散化
    for (int i = 1 ; i <= n ; i++) {
        lib[i] = a[i];
    }
    sort(lib+1,lib+n+1);
    last = unique(lib+1,lib+1+n) - (lib+1);
    for (int i = 1 ; i <= n ; i++) {
        int tmp = a[i];
        a[i] = lower_bound(lib+1,lib+last+1,tmp)-lib;
    }

    for (int i = 1 ; i <= b_cnt ; i++) {
        for (int j = bl[i] ; j <= br[i] ; j++) {
            freq[i][a[j]]++;
        }
        for (int j = 1 ; j <= last ; j++) {
            freq[i][j] += freq[i-1][j];
        }
    }
    for (int i = 1 ; i <= b_cnt ; i++) {
        for (int j = i ; j <= b_cnt ; j++) {
            int most = mode[i][j-1];
            int mostCnt = freq[j][most] - freq[i-1][most];
            for (int k = bl[j] ; k <= br[j] ; k++) {
                int cur = a[k];
                int curCnt = freq[j][cur] - freq[i-1][cur];
                if (curCnt > mostCnt || (curCnt == mostCnt && cur < most)) {
                    most = cur;
                    mostCnt = curCnt;
                }
            }
            mode[i][j] = most;
        }
    }
}

int query(int l,int r) {
    int most = 0;
    if (block[l] == block[r]) {
        for (int i = l ; i <= r ; i++) {
            numCnt[a[i]]++;
        }
        for (int i = l ; i <= r ; i++) {
            if (numCnt[a[i]] > numCnt[most] || (numCnt[a[i]] == numCnt[most] && a[i] < most)) {
                most = a[i];
            }
        }
        for (int i = l ; i <= r ; i++) {
            numCnt[a[i]] = 0;
        }
    }
    else {
        for (int i = l ; i <= br[block[l]]; i++) {
            numCnt[a[i]]++;
        }
        for (int i = bl[block[r]] ; i <= r ; i++) {
            numCnt[a[i]]++;
        }
        most = mode[block[l] + 1][block[r] - 1];
        int mostCnt = freq[block[r] - 1][most] - freq[block[l]][most] + numCnt[most];
        for (int i = l ; i <= br[block[l]] ; i++) {
            int cur = a[i];
            int curCnt = freq[block[r] - 1][cur] - freq[block[l]][cur] + numCnt[cur];
            if (curCnt > mostCnt || (curCnt == mostCnt && cur < most)) {
                most = cur;
                mostCnt = curCnt;
            }
        }
        for (int i = bl[block[r]] ; i <= r ; i++) {
            int cur = a[i];
            int curCnt = freq[block[r] - 1][cur] - freq[block[l]][cur] + numCnt[cur];
            if (curCnt > mostCnt || (curCnt == mostCnt && cur < most)) {
                most = cur;
                mostCnt = curCnt;
            }
        }
        for (int i = l ; i <= br[block[l]]; i++) {
            numCnt[a[i]] = 0;
        }
        for (int i = bl[block[r]] ; i <= r ; i++) {
            numCnt[a[i]] = 0;
        }
    }
    return lib[most];
}

void solve() {
    cin >> n >> m;
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
    }
    int ans = 0;
    build();
    for (int i = 1 ; i <= m ; i++) {
        int a,b;
        cin >> a >> b;
        a = (a+ans-1)%n+1;
        b = (b+ans-1)%n+1;
        int l = min(a,b);
        int r = max(a,b);
        ans = query(l,r);
        cout << ans << endl;
    }
}

signed main() {
    Detristy;
    int DETRISTY = 1;
    //cin >> DETRISTY;
    while (DETRISTY--) {
        solve();
    }
    return 0;
}
