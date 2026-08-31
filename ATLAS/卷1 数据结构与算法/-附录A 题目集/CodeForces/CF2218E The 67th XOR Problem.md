---
tags:
  - 贪心
  - 数学（算法）
---
https://codeforces.com/contest/2218/problem/E

考虑异或的两个性质：
1. $a\oplus a = 0$ 
2. $a \oplus 0=a$ 

因此可以得到 $a\oplus b\oplus b=a$

于是我们试着模拟题目操作，对于
$$
	[a_{1},a_{2},a_{3},a_{4}\dots a_{n}] 
$$
选择 $a_{m}$ 执行一次操作：
$$
	[a_{1}\oplus a_{m},a_{2}\oplus a_{m},a_{3}\oplus a_{m},a_{4}\oplus a_{m}\dots a_{n}\oplus a_{m}]
$$
此时删除 $a_{m}$ ，再选择 $a_{x}$ 执行一次操作，对于 $k(1\leq k\leq n)$：
$$
	a_{k}\oplus a_{m}\oplus(a_{1}\oplus a_{m}) = a_{k}\oplus a_{x}
$$
此时删除 $a_{x}$ ，数组最终将变为：
$$
	[a_{1}\oplus a_{x},a_{2}\oplus a_{x},a_{3}\oplus a_{x}\dots a_{n}\oplus a_{x}]
$$
会发现此时数组的值跟 $a_{m}$ 没有任何关系，由异或的性质 1 和性质 2 共同得到。

因此最终值将是最后一次选择的元素 $x$ 和最后一次被选择的元素 $y$ 异或后的值，暴力枚举这个数对 $(x,y)$ 即可。

![[CF2218E.cpp]]
