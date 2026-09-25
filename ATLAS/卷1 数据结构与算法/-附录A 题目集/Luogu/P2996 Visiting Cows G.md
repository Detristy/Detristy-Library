---
tags:
  - 树形DP
---
https://www.luogu.com.cn/problem/P2996

定义 $dp[u][0/1]$ 是第 $u$ 个节点不访问时所访问过的最大数目，状态转移方程：
$$
	dp[u][1] = dp[u][1]+dp[v][0]
$$
$$
	dp[u][0]=dp[u][0]+\max(dp[v][0],dp[v][1])
$$

![[2996.cpp]]
