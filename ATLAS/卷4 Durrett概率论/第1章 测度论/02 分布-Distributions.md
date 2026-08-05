---
tags:
  - 概率论
  - 测度论
---
# 1. 分布函数

## 1.1 随机变量 - Random Variable

随机变量是一个函数 $X:\Omega\to \mathbf{R}$ ，将 $\Omega$ 中的样本点通过 $X(\omega)$ 映射到实数上，其定义如下：

>[!definition] 定义 1.2.1 随机变量
>若对于实数轴上的任意波莱尔集合 $B \subset \mathbf{R}$ ，均有 $X^{-1}(B)=\{\omega:X(\omega)\in B\}\in \mathcal{F}$ ，则称 $X$ 是一个随机变量，且 $X$ 是 $\mathcal{F}$-可测的。
>


$B$ 的原像即能找到一个对应的事件与某个范围或某个值相对应。
反之，如果 $X^{-1}(B)$ 不在 $\mathcal{F}$ 中，我们就无法定义 $X$ 的取值落在 $B$ 里的概率。

对于离散概率空间 $\Omega$ 而言，因为所有的子集都是可测的，因此 $X$ 显然是一个随机变量。

此外，示性函数也是随机变量，示性函数满足对于任意集合 $A\in \mathcal{F}$ ，都有
$$1_A(\omega) = \begin{cases} 1 & \omega \in A \\ 0 & \omega \notin A \end{cases}$$
## 1.2 分布 - Distribution

如果 $X$ 是一个随机变量，那么样本空间 $\Omega$ 就能通过 $X$ 映射到 $\mathbf{R}$ 上，同时，$\Omega$ 上的概率测度 $P$ 也通过 $X$ 诱导到了 $\mathbf{R}$ 上，称这个 $\mathbf{R}$ 上由 $X$ 诱导出的概率测度 $\mu$ 为 $X$ 的分布或前推测度（Push-forward measure），记作：
$$
	\mu=P\circ X^{-1}
$$

![[Pasted image 20260725164318.png | 300]]

上图展示了概率空间内的一个事件 $X^{-1}(A)$ 通过随机变量 $X$ 映射到了实数轴上的一个波莱尔集 $A$ 上，我们可以通过分布 $\mu(A)$ 来描述事件通过 $X$ 映射后的部分落在 $A$ 内的概率，其对应事件落在概率空间内概率，我们可以用概率测度 $P(X^{-1}(A))$ 来描述，也就是说通过映射 $X$ ，我们能得出下面这个等价关系：
$$
	\mu(A)=P(X\in A)=P(X^{-1}(A))
$$

因为 $\mu$ 实际上是通过概率测度 $P$ 诱导得到的，因此我们需要保证其也满足测度的性质，其中非负性是显然的，接下来我们证明其满足可列可加性。

设 $A_{i}$ 是一族互不相交的波莱尔集，则显然其关于 $X$ 的原像也互不相交。
根据刚刚推导出的等价关系，有：
$$
	\mu\left( \bigcup_{i}A_{i} \right)=P\left( X\in \bigcup_{i}A_{i} \right)
$$
因为原像的并等于并的原像（集合论性质）所以
$$
	\mu\left( \bigcup_{i}A_{i} \right)=P\left( \bigcup_{i} \{X\in A_{i}\} \right)
$$
因为概率测度 $P$ 满足可列可加性，因此
$$
		\mu\left( \bigcup_{i}A_{i} \right)=\sum_{i}P(X\in A_{i})
$$
再由等价关系，就有
$$
		\mu\left( \bigcup_{i}A_{i} \right)=\sum_{i}\mu(A_{i})
$$
因此 $\mu$ 具有可列可加性。

## 1.3 分布函数 - Distribution Function

通常用一个实变量函数 $F$ 来刻画随机变量 $X$ 的取值在 $\leq x$ 范围内的概率：
$$
	F(x)=P(X\leq x)
$$
称这个函数为分布函数。

分布函数具有如下的性质：

>[!theorem] 定理 1.2.1 分布函数的性质
>1. $F$ 单调不减。
>2. $\lim_{ n \to \infty }F(x)=1$ ，$\lim_{ n \to -\infty }F(x)=0$ 。
>3. $F$ 是右连续的。
>4. $F(x^{-})=P(X<x)$ 。
>5. $P(X=x)=F(x)-F(x^{-})$ 。

接下来我们对这些性质进行证明。

