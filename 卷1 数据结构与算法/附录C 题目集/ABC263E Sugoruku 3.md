---
tags:
  - 概率DP
  - 数论
  - 费马小定理
Difficulty:
  - Green
---

# 链接

https://www.luogu.com.cn/problem/AT_abc263_e

# 分析

一道[[101-2 概率DP|期望DP]]题，我们不妨考虑从后向前推，题目问我们从第 $1$ 格走到第 $N$ 格的期望，那么我们不妨从这里入手来定义状态。

定义 $dp_{i}$ 为从第 $i$ 格走到第 $N$ 格的期望。

接下来我们来推导状态转移方程：

假设当前处在第 $i$ 格，掷骰子以固定的 $\frac{1}{A_{i}+1}$ 的概率（骰子有 $A_{i}+1$ 面）掷到了 $k$ ，向前走 $k$ 格走到第 $i+k$ 格，此时第 $i$ 格的期望就可以被第 $i+k$ 格的期望所转移过来，对于每一个骰子上的每一个数都是如此，于是加上这一步的代价 $1$ ，就有：

$$
dp_{i}=1+\sum\limits_{k=0}^{A_{i}} \frac{1}{A_{i}+1}dp_{i+k}
$$

我们将 $k=0$ 的情况单独分离出来：

$$
dp_{i}=1+\frac{1}{A_{i}+1}dp_{i}+\sum\limits_{k=1}^{A_{i}} \frac{1}{A_{i}+1}dp_{i+k}
$$

接着我们可以整理得到：

$$
dp_{i}=\frac{A_{i}+1+\sum\limits_{k=1}^{A_{i}}dp_{i+k}}{A_{i}}
$$

我们只需要处理 $\sum\limits_{k=1}^{A_{i}}dp_{i+k}$ 就可以了，我们可以用前缀和来优化。
特殊考虑一下 $dp_{n}$ ，显然地，$dp_{n} = 0$ 。

除法取模即对乘法的逆元取模，使用费马小定理即可。

# 代码

```cpp
#include<bits/stdc++.h>  using namespace std;    
#define int long long    
constexpr int MOD = 998244353;  
constexpr int N = 2e5+10;  
int n;  
int a[N],s[N],dp[N];  
  
int mod_pow(int x, int b) {  
    int res = 1;  
    while (b) {  
        if (b & 1) res = 1LL * res * x % MOD;  
        x = 1LL * x * x % MOD;  
        b >>= 1;  
    }  
    return res;  
}  
  
int inv(int x) {  
    return mod_pow(x, MOD - 2);  
}  
    
void solve() {    
    cin >> n;  
    for (int i = 1 ; i < n ; i++) cin >> a[i];  
    dp[n] = 0;  
    for (int i = n-1 ; i >= 1 ; i--) {  
        int sum1 = (s[i+1] - s[i+a[i]+1] + MOD) % MOD;  
        int sum2 = (a[i] + 1 + sum1) % MOD;  
        dp[i] = (sum2 * inv(a[i])) % MOD;  
        s[i] = (s[i+1] + dp[i]) % MOD;  
    }  
    cout << dp[1] << '\n';  
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