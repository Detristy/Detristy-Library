---
tags:
  - 动态规划
  - 背包DP
Difficulty:
  - Yellow
---

# 链接

https://www.luogu.com.cn/problem/AT_abc262_d

# 分析

所有的情况有 $2^N-1$ 种，显然肯定不能一种一种情况枚举。考虑到不同的选择方式本质上的区别就是某些数字选或不选，想到这里就可以用[[101-1 背包DP]]来解决了。

假设我们选择 $p$ 个数，定义 $dp[i][j][k]$ 为前 $i$ 项里选了 $j$ 个数使得它们的和模 $p$ 得到 $k$ 的方案数。

先确定一下初始情况，在 $i=0,j=0,k=0$ 的时候，只有一个数字都不选一种方案，所以 $dp[i][j][k] = 0$ 。

接下来我们从小到达枚举 $i$ ，考虑第 $i$ 个数选不选：
1. 选，那么：
	$$
		dp[i][j][k] = dp[i-1][j-1][(k-a[i]\%p+p)\%p]
	$$
2. 不选，那么：
	$$
		dp[i][j][k] = dp[i-1][j][k]
	$$

那么 $dp[n][p][0]$ 就是方案数。

显然 $p\in[1,n]$ 我们要枚举每一个 $p$ ，然后将每一个 $p$ 下的方案数算入答案的贡献，最终答案就是 $2^N-1$ 种情况里所有的选择方案。

复杂度是 $O(N^4)$ 。

# 代码

```cpp
#include<bits/stdc++.h>  
using namespace std;  
#define int long long  
  
constexpr int MOD = 998244353;  
constexpr int N = 5e5+10;  
int n,a[105],dp[105][105][105];  
  
void solve() {  
    cin >> n;  
    for (int i = 1 ; i <= n ; i++) cin >> a[i];  
    int ans = 0;  
    for (int p = 1 ; p <= n ; p++) {  
        memset(dp, 0, sizeof dp);  
        dp[0][0][0] = 1;  
        for (int i = 1 ; i <= n ; i++) {  
            for (int j = 0 ; j <= p ; j++) {  
                for (int k = 0 ; k < p ; k++) {  
                    dp[i][j][k] = (dp[i][j][k] + dp[i-1][j][k]) % MOD;  
                    if (j >= 1)
                     dp[i][j][k]=(dp[i][j][k]+dp[i-1][j-1][(k-a[i]%p+p)%p]) % MOD; 
                }  
            }  
        }  
        ans = (ans + dp[n][p][0])%MOD;  
    }  
    cout << ans << endl;  
}  
  
signed main() {  
    ios::sync_with_stdio(false);  
    cin.tie(NULL);  
  
    int T = 1;  
    //cin >> T;  
    while (T--) solve();  
    return 0;  
}
```