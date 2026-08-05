---
tags:
  - 概率论
  - 测度论
---

# 1. 可测映射 - Measurable Map

## 1.1 可测映射与随机变量

在 [[02 分布-Distributions | §1.2]] 中，我们定义了随机变量 $X:\Omega\to\mathbf{R}$ 需要满足 $X^{-1}(B)\in\mathcal{F}$ 对任意 Borel 集 $B$ 成立。Durrett 在 §1.3 中将这一概念推广至一般的可测空间。

>[!definition] 定义 1.3.1 - 可测映射（Measurable Map）
>设 $(\Omega,\mathcal{F})$ 和 $(S,\mathcal{S})$ 是两个可测空间。称函数 $X:\Omega\to S$ 是从 $(\Omega,\mathcal{F})$ 到 $(S,\mathcal{S})$ 的**可测映射**，如果：
>
>$$
>	X^{-1}(B)\equiv\{\omega:X(\omega)\in B\}\in\mathcal{F},\quad \forall B\in\mathcal{S}
>$$
>
> ^def-5e8a2c

当 $(S,\mathcal{S})=(\mathbf{R}^d,\mathcal{R}^d)$ 且 $d>1$ 时，$X$ 称为**随机向量**（random vector）；当 $d=1$ 时，$X$ 就是普通的**随机变量**（random variable）。

换句话说，可测映射就是把可测空间「搬运」到另一个可测空间上，同时保证原像的可测性不丢失。

## 1.2 可测性的判定定理

直接对所有 $B\in\mathcal{S}$ 验证可测性太过繁琐。下面的定理告诉我们，**只需在生成 $\mathcal{S}$ 的一个集合族上验证即可**。

>[!theorem] 定理 1.3.1 - 可测性的生成类判定
>设 $\mathcal{A}$ 生成 $\mathcal{S}$（即 $\mathcal{S}=\sigma(\mathcal{A})$）。若对所有 $A\in\mathcal{A}$ 都有 $\{\omega:X(\omega)\in A\}\in\mathcal{F}$，则 $X$ 是可测映射。
>
> ^thm-3f7d1a

我们证明这个定理。记 $\{X\in B\}$ 为 $\{\omega:X(\omega)\in B\}$ 的简写。考虑集合族：

$$
	\mathcal{B}=\{B:\{X\in B\}\in\mathcal{F}\}
$$

首先验证 $\mathcal{B}$ 是 $\sigma$-域：
- **可数并封闭**：$\{X\in\bigcup_i B_i\}=\bigcup_i\{X\in B_i\}$，若每个 $\{X\in B_i\}\in\mathcal{F}$，由 $\mathcal{F}$ 是 $\sigma$-域知其并也在 $\mathcal{F}$ 中，故 $\bigcup_i B_i\in\mathcal{B}$。
- **补封闭**：$\{X\in B^c\}=\{X\in B\}^c$，同理 $\{X\in B\}^c\in\mathcal{F}$，故 $B^c\in\mathcal{B}$。

由条件知 $\mathcal{B}\supset\mathcal{A}$，又 $\mathcal{S}=\sigma(\mathcal{A})$ 是包含 $\mathcal{A}$ 的最小 $\sigma$-域，所以 $\mathcal{B}\supset\mathcal{S}$。即对所有 $B\in\mathcal{S}$ 都有 $\{X\in B\}\in\mathcal{F}$，$X$ 可测得证。

>[!example] 例 1.3.2 - $\mathbf{R}$ 上的判定集
>在 $(\mathbf{R},\mathcal{R})$ 中，$\mathcal{A}$ 可以取：
>- $\{(-\infty,x]:x\in\mathbf{R}\}$
>- $\{(-\infty,x):x\in\mathbf{Q}\}$（有理数端点就够！）
>
>也就是说，要判断 $X$ 是否是随机变量，只需验证对所有的 $x$，$\{X\leq x\}\in\mathcal{F}$ 即可。
> ^ex-9c2b3d

>[!example] 例 1.3.3 - $\mathbf{R}^d$ 上的判定集
>在 $(\mathbf{R}^d,\mathcal{R}^d)$ 中，$\mathcal{A}$ 可以取所有开矩形：
>
>$$
>	\{(a_1,b_1)\times\cdots\times(a_d,b_d):-\infty<a_i<b_i<\infty\}
>$$
>
>也可以取更大的开集族。
> ^ex-d1e4f6

注意到，从定理 1.3.1 证明中出现的两个等式可以推出：若 $\mathcal{S}$ 是 $\sigma$-域，则 $\{\{X\in B\}:B\in\mathcal{S}\}$ 也是一个 $\sigma$-域。

