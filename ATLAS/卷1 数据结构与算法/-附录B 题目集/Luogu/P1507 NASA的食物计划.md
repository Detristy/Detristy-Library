---
tags:
  - 01背包
  - 背包DP
Difficulty:
  - Orange
---
https://www.luogu.com.cn/problem/P1507

这里每一个物品都带有两个属性：体积 $h_{i}$ 和质量 $t_{i}$ ，因此需要开二维的01背包。
对应的状态转移方程为：
$$
	dp_{i,j}=\max(dp_{i,j},dp_{i-h_{i},j-t_{i}}+k_{i})
$$

![[1507.cpp]]
