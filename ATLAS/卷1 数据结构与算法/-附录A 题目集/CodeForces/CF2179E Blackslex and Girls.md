---
tags:
  - 贪心
---
https://codeforces.com/problemset/problem/2179/E

首先判断两个党派的人数是否够投票份额，即必须有 $x+y\geq \sum p_{i}$ 。

当 01 都有的时候考虑贪心，对于 0 的地区就让 $a$ 不投只有 $b$ 投，此时让 $b$ 投最小的，即 $\left\lfloor  \frac{p_{i}}{2}  \right\rfloor + 1$ ，对于 1 的地区同理。此时只要满足  $x+y\geq \sum p_{i}$ 就能保证一定能通过某种分配方式实现 $a_{i}+b_{i}\geq p_{i}$ 。

当只有 0 的时候，要求对于每个选区都 $a_{i} \geq b_{i}+1$ ，求和后即 $\sum a_{i}\geq \sum b_{i}+n$，同时也要有 $x \geq \sum a_{i}$ 。
当只有 1 的时候，要求对于每个选区都 $b_{i} \geq a_{i} + 1$ ，求和同理，同时也要有 $y \geq \sum b_{i}$ 。

![[CF2179E.cpp]]
