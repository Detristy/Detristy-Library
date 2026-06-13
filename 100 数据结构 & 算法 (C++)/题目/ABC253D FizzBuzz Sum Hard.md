---
tags:
  - 数论（算法）
  - GCD/LCM
Difficulty:
  - Orange
---
# 链接

https://www.luogu.com.cn/problem/AT_abc253_d

# 思路

首先考虑从小到大枚举，因为 $N$ 很大，所以肯定会爆。

接着我们思考能不能把所有的 $A$ 的倍数和 $B$ 的倍数全部处理出来，然后让所有数的和减去所有的 $A$ 的倍数和 $B$ 的倍数的和，根据容斥原理，既是 $A$ 的倍数又是 $B$ 的倍数的数被减去了两次，因此我们要加一次回来。

大体思路有了我们来写式子。

小于 $N$ 的最大的 $A$ 的倍数为：
$$
	\left\lfloor  \frac{N}{A}  \right\rfloor A
$$
我们对所有的小于 $N$ 的 $A$ 的倍数求和：
$$
	\sum_{k=1}^{\left\lfloor  \frac{N}{A}  \right\rfloor}kA
$$
同理可以求出小于$N$ 的 $B$ 的倍数之和：
$$
	\sum_{k=1}^{\left\lfloor  \frac{N}{B}  \right\rfloor}kB
$$
然后求出小于 $N$ 的既是 $A$ 的倍数又是 $B$ 的倍数（即 $A$ 和 $B$ 的最小公倍数）之和：
$$
	\sum_{k=1}^{\left\lfloor  \frac{N}{\mathrm{lcm}(A,B)}  \right\rfloor}k\mathrm{lcm}(A,B)
$$
于是最终的答案为：
$$
	\sum_{i=1}^Ni-\sum_{k=1}^{\left\lfloor  \frac{N}{A}  \right\rfloor}kA-\sum_{k=1}^{\left\lfloor  \frac{N}{B}  \right\rfloor}kB+\sum_{k=1}^{\left\lfloor  \frac{N}{\mathrm{lcm}(A,B)}  \right\rfloor}k\mathrm{lcm}(A,B)
$$

# 代码

```cpp
#include <bits/stdc++.h>  
using namespace std;  
#define int long long  
#define detristy ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);  
  
set<int> st;  
int n,a,b;  
  
void solve() {  
    cin >> n >> a >> b;  
    int k1 = n/a;  
    int suma = a * k1 * (k1+1)/2;  
    int k2 = n/b;  
    int sumb = b * k2 * (k2+1)/2;  
    int lcm = (a*b)/gcd(a,b);  
    int k3 = n/lcm;  
    int sumc = lcm * k3 * (k3+1)/2;  
    int ans = n*(n+1)/2 - suma - sumb + sumc;  
    cout << ans << endl;  
}  
  
signed main() {  
    detristy  
    int T = 1;  
    //cin >> T;  
    while (T--) solve();  
    return 0;  
}
```