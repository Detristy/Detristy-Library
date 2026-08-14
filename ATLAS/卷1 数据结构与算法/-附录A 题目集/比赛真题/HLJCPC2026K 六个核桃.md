---
tags:
  - 贪心
---
https://qoj.ac/contest/3768/problem/18332

题目的目标是构造排列 $p$ 使得最大化
$$
	\sum_{i}\min(|p_{i}-i|,m)
$$

显然对于给定的 $m$ ，每一个点的最大贡献即为 $m$ ，整体的上界即为 $nm$ 。

当 $m\leq\left\lfloor  \frac{n}{2}  \right\rfloor$ 时考虑循环位移，能够使得尽可能多的数的 $|p_{i}-i|=m$ ，尽量靠进上界。
但当 $m>\left\lfloor  \frac{n}{2}  \right\rfloor$ 时位移会失效，此时只位移 $k=\left\lfloor  \frac{n}{2}  \right\rfloor$ 。
对于前 $[1,n-k]$ 个位置，$p_{i}=\min\left( \left\lfloor  \frac{n}{2}  \right\rfloor,m \right)=\left\lfloor  \frac{n}{2}  \right\rfloor$ ；
对于后 $(k,n]$ 个位置，$p_{i}'=\min(n-k,m)=\min\left( \left\lceil  \frac{n}{2}  \right\rceil ,m\right)=\left\lceil  \frac{n}{2}   \right\rceil$ 。
因此总和为
$$
	k(n-k)+(n-k)k = \left\lfloor  \frac{n^{2}}{2}  \right\rfloor 
$$
![[HLJCPC2026K.cpp]]
