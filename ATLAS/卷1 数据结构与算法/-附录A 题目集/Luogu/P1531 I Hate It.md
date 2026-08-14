---
tags:
  - 线段树
Difficulty:
  - Green
---
https://www.luogu.com.cn/problem/P1531

单点修改+区间查询最值

在这里涉及了单点修改的事情，因此我们要在这里讨论 pushdown 和 lazy_tag 的逻辑。

我们考虑最值运算的分配律：

$$  
max(a_1+k,a_2+k,\cdots,a_n+k)=max(a_1,a_2,\cdots,a_n)+k  
$$

也就是说当我们给整个区间加上 $k$ 的时候最值也只加 $k$ ，这和加法不同，于是我们在 pushdown 的更新里只需要让 `rt[x] += lazy[x]` 就可以了。

![[1531.cpp]]
