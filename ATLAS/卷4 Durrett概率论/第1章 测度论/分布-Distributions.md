---
tags:
  - 概率论
  - 测度论
---

# 1. 分布 - Distributions

在 [[概率空间-Probability Spaces|§1.1]] 我们建立了概率空间 $(\Omega,\mathcal{F},P)$ 的框架。本节（Durrett §1.2）要回答的核心问题是：**如何用实数轴上的语言去描述随机现象？** 答案是引入**随机变量**，把样本空间上的概率「搬运」到实数轴上，进而得到**分布**与**分布函数**。

## 1.1 随机变量 - Random Variable

随机变量是一个函数 $X:\Omega\to \mathbf{R}$，把 $\Omega$ 中的样本点通过 $X(\omega)$ 映射到实数上。但并非任意函数都能当随机变量——我们必须能对它讨论「取值落在某范围内的概率」，这要求 $X$ 的任何 Borel 集的原像都是一个事件。

>[!definition] 定义 1.2.1 - 随机变量（Random Variable）
>若对实数轴上的任意波莱尔集合 $B\subset \mathbf{R}$，均有
>
>$$
>	X^{-1}(B)=\{\omega:X(\omega)\in B\}\in \mathcal{F}
>$$
>
>则称 $X$ 是一个随机变量，也称 $X$ 是 $\mathcal{F}$-可测的。
> ^def-3b7c1e

换句话说，$B$ 的原像 $X^{-1}(B)$ 必须是一个「能谈概率」的事件：只有它落在 $\mathcal{F}$ 里，我们才能定义「$X$ 的取值落在 $B$ 内」的概率 $P(X\in B)$。反之，若 $X^{-1}(B)\notin\mathcal{F}$，$X$ 落在 $B$ 里的概率就无从谈起。

对于离散概率空间 $\Omega$ 而言，$\mathcal{F}$ 通常是 $\Omega$ 的幂集，所有子集都可测，因此任意函数 $X:\Omega\to\mathbf{R}$ 都自动是随机变量——可测性约束在离散情形下「白送」。

此外，示性函数也是随机变量：对任意 $A\in\mathcal{F}$，定义

$$
	1_A(\omega)=\begin{cases}1,&\omega\in A\\0,&\omega\notin A\end{cases}
$$

$1_A$ 只取 $0$ 或 $1$ 两个值，其任意 Borel 集的原像无非是 $\varnothing$、$A$、$A^c$、$\Omega$ 四者之一，都在 $\mathcal{F}$ 中，故 $1_A$ 可测。

## 1.2 分布 - Distribution

如果 $X$ 是一个随机变量，那么样本空间 $\Omega$ 就能通过 $X$ 映射到 $\mathbf{R}$ 上；与此同时，$\Omega$ 上的概率测度 $P$ 也被 $X$ 诱导「搬运」到了 $\mathbf{R}$ 上。

我们为什么要做这个诱导？因为我们真正关心的往往是 $X$ 的取值规律（例如「骰子掷出 3 的概率」），而不是抽象的样本点 $\omega$。把 $P$ 推到实数轴上之后，$\mu(A)$ 就完整描述了 $X$ 的取值分布。称这个 $\mathbf{R}$ 上由 $X$ 诱导出的概率测度 $\mu$ 为 $X$ 的分布，或前推测度（push-forward measure），记作

$$
	\mu=P\circ X^{-1}
$$

![[Pasted image 20260725164318.png | 300]]

上图展示了概率空间内的一个事件 $X^{-1}(A)$ 通过随机变量 $X$ 映射到实数轴上的 Borel 集 $A$。分布 $\mu(A)$ 描述的是「$X$ 的取值落在 $A$ 内」的概率，它等于原像事件 $X^{-1}(A)$ 在 $\Omega$ 上的概率 $P(X^{-1}(A))$。也就是说，通过映射 $X$，我们得到如下等价关系：

$$
	\mu(A)=P(X\in A)=P(X^{-1}(A))
$$

因为 $\mu$ 是由概率测度 $P$ 诱导得到的，我们必须确认它真的还是一条测度。非负性是显然的（继承自 $P$）；接下来证明它满足可列可加性。

设 $A_i$ 是一族互不相交的 Borel 集。原像运算保持不交性：若 $A_i\cap A_j=\varnothing$，则

$$
	\{X\in A_i\}\cap\{X\in A_j\}=X^{-1}(A_i\cap A_j)=\varnothing
$$

即 $\{X\in A_i\}$ 也互不相交。根据上面的等价关系：

$$
	\mu\left(\bigcup_i A_i\right)=P\left(X\in\bigcup_i A_i\right)
$$

因为「原像的并等于并的原像」（集合论性质），

