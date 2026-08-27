---
tags:
  - 字符串
---

# 题目背景

Don't stop funky music!

Bass drop!

This stuff is really fresh! This stuff is really fresh!
This stuff is really fresh! This stuff is really fresh!
This stuff is really fresh! This stuff is really fresh!
This stuff is really fresh! Wow!

# 题目描述

为了让DX超性能フルメタル少女拥有更高的超性能，我们需要让数据传输更加高效，这就需要使用压缩技术了！

将字符串中重复的字段进行压缩，通常的方法是将其压缩成重复的片段+重复次数。例如：`xxxxxxyyyababyuanshenniubi` 会被压缩成 `x6y3ab2yuanshe1n2iubi1` 。

不过高效数据的传输只有压缩可不够，解压也是关键。你需要将压缩后的字符串 $s$ 解压为它原来的字符串 $t$ 。

# 输入格式

本题共 $T$ 组输入数据。

第一行输入一个整数 $T$ ，表示数据组数。

接下来的 $T$ 行，第 $i$ 行输入一个字符串 $s_{i}$ ，表示压缩后的字符串。

# 输出格式

输出 $T$ 行，每行一个字符串 $t$ ，第 $i$ 行的字符串为 $t_{i}$ ，表示 $s_{i}$ 解压后的结果。

# 样例

输入：

```
3
ThisStuffIsReallyFun4
Funky2Music3
x2y3z1
```

输出：

```
ThisStuffIsReallyFunThisStuffIsReallyFunThisStuffIsReallyFunThisStuffIsReallyFun
FunkyFunkyMusicMusicMusic
xxyyyz
```

输入：

```
1
Yes!10
```

输出：

```
Yes!Yes!Yes!Yes!Yes!Yes!Yes!Yes!Yes!Yes!
```

# 说明

本题采用子任务捆绑测试。每个测试点隶属于且仅隶属于一个子任务；只有当某子任务内的全部测试点通过时，你才能获得该子任务对应的分数。

对于 $100\%$ 的数据：$1 \le T \le 10^5$，每个 $s_i$ 不含空格，$\sum |s_i| \le 10^6$。保证压缩串合法，即 $s_i$ 由若干「片段 + 次数」交替拼接而成，其中片段为非空且只含有大小写字母和 `?!.()` 的不含空格的字符串，次数为无前导零的正整数。保证所有解压结果的总长度 $\sum |t_i| \le 10^7$。

| 子任务编号 | 分值  |    约束     | 特殊性质    |
| :---: | :-: | :-------: | :------ |
|   1   | 15  |   $T=1$   | 次数均为一位数 |
|   2   | 20  | $T\le 10$ | 次数均为一位数 |
|   3   | 30  |     无     | 次数均为一位数 |
|   4   | 35  |     无     | 无       |