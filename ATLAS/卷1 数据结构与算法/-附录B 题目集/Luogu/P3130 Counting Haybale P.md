---
tags:
  - 线段树
Difficulty:
  - Green
---
https://www.luogu.com.cn/problem/P3130

区间修改+区间查询+区间最值。

我们需要考虑区间修改对区间最值的影响，在 [[P1531 I Hate It]] 分析了这个问题，不同的是，这里涉及的是区间修改，因此我们需要在 pushdown 里也对最小值进行维护，让最小值也加上 lazy。

![[3130.cpp]]
