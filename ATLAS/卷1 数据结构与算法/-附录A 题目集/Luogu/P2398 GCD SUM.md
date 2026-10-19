---
tags:
  - 欧拉函数
  - 数论分块
---
https://www.luogu.com.cn/problem/P2398

使用欧拉函数的性质： $n=\sum_{d|n}\phi(d)$ 。

即 $\gcd(i,j)=\sum_{d|\gcd(i,j)}\phi(d)$ 。

原式子写为：
$$
\sum_{i=1}^n \sum_{j=1}^n \sum_{d|\gcd(i,j)}\phi(d)
$$
其中 $d|\gcd(i,j)$ 等价于 $d|i$ 且 $d|j$ ，替换可以得到：
$$
\sum_{i=1}^n \sum_{j=1}^n \sum_{d=1}^n \phi(d)[d|i][d|j]
$$
其中 $\phi(d)$ 的计算与 $i,j$ 无关，因此可以交换到前面：
$$
\sum_{d=1}^n \left( \phi(d)\sum_{i=1}^n \sum_{j=1}^n [d|i][d|j]\right)
$$
对于内部的双层求和，$i,j$ 是独立的，因此可以各自求和再相乘，其中
$$
\sum_{i=1}^n [d|i]
$$
本质上是求 $1$~$n$ 里 $d$ 的倍数的个数，为 $\left\lfloor  \frac{n}{d}  \right\rfloor$ 。

因此最终答案为：

$$
\sum_{d=1}^n \phi(d)\left\lfloor  \frac{n}{d}  \right\rfloor ^2
$$
欧拉函数用线筛预处理，对于较大的 $n$ 可以考虑数论分块。

![[2398.cpp]]