## 1.3 $\sigma(X)$ — 由 $X$ 生成的 $\sigma$-域

上面这个 $\sigma$-域正是使得 $X$ 可测的**最小** $\sigma$-域，我们给它一个名字。

>[!definition] 定义 - $\sigma(X)$（由 $X$ 生成的 $\sigma$-域）
>设 $X$ 是从 $(\Omega,\mathcal{F})$ 到 $(S,\mathcal{S})$ 的可测映射。称
>
>$$
>	\sigma(X)=\{\{X\in B\}:B\in\mathcal{S}\}
>$$
>
>为由 $X$ 生成的 $\sigma$-域。它是 $\mathcal{F}$ 的子 $\sigma$-域，也是 $\Omega$ 上使得 $X$ 可测的最小 $\sigma$-域。
>
> ^def-8a4c1f

直观上，$\sigma(X)$ 包含了「仅通过观察 $X$ 的取值就能判断是否发生」的所有事件。对于给定的 $\omega$，你只能知道 $X(\omega)$ 是什么——$\sigma(X)$ 恰好刻画了这些信息。

# 2. 随机变量的运算封闭性

接下来我们讨论：对随机变量做运算，什么时候结果还是随机变量？

## 2.1 可测映射的复合

>[!theorem] 定理 1.3.4 - 可测映射的复合
>若 $X:(\Omega,\mathcal{F})\to(S,\mathcal{S})$ 和 $f:(S,\mathcal{S})\to(T,\mathcal{T})$ 都是可测映射，则 $f(X)$ 也是可测映射（从 $(\Omega,\mathcal{F})$ 到 $(T,\mathcal{T})$）。
>
> ^thm-b2d7e4

证明很简单：对任意 $B\in\mathcal{T}$，

$$
	\{\omega:f(X(\omega))\in B\}=\{\omega:X(\omega)\in f^{-1}(B)\}
$$

因为 $f$ 可测，$f^{-1}(B)\in\mathcal{S}$；又因为 $X$ 可测，$\{X\in f^{-1}(B)\}\in\mathcal{F}$。得证。

由这个定理立即可得：若 $X$ 是随机变量，则 $cX$（$c\in\mathbf{R}$）、$X^2$、$\sin X$ 等等都是随机变量——因为这些都是一维 Borel 可测函数。

## 2.2 多元情形

>[!theorem] 定理 1.3.5 - 多元可测函数的复合
>若 $X_1,\dots,X_n$ 是随机变量，$f:(\mathbf{R}^n,\mathcal{R}^n)\to(\mathbf{R},\mathcal{R})$ 可测，则 $f(X_1,\dots,X_n)$ 是随机变量。
>
> ^thm-c3e8f5

**证明**：由定理 1.3.4，只需证明 $(X_1,\dots,X_n)$ 是一个随机向量（即取值在 $\mathbf{R}^n$ 上的可测映射）。