对于性质 1 ，若 $x \geq y$ 则 $\{X\leq x\}\subset\{X\leq y\}$ ，由 [[01 概率空间-Probability Spaces#^cor-a238e1 | 测度的性质]] ，可得 $P(X\leq x)\leq P(X \leq y)$ ，故而 $F(x) \leq F(y)$。

对于性质 2，$\lim_{ x \to \infty }F(x)=F(\Omega)=1$ ，且 $\lim_{ x \to -\infty }F(x)=F(\varnothing)=0$ 。

对于性质 3，形式化地，即要证 $\lim_{ y \downarrow x }F(y)=F(x)$ 。当 $y \downarrow x$ 时，$\{X\leq x\}\downarrow\{X\leq y\}$ ，因此 $\lim_{ y \downarrow x }F(X\leq y)=F(X \leq x)$ ，因此 $\lim_{ y \downarrow x }F(y)=F(x)$。

对于性质 4，其表示左极限的概率意义，即当 $y$ 从左侧不断逼近 $x$ 的时候，其概率不断单调递增逼近 $P(X\leq x)$ ，但不会相等，因此是 $P(X<x)$ 。证明和性质 3 基本同理。

对于性质 5 ，其表示单点概率，即随机变量恰好等于某个值的概率。根据概率的可加性：
$$
	P(X\leq x)=P(X<x)+P(X=x)
$$
移项整理并代入 $F(x)$ 的定义可得：
$$
	P(X=x)=F(x)-F(x^{-})
$$

定理 1.2.1 指出，只要函数是分布函数，其一定满足单调不减、极限为 1 和 0、右连续三条性质。而反之，我们可以指出，如果一个函数满足单调不减、极限为 1 和 0、右连续三条性质，其一定是一个分布函数。接下来的定理 1.2.2 提出了这一点。

>[!theorem] 定理 1.2.2 分布函数性质的充分性
>若函数 $F$ 同时满足：
>1. $F$ 单调不减。
>2. $\lim_{ n \to \infty }F(x)=1$ ，$\lim_{ n \to -\infty }F(x)=0$ 。
>3. $F$ 是右连续的。
>
>则 $F$ 即可作为某一随机变量 $X$ 的分布函数。

设 $\Omega=(0,1)$ ，$\sigma$-代数 $\mathcal{F}$ 是 $\Omega$ 上的波莱尔集，概率测度 $P$ 是勒贝格测度。

在 $\Omega$ 中，如果存在一个区间 $(0,x]$ 其中 $x<1$，则样本点 $\omega$ 小于等于 $x$ 的概率 $P(\omega\leq x)=x$ ，即对应区间的长度。 

对于任意一个样本点 $\omega\in(0,1)$ ，我们定义随机变量 $X$：
$$
	X(\omega)=\sup\{y:F(x)<\omega\}
$$
其中 $\sup$ 代表上确界。
在 $F$ 单调递增连续的情形下，$X = F^{-1}$ ，但多数情况下 $F$ 并不单调递增（可能单调不减）甚至并不连续 ，因此我们使用 $\sup$ 来定义。

我们要证明的是 $P(X\leq x)=F(x)$ ，其中如果 $X$ 的分布函数是 $F$ ，那么等号左边我们可以写成 $P(\omega:X(\omega)\leq x)$ ，也可以写成 $P(\omega:\omega\leq F(x))$ ，即得到：
$$
	\{\omega:X(\omega)\leq x\}=\{\omega:\omega\leq F(x)\}
$$
我们只要证出这个等价关系，那么 $F$ 自然就是分布函数。

证明这两个集合相等我们需要证明两个方向：
 1. 如果 $\omega\leq F(x)$ 则 $X(\omega)\leq x$ 
 2. 如果 $\omega>F(x)$ 则 $X(\omega)>x$ 
这两个方向应同时成立。

对于第一个方向：
我们用 $S$ 来表示集合 $\{y:F(y)<\omega\}$ 。
因为 $\omega\leq F(x)$ ，则对于任意 $y\in S$ 都 $F(y) < \omega \leq F(x)$ ，显然 $F(y)<F(x)$ 。
因为 $F$ 单调不减，因此 $y < x$ 。
因为对于任意一个 $y$ 都有 $y<x$ ，那么 $x$ 就是 $S$ 的一个上界。
根据我们的定义， $X(\omega)=\sup S$ ，那么必然 $X(\omega)\leq x$ 。

对于第二个方向：
因为 $\omega>F(x)$ ，根据 $F$ 具有右连续性，因此必然存在一个 $\epsilon>0$ ，使得：
$$
	F(x+\epsilon)<\omega
$$
因此 $x+\epsilon\in S$ 。
根据我们的定义， $X(\omega)=\sup S$ ，因此必然 $X(\omega)\geq x+\epsilon>x$ 。

# 2. 同分布 - Equal in Distribution

>[!definition] 定义 1.2.2 同分布
>若两随机变量 $X$ 和 $Y$ 在实数轴 $(\mathbf{R},\mathcal{R})$ 上诱导得到相同的概率测度 $\mu$ ，则称两个随机变量同分布，记作：
>
>$$
>	X=_{d}Y
>$$

等价地，两个变量同分布即对所有的 $x$ 都有：
$$
	P(X\leq x)=P(Y\leq x)
$$
需要注意的是，两个随机变量同分布不等价于两个随机变量相同。

# 3. 概率密度函数 - Density Function

>[!definition] 定义 1.2.3 概率密度函数
>如果分布函数 $F(x)=P(X\leq x)$ 可以表示为：
>
>$$
>	F(x)=\int_{-\infty}^{x}f(y)\mathrm{d}y
>$$
>则称 $X$ 具有概率密度函数 $f_{X}(x)$ 。

概率密度直观上而言是单位长度上的概率，即在 $x$ 附近的一个区间 $[x,x+\mathrm{d}x]$ 内，随机变量落在这个区间内的概率为 $f(x)\mathrm{d}x$ 。

