---
tags:
  - 概率论
  - 测度论
---
# 1. 概率空间

为了讨论概率，我们定义概率空间。

>[!definition] 定义 1 - 概率空间（Probability Space）
>定义概率空间是一个三元组 $(\Omega,\mathcal{F},P)$ 。
>其中：
>称 $\Omega$ 是样本空间，即事件的所有结果的集合（outcomes）。
>$\mathcal{F}$ 是事件域，即某些事件的集合（events）。
>$P:\mathcal{F}\to [0,1]$ 是一个函数，称为概率测度（probability measure），对应 $\mathcal{F}$ 中每一个事件的权重（即对应的概率）。

$\Omega$ 是所有结果的集合，例如投骰子得到的所有结果的集合为 $\{1,2,3,4,5,6\}$，而 $\mathcal{F}$ 是某些结果组成的事件 $A$ 构成的集合，$A$ 是 $\Omega$ 的子集，例如事件 「骰子结果是偶数」对应的事件就是 $\{2,4,6\}$。

我们需要 $\mathcal{F}$ 满足一些合理的封闭性条件，这引出了 $\sigma$-代数的概念。

>[!definition] 定义 2 - $\sigma$-代数（$\sigma$-field）
>设 $\mathcal{F}$ 是由 $\Omega$ 的某些子集构成的集族。称 $\mathcal{F}$ 是 $\sigma$-代数（或称 $\sigma$-field），如果满足：
>1. $\varnothing \in \mathcal{F}$。
>2. **对补运算封闭**：若 $A\in \mathcal{F}$，则 $A^{c}\in \mathcal{F}$。
>3. **对可数并运算封闭**：若 $A_{i}\in \mathcal{F}\;(i=1,2,\dots)$ 是一列集合，则 $\bigcup_{i=1}^{\infty}A_{i}\in \mathcal{F}$。

直观地说，$\sigma$-代数就是一个「对可数次集合运算封闭」的事件集合——取补、可数并、可数交、差集，都不会跑出 $\mathcal{F}$。

>[!example] 例 1 - 骰子的 $\sigma$-代数
>取 $\Omega=\{1,2,3,4,5,6\}$。最简单的 $\sigma$-代数是 $\mathcal{F}_{0}=\{\varnothing ,\Omega\}$——它什么信息都没有。
>
>最丰富的 $\sigma$-代数是 $\Omega$ 的幂集 $\mathcal{F}_{\max}=2^{\Omega}$，包含了 $\Omega$ 的所有子集（共 $2^{6}=64$ 个）——它知道一切。
>
>一个介于两者之间的例子是 $\mathcal{F}=\{\varnothing ,\{1,3,5\},\{2,4,6\},\Omega\}$，它只区分「奇数」和「偶数」两类结果。

由 $\sigma$-代数的定义可以推出两条直接的性质：

>[!corollary] 性质 1 - 对可数交封闭
>若 $A_{i}\in \mathcal{F}\;(i=1,2,\dots)$，则 $\bigcap_{i=1}^{\infty}A_{i}\in \mathcal{F}$。由 De Morgan 律和条件 2,3 立得。

>[!corollary] 性质 2 - 对差运算封闭
>若 $A,B\in \mathcal{F}$，则 $A\setminus B\in \mathcal{F}$。因为 $A\setminus B=A\cap B^{c}$。

有了事件域 $\mathcal{F}$，接下来我们定义概率测度 $P$。Kolmogorov 在 1933 年给出了概率的公理化定义：

>[!definition] 定义 3 - 概率测度（Kolmogorov 公理）
>$P:\mathcal{F}\to [0,1]$ 称为概率测度，如果满足：
>1. **非负性**：对任意 $A\in \mathcal{F}$，有 $P(A)\geq 0$。
>2. **规范性**：$P(\Omega)=1$。
>3. **可数可加性**：若 $A_{1},A_{2},\dots$ 是 $\mathcal{F}$ 中两两不相交的集合列（即 $A_{i}\cap A_{j}=\varnothing ,\,i\neq j$），则
>
>$$
>P\left(\bigcup_{i=1}^{\infty}A_{i}\right)=\sum_{i=1}^{\infty}P(A_{i})
>$$