$$
	P\left(X\in\bigcup_i A_i\right)=P\left(\bigcup_i\{X\in A_i\}\right)
$$

因为概率测度 $P$ 满足可列可加性，

$$
	P\left(\bigcup_i\{X\in A_i\}\right)=\sum_i P(X\in A_i)
$$

再代回等价关系 $\mu(A_i)=P(X\in A_i)$，就有

$$
	\mu\left(\bigcup_i A_i\right)=\sum_i \mu(A_i)
$$

因此 $\mu$ 具有可列可加性，确实是一条概率测度。

## 1.3 分布函数 - Distribution Function

有了分布这个抽象概念，我们进一步希望用一个具体的实变量函数来刻画 $X$。通常用一个实变量函数 $F$ 来描述随机变量 $X$ 取值不超过 $x$ 的概率：

$$
	F(x)=P(X\leq x)
$$

称这个函数为分布函数（distribution function）。它其实就是分布 $\mu$ 在特殊集合 $(-\infty,x]$ 上的取值：$F(x)=\mu((-\infty,x])$。

分布函数具有如下性质：

>[!theorem] 定理 1.2.1 - 分布函数的性质
>若 $F$ 是随机变量 $X$ 的分布函数，则：
>1. $F$ 单调不减；
>2. $\lim_{x\to\infty}F(x)=1$，$\lim_{x\to-\infty}F(x)=0$；
>3. $F$ 是右连续的；
>4. $F(x^{-})=P(X<x)$；
>5. $P(X=x)=F(x)-F(x^{-})$。
> ^thm-1a2b3c

接下来我们逐条证明。

