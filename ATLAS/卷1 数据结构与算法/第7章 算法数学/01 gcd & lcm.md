---
tags:
  - 算法
  - 数论（算法）
  - GCD/LCM
---
gcd 是 Greatest Common Divisor 的缩写，即最大公约数；
lcm 是 Least Common Multiple 的缩写，即最小公倍数。

# 1. 最大公约数 gcd

对于不全为零的整数 $a,b$ ，记他们的最大公约数为 $\gcd(a,b)$ ，可以简写为 $(a,b)$

在 C++ STL 中的 gcd 函数将 0 和 0 的最大公约数约定为 0

## 1.1 性质

下面所有的数均约定不全为 0 的整数；

最大公约数运算是可结合的，即对于 $a,b,c$ ，有 $\gcd(a,\gcd(b,c))=\gcd(\gcd(a,b),c)$；

最大公约数运算是可交换的，即对于 $a,b$ 有 $\gcd(a,b)=\gcd(b,a)$；

由于负数的存在，这个运算并不是自反的， $\gcd(a,a)=|a|$；

若 $\gcd(a,b)=1$ 则 $a,b$ 互质。

## 1.2 欧几里得算法

首先我们得到这么一个性质：

$$  
\gcd(a,b) = \gcd(b,a\bmod b)  
$$

也可以写作： $\gcd(kb+r,b) = \gcd(r,b)$

于是我们可以运用这个性质，使用递归的形式求出最大公约数，递归的终点是 $b=0$ ，即 $a\bmod b=0$ 时

```cpp
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
```

这个算法的最坏时间复杂度为 $O(n)$

## 2. 最小公倍数 lcm

对于不全为零的整数 $a,b$ ，记他们的最小公倍数为 $\text{lcm}(a,b)$ ，可以简写为 $[a,b]$

和 gcd 相同，lcm 的运算是可交换的，可结合的

如果 $a\mid b$，则 $[a,b]=|b|$

对于乘法（正整数）是可分配的 $[ma_1,\dots,ma_n]=|m|[a_1,\dots,a_n]$

lcm 和 gcd 组合可以得到 $(a,b)[a,b]=|ab|$ ，既然我们知道 gcd 的求法，那么我们就可以直接求出 $[a,b]=\frac{|a,b|}{(a,b)}$