这三条公理是概率论的基石，所有概率性质都可以从它们推导出来。

# 2. 基本性质

>[!corollary] 性质 3 - $P(\varnothing)=0$
>取 $A_{1}=\Omega$，$A_{2}=A_{3}=\dots=\varnothing$，由可数可加性：
>
>$$
>P(\Omega)=P(\Omega)+P(\varnothing)+P(\varnothing)+\dots=P(\Omega)+\sum_{i=2}^{\infty}P(\varnothing)
>$$
>
>由于 $P(\Omega)=1<\infty$，必须有 $P(\varnothing)=0$。

>[!corollary] 性质 4 - 有限可加性
>若 $A_{1},\dots,A_{n}$ 两两不相交，则
>
>$$
>P\left(\bigcup_{i=1}^{n}A_{i}\right)=\sum_{i=1}^{n}P(A_{i})
>$$
>
>只需在可数可加性中取 $A_{n+1}=A_{n+2}=\dots=\varnothing$ 即得。

>[!corollary] 性质 5 - 补集公式
>对任意 $A\in \mathcal{F}$，
>
>$$
>P(A^{c})=1-P(A)
>$$
>
>因为 $\Omega=A\cup A^{c}$ 且 $A\cap A^{c}=\varnothing$，由有限可加性和规范性：$1=P(\Omega)=P(A)+P(A^{c})$。

>[!corollary] 性质 6 - 单调性
>若 $A\subset B$，则 $P(A)\leq P(B)$。
>
>因为 $B=A\cup (B\setminus A)$ 且两者不相交，由有限可加性和非负性：$P(B)=P(A)+P(B\setminus A)\geq P(A)$。

>[!corollary] 性质 7 - 次可加性（Union Bound）
>对任意（不一定不相交的）$A_{1},A_{2},\dots,A_{n}\in \mathcal{F}$，
>
>$$
>P\left(\bigcup_{i=1}^{n}A_{i}\right)\leq \sum_{i=1}^{n}P(A_{i})
>$$
>
>$n=2$ 时 $P(A\cup B)=P(A)+P(B)-P(A\cap B)\leq P(A)+P(B)$。一般情形归纳即得。

>[!corollary] 性质 8 - 容斥原理（Inclusion-Exclusion）
>对任意 $A_{1},\dots,A_{n}\in \mathcal{F}$，
>
>$$
>P\left(\bigcup_{i=1}^{n}A_{i}\right)=\sum_{i=1}^{n}P(A_{i})-\sum_{i<j}P(A_{i}\cap A_{j})+\sum_{i<j<k}P(A_{i}\cap A_{j}\cap A_{k})-\cdots+(-1)^{n+1}P(A_{1}\cap\cdots\cap A_{n})
>$$
>
>$n=2$ 即 $P(A\cup B)=P(A)+P(B)-P(A\cap B)$。$n=3$：
>
>$$
>P(A\cup B\cup C)=P(A)+P(B)+P(C)-P(A\cap B)-P(B\cap C)-P(C\cap A)+P(A\cap B\cap C)
>$$

>[!corollary] 性质 9 - 连续性（Continuity）
>（**上连续**）若 $A_{n}\uparrow A$（即 $A_{1}\subset A_{2}\subset\cdots$ 且 $A=\bigcup_{n}A_{n}$），则 $P(A_{n})\uparrow P(A)$。
>
>（**下连续**）若 $A_{n}\downarrow A$（即 $A_{1}\supset A_{2}\supset\cdots$ 且 $A=\bigcap_{n}A_{n}$），则 $P(A_{n})\downarrow P(A)$。

>[!important]
>性质 9 表明概率测度 $P$ 在单调集合列的极限下是连续的——这是**可数可加性**带来的关键好处。在构造复杂事件的概率时，连续性经常用来把「极限事件」的概率转化为「有限事件」概率的极限。

>[!warning] 注意
>可数可加性（公理 3）是概率测度区别于一般有限可加测度的核心性质。它允许我们处理「极限」操作——很多关键定理（如大数定律、中心极限定理）的证明都依赖于此。