**性质 1（单调不减）**：若 $x\geq y$，则 $\{X\leq y\}\subset\{X\leq x\}$——$X$ 不超过较小的 $y$，自然也不超过较大的 $x$。由 [[概率空间-Probability Spaces#^cor-a238e1|测度的单调性]]，得 $P(X\leq y)\leq P(X\leq x)$，即 $F(y)\leq F(x)$。故 $F$ 单调不减。

**性质 2（两端极限）**：当 $x\to\infty$ 时，事件 $\{X\leq x\}$ 单调上升趋于 $\Omega$；当 $x\to-\infty$ 时单调下降趋于 $\varnothing$。由测度的连续性，

$$
	\lim_{x\to\infty}F(x)=\lim_{x\to\infty}P(X\leq x)=P(\Omega)=1,\qquad \lim_{x\to-\infty}F(x)=P(\varnothing)=0
$$

**性质 3（右连续）**：形式化地，要证 $\lim_{y\downarrow x}F(y)=F(x)$。当 $y\downarrow x$（$y$ 从右侧单调下降趋于 $x$）时，事件族 $\{X\leq y\}$ 单调下降趋于 $\{X\leq x\}$：

$$
	\{X\leq y\}\downarrow\{X\leq x\},\qquad y\downarrow x
$$

由测度的上连续性，$P(X\leq y)\downarrow P(X\leq x)$，即 $\lim_{y\downarrow x}F(y)=F(x)$。故 $F$ 右连续。

**性质 4（左极限）**：性质 4 刻画的是左极限的概率意义。当 $y\uparrow x$（$y$ 从左侧单调上升趋于 $x$）时，事件族 $\{X\leq y\}$ 单调上升趋于 $\{X<x\}$：

$$
	\{X\leq y\}\uparrow\{X<x\},\qquad y\uparrow x
$$

（这个并集确实等于 $\{X<x\}$：若 $X(\omega)<x$，取 $y$ 满足 $X(\omega)<y<x$，则 $\omega\in\{X\leq y\}$。）由测度的下连续性，

$$
	F(x^{-})=\lim_{y\uparrow x}F(y)=\lim_{y\uparrow x}P(X\leq y)=P(X<x)
$$

即左极限等于 $X$ 严格小于 $x$ 的概率。

**性质 5（单点概率）**：因为 $\{X\leq x\}$ 可分解为互不相交的并 $\{X<x\}\cup\{X=x\}$，由可加性：

$$
	P(X\leq x)=P(X<x)+P(X=x)
$$

代入 $F(x)=P(X\leq x)$ 与性质 4 的 $F(x^{-})=P(X<x)$，移项即得：

$$
	P(X=x)=F(x)-F(x^{-})
$$

性质 5 的意义在于：$X$ 恰好取单个值 $x$ 的概率，正是 $F$ 在 $x$ 处的「跳跃」高度。若 $F$ 在 $x$ 处连续（没有跳跃），则 $P(X=x)=0$。

定理 1.2.1 告诉我们：**任何**分布函数都必须满足「单调不减、两端极限为 1 和 0、右连续」这三条性质。一个自然的问题是反过来：任意一个满足这三条性质的函数，是否一定是某个随机变量的分布函数？答案是肯定的。

>[!theorem] 定理 1.2.2 - 分布函数性质的充分性
>若函数 $F$ 同时满足：
>1. $F$ 单调不减；
>2. $\lim_{x\to\infty}F(x)=1$，$\lim_{x\to-\infty}F(x)=0$；
>3. $F$ 是右连续的。
>
>则 $F$ 必可作为某一随机变量 $X$ 的分布函数。
> ^thm-4d5e6f

证明的思路是构造。设 $\Omega=(0,1)$，$\sigma$-代数 $\mathcal{F}$ 是 $\Omega$ 上的 Borel 集，概率测度 $P$ 是勒贝格测度。在 $\Omega$ 中，样本点落在区间 $(0,x]$（其中 $x<1$）内的概率就是该区间的长度：$P(\omega\leq x)=x$。

对任意样本点 $\omega\in(0,1)$，定义随机变量

$$
	X(\omega)=\sup\{y:F(y)<\omega\}
$$

其中 $\sup$ 代表上确界。在 $F$ 严格递增且连续的情形下，$X$ 就是反函数 $F^{-1}$；但一般情况下 $F$ 可能只是单调不减、甚至不连续，因此我们用 $\sup$ 来定义，以保证 $X$ 处处有定义。

我们要证 $P(X\leq x)=F(x)$。若能证明集合相等

$$
	\{\omega:X(\omega)\leq x\}=\{\omega:\omega\leq F(x)\}
$$

那么左边概率 $P(X\leq x)$ 就等于右边 $\{\omega:\omega\leq F(x)\}$ 的勒贝格测度，即区间 $(0,F(x)]$ 的长度 $F(x)$，命题即得证。

证明集合相等需要两个方向的包含关系：

1. 若 $\omega\leq F(x)$，则 $X(\omega)\leq x$；
2. 若 $\omega>F(x)$，则 $X(\omega)>x$。

**方向一**：记 $S=\{y:F(y)<\omega\}$。若 $\omega\leq F(x)$，则对任意 $y\in S$，有 $F(y)<\omega\leq F(x)$，故 $F(y)<F(x)$。由 $F$ 单调不减，$y<x$。于是 $x$ 是 $S$ 的一个上界，而 $X(\omega)=\sup S$，故 $X(\omega)\leq x$。

**方向二**：若 $\omega>F(x)$，由 $F$ 的右连续性，存在 $\epsilon>0$ 使得

$$
	F(x+\epsilon)<\omega
$$

因此 $x+\epsilon\in S$，从而 $X(\omega)=\sup S\geq x+\epsilon>x$。

两个方向都成立，故 $\{\omega:X(\omega)\leq x\}=\{\omega:\omega\leq F(x)\}$，于是 $P(X\leq x)=F(x)$，$F$ 确实是 $X$ 的分布函数。∎

# 2. 同分布 - Equal in Distribution

>[!definition] 定义 1.2.2 - 同分布（Equal in Distribution）
>若两个随机变量 $X$ 和 $Y$ 在实数轴 $(\mathbf{R},\mathcal{R})$ 上诱导出相同的概率测度 $\mu$，则称 $X$ 与 $Y$ 同分布，记作
>
>$$
>	X\overset{d}{=}Y
>$$
> ^def-7a8b9c

等价地，$X\overset{d}{=}Y$ 当且仅当对所有的 $x$ 都有

$$
	P(X\leq x)=P(Y\leq x)
$$

即两者具有相同的分布函数。

注意：**同分布不等于相同**。例如抛一枚均匀硬币，令 $X=1_A$（正面朝上取 $1$），$Y=1_{A^c}$（反面朝上取 $1$）。$X$ 与 $Y$ 是两个不同的函数，但都满足 $P(X=1)=P(Y=1)=\frac{1}{2}$，故 $X\overset{d}{=}Y$。同分布关心的是「取值规律」，而不关心「哪个样本点对应哪个值」。

# 3. 概率密度函数 - Density Function

>[!definition] 定义 1.2.3 - 概率密度函数（Density Function）
>若分布函数 $F(x)=P(X\leq x)$ 可以表示为
>
>$$
>	F(x)=\int_{-\infty}^{x}f(y)\,\mathrm{d}y
>$$
>
>则称 $X$ 具有概率密度函数 $f_X(x)$。
> ^def-d0e1f2

概率密度 $f$ 直观上是「单位长度上的概率质量」：在 $x$ 附近一个很小区间 $[x,x+\mathrm{d}x]$ 内，$X$ 落入其中的概率约为 $f(x)\,\mathrm{d}x$。密度是分布函数的变化率——$F(x)$ 是 $f$ 的「累积」，$f(x)$ 是 $F(x)$ 的「瞬时增量」。
