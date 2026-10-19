---
tags:
  - 数论（算法）
  - Mobius反演
---
莫比乌斯反演的内容如下。

设 $f(x),g(x)$ 都是数论函数，那么有：
$$
f(n) = \sum_{d\mid n}g(d) \iff g(n) = \sum_{d\mid n}\mu\left(\dfrac{n}{d}\right)f(d) .
$$
