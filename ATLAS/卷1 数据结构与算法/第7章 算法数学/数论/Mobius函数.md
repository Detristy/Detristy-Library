---
tags:
  - Mobius函数
  - 数论（算法）
---
# 定义

定义莫比乌斯函数：
$$
\mu(n)=
\begin{cases}
1,&n=1,\\
0,&n\text{ is divisible by a square }>1,\\
(-1)^k,&n\text{ is the product of }k\text{ distinct primes}.\\
\end{cases}
$$
莫比乌斯函数指出，若非 $1$ 正整数 $n$ 存在质因数分解，任何一个质因数出现超过一次时 $\mu(n)=0$ ，否则设质因数个数为 $k$ ，$\mu(n)=(-1)^k$ 。特殊地，$\mu(1) =1$ 。

# 性质

1. $\mu(n)$ 是非完全积性函数。
2. 对正整数 $n$ ，对于 $\sum_{d|n}\mu(d)$ ，若 $n=1$ ，其值为 $1$ ，否则为 $0$ 。

## 推论

通过使用莫比乌斯函数的性质，我们可以翻译两数互素的条件。

对于 $gcd(x,y)$ ，有：
$$
[\gcd(x,y)=1]=\sum_{d|\gcd(x,y)}\mu(d)
$$
这个推论将两数互素的条件转化为了莫比乌斯求和的表达式。

# 质因数分解求莫比乌斯函数

```cpp
int mu(int n) {
  int res = 1;
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      n /= i;
      // 每个因数只能出现一次
      if (n % i == 0) return 0;
      res = -res;
    }
  }
  //特判 n != 1
  //此时仍然剩余一个质因子，取一次反
  if (n > 1) res = -res;
  return res;
}
```

复杂度为 $O(\sqrt{ n })$ 。
# 线性筛预处理莫比乌斯函数

```cpp
std::vector<int> get_mu(int n) {
  std::vector<int> mu(n + 1), primes;
  std::vector<bool> not_prime(n + 1);
  primes.reserve(n);
  mu[1] = 1;
  for (int x = 2; x <= n; ++x) {
    if (!not_prime[x]) {
      primes.push_back(x);
      mu[x] = -1;
    }
    for (int p : primes) {
      if (x * p > n) break;
      not_prime[x * p] = true;
      if (x % p == 0) {
        mu[x * p] = 0;
        break;
      } else {
        mu[x * p] = -mu[x];
      }
    }
  }
  return mu;
}
```

原理和线性筛预处理欧拉函数是一样的。

