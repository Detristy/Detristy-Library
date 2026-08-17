---
tags:
  - 单调栈
  - 构造
CF_Rating: "*1600"
---
https://codeforces.com/contest/2171/problem/F

这题是 [[CF2171D Rae Taylor and Trees (easy ver.)]] 的困难版本，在判断是否能构造的基础上还要求如果能构造则要构造出来。

显然每合并一个连通块就相当于连一条边，而为了保证 $u>v$ 且 $P_{u}>P_{v}$ ，我们考虑让新连通块的最大边和栈顶连通块的最小边相连即可保证正确性。

![[CF2171F.cpp]]