取 $\mathcal{A}$ 为所有 Borel 矩形的族（即 [[#^ex-d1e4f6 | 例 1.3.3]] 中的生成类），对 $A_1\times\cdots\times A_n$：

$$
	\{(X_1,\dots,X_n)\in A_1\times\cdots\times A_n\}=\bigcap_{i=1}^n\{X_i\in A_i\}\in\mathcal{F}
$$

因为形如 $A_1\times\cdots\times A_n$ 的集合生成 $\mathcal{R}^n$，由 [[#^thm-3f7d1a | 定理 1.3.1]] 即得结论。

这个定理的意思是：只要 $f$ 是一个 Borel 可测的多元函数，把随机变量塞进去，出来的还是随机变量。

## 2.3 和的封闭性

>[!theorem] 定理 1.3.6 - 随机变量之和
>若 $X_1,\dots,X_n$ 是随机变量，则 $X_1+\cdots+X_n$ 也是随机变量。
>
> ^thm-d4f9a6

**证明**：由 [[#^thm-c3e8f5 | 定理 1.3.5]]，只需证 $f(x_1,\dots,x_n)=x_1+\cdots+x_n$ 是 Borel 可测的。

由 [[#^ex-9c2b3d | 例 1.3.2]]，只需验证 $\{x:x_1+\cdots+x_n<a\}$ 是 Borel 集——而这是一个开集，自然在 $\mathcal{R}^n$ 中。

类似地，乘积 $X_1X_2\cdots X_n$ 也是随机变量（$f$ 取乘积函数，也是连续的）。

## 2.4 上下确界与极限

>[!theorem] 定理 1.3.7 - inf、sup、liminf、limsup
>若 $X_1,X_2,\dots$ 是一列随机变量，则以下都是随机变量：
>
>$$
>	\inf_n X_n,\quad \sup_n X_n,\quad \liminf_{n\to\infty} X_n,\quad \limsup_{n\to\infty} X_n
>$$
>
> ^thm-e5a0b7

我们逐一证明。

**下确界**：因为一个序列的下确界 $<a$ 等价于存在某一项 $<a$（若所有项都 $\geq a$，下确界也 $\geq a$），我们有：

$$
	\{\inf_n X_n < a\} = \bigcup_n \{X_n < a\}\in\mathcal{F}
$$

由 [[#^ex-9c2b3d | 例 1.3.2]]（取 $\mathcal{A}=\{(-\infty,a):a\in\mathbf{Q}\}$ 就够），得 $\inf_n X_n$ 是随机变量。

**上确界**：类似地，$\{\sup_n X_n > a\}=\bigcup_n\{X_n > a\}\in\mathcal{F}$。

**下极限与上极限**：我们利用定义

$$
	\liminf_{n\to\infty} X_n = \sup_n\left(\inf_{m\geq n} X_m\right)
$$

$$
	\limsup_{n\to\infty} X_n = \inf_n\left(\sup_{m\geq n} X_m\right)
$$

对每个 $n$，$Y_n=\inf_{m\geq n}X_m$ 是随机变量（由上一步），所以 $\sup_n Y_n$ 也是随机变量。上极限同理。

这个定理非常重要：它保证了我们对随机变量序列取极限时，极限（在可测的意义下）仍然在概率论的研究框架内。

# 3. 几乎必然收敛 - Almost Sure Convergence

有了上确界和下确界的可测性，我们就能严格定义「几乎必然收敛」。

注意到：

$$
	\{\omega:\lim_{n\to\infty}X_n\ \text{存在}\} = \{\omega:\limsup_{n\to\infty}X_n - \liminf_{n\to\infty}X_n = 0\}
$$

由于 $\limsup$ 和 $\liminf$ 都是随机变量（[[#^thm-e5a0b7 | 定理 1.3.7]]），它们的差也是，所以极限存在的集合是一个可测集。记这个集合为 $\Omega_0$。

>[!definition] 定义 1.3.2 - 几乎必然收敛（Almost Sure Convergence）
>若 $P(\Omega_0)=1$（即极限存在的事件概率为 1），则称 $X_n$ **几乎必然收敛**（converges almost surely，简记为 a.s.），记作 $X_n\to X$ a.s.。
>
>在测度论中，这种收敛方式称为**几乎处处收敛**（almost everywhere convergence）。
>
> ^def-2f7b3d

为了让极限在整个 $\Omega$ 上都有定义（而不只是在 $\Omega_0$ 上），一个常见的技巧是令

$$
	X_\infty = \limsup_{n\to\infty} X_n
$$

这样 $X_\infty$ 一定存在——只不过可能取到 $+\infty$ 或 $-\infty$。

# 4. 扩展实值随机变量 - Extended Real-Valued Random Variables

这就自然引出了一个问题：如果随机变量允许取 $\pm\infty$，框架还能运转吗？

>[!definition] 定义 1.3.3 - 扩展实值随机变量
>设 $D\in\mathcal{F}$，称定义在 $D$ 上、取值于 $\mathbf{R}^*=[-\infty,\infty]$ 的函数 $X$ 是一个**扩展实值随机变量**，如果对所有的 $B\in\mathcal{R}^*$ 都有：
>
>$$
>	X^{-1}(B)=\{\omega:X(\omega)\in B\}\in\mathcal{F}
>$$
>
>其中 $\mathcal{R}^*$ 是 $\mathbf{R}^*$ 上的 Borel $\sigma$-域，由区间 $[-\infty,a)$、$(a,b)$、$(b,\infty]$（$a,b\in\mathbf{R}$）生成。
>
> ^def-3c8d4e

由于 $(\mathbf{R}^*,\mathcal{R}^*)$ 本身也是一个可测空间，前面所有的定理（1.3.1 到 1.3.7）对扩展实值随机变量全部自动成立。

这就解决了极限可能取 $\pm\infty$ 的麻烦——我们把实数线两端「封上」，让极限始终落在 $[-\infty,\infty]$ 内，同时保持了所有可测性结论。Durrett 用这个技巧来处理 a.s. 收敛时极限不定义在 $D$ 外的情形，非常优雅 (｡･ω･｡)
