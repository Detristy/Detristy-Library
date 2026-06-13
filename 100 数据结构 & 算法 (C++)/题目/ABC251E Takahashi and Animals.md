---
tags:
  - 动态规划
Difficulty:
  - Yellow
---
# 链接

https://www.luogu.com.cn/problem/AT_abc251_e

# 分析

一道DP题，设 $dp[i][0/1]$ 为是否喂养第 $i$ 个宠物所花费的最小日元数，0 表示不喂养，1 表示喂养。

因为要保证每个宠物都被喂养，因此当第 $i$ 个宠物没有被喂养的时候，第 $i-1$ 个宠物必须要喂养，而如果第 $i$ 个宠物被喂养了，第 $i-1$ 个宠物是否喂养均可，我们取两种情况的最小值即可，因此我们可以写出状态转移方程：
$$
	dp[i][0]=dp[i-1][1]
$$
$$
	dp[i][1]=\min(dp[i-1][0],dp[i-1][1]) + A_{i}
$$

接下来我们考虑一下特殊的情况：

支付 $A_{n}$ 或 $A_{1}$ 日元的时候，都可以喂养到第 1 个宠物，因此我们要单独分两种情况来讨论，跑两次DP，最终答案取最小值即可。

# 代码

```cpp
#include <bits/stdc++.h>  
using namespace std;  
#define int long long  
#define detristy ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);  
  
constexpr int N = 3e5+10;  
int n,a[N],dp[N][2];  
  
void solve() {  
    cin >> n ;  
    for(int i=1;i<=n;i++) cin >> a[i];  
    for (int i = 0 ; i <= n ; i++) dp[i][0] = dp[i][1] = 0x3f3f3f3f3f3f3f3f;  
    dp[1][1] = a[1];  
    for (int i = 2 ; i <= n ; i++) {  
        dp[i][0] = dp[i-1][1];  
        dp[i][1] = min(dp[i-1][0],dp[i-1][1]) + a[i];  
    }  
    int ans1 = min(dp[n][0],dp[n][1]);  
    for (int i = 0 ; i <= n ; i++) dp[i][0] = dp[i][1] = 0x3f3f3f3f3f3f3f3f;  
    dp[1][0] = 0;  
    for (int i = 2 ; i <= n ; i++) {  
        dp[i][0] = dp[i-1][1];  
        dp[i][1] = min(dp[i-1][0],dp[i-1][1]) + a[i];  
    }  
    int ans2 = dp[n][1];  
    int ans = min(ans1,ans2);  
    cout << ans << '\n';  
}  
  
signed main() {  
    detristy  
    int T = 1;  
    //cin >> T;  
    while (T--) solve();  
    return 0;  
}
```