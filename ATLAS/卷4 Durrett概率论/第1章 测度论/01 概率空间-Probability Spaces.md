---
tags:
  - 概率论
  - 测度论
---
# 1. 概率空间 - Probability Space

## 1.1 概率空间

为了讨论概率，我们定义概率空间。

>[!definition] 定义 1.1.1 - 概率空间（Probability Space）
>定义概率空间是一个三元组 $(\Omega,\mathcal{F},P)$ 。
>其中：
>称 $\Omega$ 是样本空间，即事件的所有结果的集合（outcomes）。
>$\mathcal{F}$ 是事件域，即某些事件的集合（events）。
>$P:\mathcal{F}\to [0,1]$ 是一个函数，称为概率测度（probability measure），对应 $\mathcal{F}$ 中每一个事件的权重（即对应的概率）。

$\Omega$ 是所有结果的集合，例如投骰子得到的所有结果的集合为 $\{1,2,3,4,5,6\}$，而 $\mathcal{F}$ 是某些结果组成的事件 $A$ 构成的集合，$A$ 是 $\Omega$ 的子集，即 $\mathcal{F}$ 是 $\Omega$ 的幂集 ，例如事件 「骰子结果是偶数」对应的事件就是 $\{2,4,6\}$。

## 1.2 $\sigma$-域 - $\sigma$ Field

我们需要 $\mathcal{F}$ 满足一些合理的封闭性条件，这引出了 $\sigma$-域的概念。

>[!definition] 定义 1.1.2 - $\sigma$-域（$\sigma$-field）
>设 $\mathcal{F}$ 是由 $\Omega$ 的某些子集构成的集族。称 $\mathcal{F}$ 是 $\sigma$-域（或称 $\sigma$-field），如果满足：
>1. $\varnothing \in \mathcal{F}$。
>2. **对补运算封闭**：若 $A\in \mathcal{F}$，则 $A^{c}\in \mathcal{F}$。
>3. **对可数并运算封闭**：若 $A_{i}\in \mathcal{F}\;(i=1,2,\dots)$ 是一列集合，则 $\bigcup_{i=1}^{\infty}A_{i}\in \mathcal{F}$。

## 1.3 $\sigma$-域的性质

>[!corollary] 性质 1.1.1
>任意个 $\sigma$-域的交集 $\bigcap_{i\in I}\mathcal{F_{i}}$ 仍然是一个 $\sigma$-域。
> ^cor-34d8e5

# 2. 可测空间 - Measurable Space

## 2.1 可测空间和测度

可测空间就是没有概率测度 $P$ 的概率空间 $(\Omega,\mathcal{F})$ ，测度是一个能够在可测空间上使用的函数，接下来给出其定义：

>[!definition] 定义 1.1.3 - 测度（Measure）
>测度是一个函数 $\mu:\mathcal{F}\to \mathbf{R}$ ，满足：
>1. 非负性：对于所有的 $A \in \mathcal{F}$ 都有 $\mu(A)\geq \mu(\emptyset)=0$ .
>2. 可列可加性：如果 $A_{i}\in \mathcal{F}$ 是互不相交的可数集序列，那么：
>   
>   $$
>	\mu\left( \bigcup _{i}A_{i} \right)=\sum_{i}\mu(A_{i})
>   $$
> ^def-ea2971

对于第二个性质，表示的是集合取并后的总测度是各个集合的测度之和。

## 2.1 测度的性质

设 $\mu$ 是一个 $(\Omega,\mathcal{F})$ 上的测度，则：

>[!corollary] 性质 1.1.2 - 单调性
>若 $A \subset B$ ，则 $\mu(A)\leq \mu(B)$ 。 
> ^cor-a238e1

接下来证明性质 1 ，设 $A\subset B$ ，则 $B$ 可以被分解为 $B=A+(B-A)$ ，由测度的可加性，我们可以得到：
$$
	\mu(B)=\mu(A)+\mu(B-A)
$$
又由 $\mu(B-A)\geq{0}$ （非负性），我们可以得到 $\mu(A)\leq \mu(B)$ 。

>[!corollary] 性质 1.1.3 - 次可加性
>若$A \subset \bigcup_{m=1}^{\infty} A_m$ ，则 $\mu(A) \le \sum_{m=1}^{\infty} \mu(A_m)$
> ^cor-d64dba

这个定理指的是，如果由 $m$ 个集合所覆盖，那么 $A$ 的测度不会大于这些覆盖 $A$ 的集合的测度之和。

接下来我们证明这个性质，设 $A_{i}$ 是覆盖的第 $i$ 个集合，我们令 $A_{i}'=A_{i}\cap A$ 是这个集合和 $A$ 重叠的区域。
接下来我们构造一系列互不相交的集合 $B$ ，令 $B_{1}=A_{1}',B_{2}=A_{2}'-A_{1}'\dots B_{n}=A_{n}'-\bigcup_{m=1}^{n-1}A_{m}'$ 。
此时所有的 $B_{i}$ 互不相交，且由我们所设，这些 $B_{i}$ 的并集恰好是 $A$ 。
于是由可加性，$\mu(A)=\sum_{m=1}^{\infty}\mu(B_{m})$ 

又因为 $B_{i}$ 实际上是 $A_{i}$ 的子集，因此由单调性：$\mu(B_{m})\leq \mu(A_{m})$ ，于是就有：
$$
	\mu (A)\leq \sum_{m=1}^{\infty}\mu(A_{m})
$$
>[!corollary] 性质 1.1.4 - 下连续性
>若 $A_i \uparrow A$ ，则 $\mu(A_i) \uparrow \mu(A)$ 

上箭头指的是单调递增地趋于，如果一系列集合不断变大，并逼近极限集合 $A$，那么这些集合的测度也会单调递增，并收敛至 $\mu(A)$ 。

我们依旧构造互不相交的集合，定义 $A_{0}=\emptyset,~B_{n}=A_{n}-A_{n-1}$ ，那么肯定有 $A=\bigcup_{m=1}^{\infty}B_{m}$ ，同时 $A_{n}=\bigcup_{m=1}^{n}B_{m}$ ，由可列可加性：
$$
	\mu(A)=\lim_{ n \to \infty } \sum_{m=1}^{n}\mu(B_{m})
$$
而 $\lim_{ n \to \infty } \sum_{m=1}^{n}\mu(B_{m})$ 恰好就是 $\mu(A_{n})$ ，所以就有 $\mu(A_i) \uparrow \mu(A)$ 。

>[!corollary] 性质 1.1.5 - 上连续性
>若 $A_i \downarrow A$ ，则 $\mu(A_i) \downarrow \mu(A)$ 

下箭头是单调递减地趋于，如果一系列集合不断变小，并逼近极限集合 $A$，那么这些集合的测度也会单调递减，并收敛至 $\mu(A)$ 。

性质 4 的证明和性质 3 基本相同，这里从略。

# 3. 离散概率空间

对于样本空间 $\Omega$ ，我们设其是一个可数集，$\mathcal{F}$ 是 $\Omega$ 的幂集，$\omega$ 是这个样本空间里的每一个样本点，设每一个样本点的概率值为 $p(\omega)\geq{0}$，那么显然有：
$$
	\sum_{\omega\in \Omega}p(\omega)=1
$$
那么对于任意一个事件 $A$ ，其概率 $P(A)$ 就是 $A$ 包含所有样本点的概率之和：
$$
	P(A)=\sum_{\omega\in A}p(\omega)
$$

# 4 集合生成的 $\sigma$ 域

由 [[01 概率空间-Probability Spaces#^cor-34d8e5 | σ-域的性质]] ，如果集合族 $\mathcal{A}$ 并不是 $\sigma$-域，我们可以对所有包含 $\mathcal{A}$ 的 $\sigma$-域取交集，此时会得到一个新的 $\sigma$-域，其是包含 $\mathcal{A}$ 的最小的 $\sigma$-域。称之为由 $\mathcal{A}$ 生成的 $\sigma$-域，记作 $\sigma(\mathcal{A})$ 。

## 4.1 波莱尔 $\sigma$ 域 - Borel $\sigma$ field

对于集合生成的 $\sigma$-域，我们进一步思考，如果在 $\mathbf{R}$ 上，这个 $\mathcal{A}$ 应该是开集，而由其生成的 $\sigma$-域，我们就定义为波莱尔$\sigma$-域。

>[!definition] 定义 1.1.4 - 波莱尔 $\sigma$-域
>设 $\mathbf{R}^{d}$ 是 $d$ 维的实数空间，定义波莱尔$\sigma$-域为包含 $\mathbf{R}^{d}$ 的所有开集（开区间）的最小 $\sigma$-域，记作 $\mathcal{R}^{d}$ 。
>一维的波莱尔 $\sigma$ 域就直接写作 $\mathcal{R}$ 。

进一步地，波莱尔$\sigma$-域中的所有集合称为波莱尔集。
# 5. 测度函数 - Stieljes Measure Function

我们先在可测空间 $(\mathbf{R},\mathcal{R})$ 上定义测度，需要用到斯蒂尔杰斯（Stieljes）测度函数，其是一个满足下面两个性质的函数：

1. 单调不减；
2. 右连续。

其中单调不减指的是，当区间变大的时候，其测度不会变小；
而右连续指的是，从右侧逼近极限的时候，有：
$$
	\lim_{ y\downarrow x } F(y)=F(x)
$$
>[!theorem] 定理 1.1.1 - (a,b]的测度
>通过右连续性，我们可以定义 $(a,b]$ 的测度为：
>$$
>	\mu((a,b])=F(b)-F(a)
>$$
> ^thm-6e288c

目前我们或许疑惑为什么这个区间是左开右闭，我们不妨将其拆解为“左开”和“右闭”两个部分，这里先解释“右闭”。

由于 Stieljes 函数是右连续的，当我们从右侧收缩区间的时候，对应的测度也会收缩，区间右闭恰好是满足这个条件的。
## 5.1 勒贝格测度 - Lebesgue Measure

如果我们令 $F(x)=x$ （显然满足两个性质），那么区间 $(a,b]$ 的测度就是 $b-a$ ，这就对应其几何长度。同时，这个测度即勒贝格测度。

# 6. 代数 - Algebra
## 6.1 半代数 - Semialgebra

为了能让区间能进行基础的交集和补集，我们定义半代数。

>[!definition] 定义 1.1.5 - 半代数
>定义半代数是一个满足下列性质的集合族 $\mathcal{S}$ ：
>1. 交集封闭性：若 $A,B\in \mathcal{S}$ ，则 $A\cap B\in \mathcal{S}$ 。
>2. 补集可拆分：任意集合 $A$ 的补集 $A^{c}$ ，都可以被表示为有限个互不相交的 $\mathcal{S}$ 中的集合的并集。
> ^def-e4c041

通过使用半代数，我们就可以分析“左开右闭”的优越性了。
设半代数 $\mathcal{S_{1}}$ 是空集和所有形如 $(a,b]$ 的区间。我们取区间 $A=(a,b]$ ，那么其补集就是：
$$
	A^{c}=(-\infty,a]\cup(b,+\infty]
$$
这恰好是两个互不相交的左开右闭的区间的并集，符合半代数中“补集可拆分”的性质。
## 6.2 代数

然而半代数还是有一定的局限性，进一步地，我们可以定义代数。

>[!definition] 定义 1.1.6 - 代数
>定义代数是一个满足下列性质的一个集合族 $\mathcal{A}$ ：
>1. 补集封闭性：若 $A\in \mathcal{A}$ ，则 $A^{c}\in \mathcal{A}$ 。
>2. 有限并集封闭性：若 $A,B\in \mathcal{A}$ ，则 $A\cup B\in \mathcal{A}$ 。 

对于有限并集封闭性，由于 $A\cap B=(A^{c}\cup B^{c})^{c}$ 由有限并集封闭性和补集封闭性，显然可以得到代数也满足 $A\cap B\in \mathcal{A}$ （有限交集封闭性）。

代数和 $\sigma$ 域（或者 $\sigma$ 代数）还是有一定区别的，代数是对有限并集封闭，而 $\sigma$ 域是对可数无穷并集封闭。

## 6.3 半代数生成代数

我们可以从半代数出发将一个集合族转变为代数，称这个代数是从半代数生成的代数。

>[!lemma] 引理 1.1.1
>半代数 $\mathcal{S}$ 的 所有有限个互不相交的集合的并集 构成的集合族 $\bar{\mathcal{S}}$ 是代数。
> ^lem-154002

证明 $\bar{\mathcal{S}}$ 是代数，我们分为三步：

设 $A=\sum_{i}S_{i},~B=\sum_{j}T_{j}$ ，其中 $A,B\in \mathcal{\bar{S}}$，$S,T\in \mathcal{S}$ ，这里 $\sum$ 代表不相交并集。

先证交集封闭，我们对 $A,B$ 取并集，那么：
 $$
	A\cap B=\sum_{i}\sum_{j}(S_{i}\cap T_{j})
 $$
因为 $\mathcal{S}$ 是半代数，因此有 $S_{i}\cap T_{j} \in \mathcal{S}$ ，故而有 $A\cap B\in \bar{\mathcal{S}}$，满足交集封闭性。

接下来证补集封闭，根据 [[01 概率空间-Probability Spaces#^def-e4c041 | 半代数的补集可拆性]] ，任意元素 $S$ 的补集 $S^{c}$ ，可以被写为 $\mathcal{S}$ 中有限个互不相交元素的并，因此 $S^{c}\in \bar{\mathcal{S}}$ 。
根据德摩根律，并集的补集等于补集的交集：
$$
	A^{c}=\left( \bigcup_{i=1}^{n}S_{i} \right)=\bigcap_{i=1}^{n}S_{i}^{c}
$$
而 $S_{c}^{i}\in \bar{\mathcal{S}}$  ，由刚刚证明得到的交集封闭性，可以得到 $A^{c}\in \bar{\mathcal{S}}$ ，因此满足补集封闭性。

运用交集封闭性和补集封闭性，以及 $A\cap B=(A^{c}\cup B^{c})^{c}$ ，我们可以证明其也满足并集封闭性。
综上所述， $\bar{\mathcal{S}}$ 是代数。

## 6.4 代数上的有限可加测度
我们引入了代数，自然考虑考察代数上的测度。

>[!definition] 定义 1.1.7 代数上的有限可加测度
>定义代数上的有限可加测度是一个满足下列性质的集合上的函数 $\mu$ ：
>1. 非负性
>2. 可列可加性
> ^def-2df7f7

这个代数上的测度性质较弱，对比 [[01 概率空间-Probability Spaces#^def-ea2971 | 定义 1.1.3 ]] 的测度是定义在 $\sigma$-域上的，而代数上的有限可加测度是定义在代数上的，代数不满足可数无穷并，只满足有限并集封闭，因此这里的可列可加性只适用于并集仍然在代数中的情形。

在测度论中，许多良好的性质要求这个测度是 $\sigma$-有限的，因此我们来讨论这个性质。

>[!definition] 定义 1.1.8 $\sigma$-有限性
>如果存在一系列的集合序列 $A_{i}\in \mathcal{A}$ ，满足下列两个性质，就称其测度是 $\sigma$-有限的：
>1. 有限性： $\mu(A_{i})<\infty$
>2. 并集填满整个空间：$\bigcup_{n}A_{n}=\Omega$ 

考虑到这个集合序列实际上可能是混乱的，虽然能够满足上述的两个性质，但是我们仍然希望其性质更加优美，例如它们的排列满足某些规律，因此我们不妨考虑整理这个集合序列。

构造一个新的集合序列 $A'_{i}$ ，满足：
1. $n=1$ 时，$A_{1}'=A_{1}$
2. $n\geq 2$ 时，$A'_{n}=\bigcup_{m=1}^{n}A_{m}$ 
通过这样的构造，我们就能保证 $A_{i}'$ 是一个单调不减的序列（即 $A_{i}'\uparrow\Omega$），同时这些集合的测度也是 $\sigma$-有限的。

这是一个整理方式，接下来我们考虑将其整理为两两互不相交的集合序列。
构造一个新的集合序列 $A'_{i}$ ，满足：
1. $n=1$ 时，$A_{1}'=A_{1}$
2. $n\geq 2$ 时，$A'_{n}=A_{n}\cap\left( \bigcap_{m=1}^{n-1}A_{m}^{c} \right)$ 
通过这样的构造，我们对于每一个 $A_{i}$ 都舍去前面重复过的部分，这样就能保证两两互不相交了。

因为这两个构造都是符合定义的，因此在接下来的证明中，我们可以直接假设这个测度下的集合序列单调或者互不相交。

## 6.5 测度延拓定理

因为 $\sigma$-域对可数无穷并运算封闭，因此直接在 $\sigma$-域上定义测度是非常困难的。
我们不难考虑通过曲线救国的方式来解决这个问题，即将测度从半代数延拓到代数上并进一步延拓到 $\sigma$-域上。

>[!theorem] 定理 1.1.2 测度延拓定理（Carathéodory 开拓定理）
>设 $\mathcal{S}$ 是半代数，$\mu$ 是定义在 $\mathcal{S}$ 上的测度，满足 $\mu(\varnothing)=0$ 。
>提出下列两个假设：
>1. 测度满足有限可加性：若 $S\in \mathcal{S}$ 是 **有限个** 互不相交的集合 $S_{i}\in \mathcal{S}$ 的并集，则 $\mu(S)=\sum_{i}\mu(S_{i})$ 。
>2. 测度满足可数次可加性： 若 $S\in \mathcal{S}$ 是 **可数无限个** 互不相交的集合 $S_{i}\in \mathcal{S}$ 的并集，则 $\mu(S)\leq \sum_{i\geq 1}\mu(S_{i})$ 。
>
>若测度 $\mu$ 满足上述两个假设，则 $\mu$ 就存在唯一的定义在 $\mathcal{S}$ 生成的代数 $\bar{\mathcal{S}}$ 上的延拓 $\bar{\mu}$ ，如果这个延拓满足 sigma有限性，那么其就可以进一步地延拓为定义在整个 $\sigma$-域（$\sigma(\mathcal{S})$）上的测度 $\nu$ 。
> ^thm-fc9001

对于第二个假设的检验，我们需要使用第一个假设。即在之假设半代数上的测度具有有限可加性的前提下，我们需要证明其在代数上的延拓具有有限可加性和有限次可加性，因此有下面这个引理：

>[!lemma] 引理 1.1.2
>1. 有限可加性：若 $A,B_{i}\in \bar{\mathcal{S}}$ ，且 $A=+_{i=1}^{n}B_{i}$ ，那么 $\bar{\mu}(A)=\sum_{i}^{n}\bar{\mu}(B_{i})$ 。
>2. 有限次可加性：若 $A,B_{i}\in \bar{\mathcal{S}}$ ，且 $A\subset \bigcup_{i=1}^{n}B_{i}$ ，那么 $\bar{\mu}(A)\leq\sum_{i}^{n}\bar{\mu}(B_{i})$ 。
> ^lem-b7b2b9

我们接下来证明引理 1.1.2 。
我们先证明有限可加性：由 [[01 概率空间-Probability Spaces#^lem-154002 | 引理 1.1.1]] ，因为 $\bar{\mathcal{S}}$ 是 $\mathcal{S}$ 生成的代数，因此其可以表示为有限个两两不交的集合的并：
$$
	B_{i}=+_{j}S_{i,j}~~(S\in \mathcal{S})
$$
同时又有：
$$
	A=+_{i=1}^{n}B_{i}
$$
因此上述两式合并可以得到：
$$
	A=+_{i,j}S_{i,j}
$$
由测度的性质，有：
$$
	\bar{\mu}(A)=\sum_{i,j}\mu(S_{i,j})
$$
同时
$$
	\bar{\mu}(B_{i})=\sum_{j}\mu(S_{i,j})
$$
故而两式联立可得
$$
	\bar{\mu}(A)=\sum_{i}^{n}\bar{\mu(B_{i})}
$$
接下来证明有限次可加性，分为两个步骤。
先证明 $n=1$ 的情形，明显 $A\subset B$ ，因此 $B$ 可以被拆分为 $A$ 内的部分，和 $A$ 外的部分，即：
$$
B=A+(B∩A^{c})
$$
括号内的部分也属于代数 ，因此
$$
	\bar{\mu}(B) = \bar{\mu}(A) + \bar{\mu}(B \cap A^c)
$$
由非负性，可以得到
$$
	\bar{\mu}(A) \le \bar{\mu}(B)
$$
接下来考虑 $n\geq 2$ 的情形，将 $B_{i}$ 拆分为两两互不相交的集合，令
$$
F_k = B_k \cap (B_1^c \cap \dots \cap B_{k-1}^c)
$$
注意到
$$A = A \cap \left( \bigcup_{i=1}^n B_i \right) = A \cap \left( \sum_{k=1}^n F_k \right) = \sum_{k=1}^n (A \cap F_k)$$
因此
$$\bar{\mu}(A) = \sum_{k=1}^n \bar{\mu}(A \cap F_k)$$
因为 $\bar{\mu}(A) = \sum_{k=1}^n \bar{\mu}(A \cap F_k)$ ，同时由测度的单调性， $\bar{\mu}(A \cap F_k) \le \bar{\mu}(F_k)$ ，因此
$$\bar{\mu}(A) \le \sum_{k=1}^n \bar{\mu}(F_k)$$
又由 $F_{k}$ 的定义，有 $\bar{\mu}(F_{k}) \leq \bar{\mu}(B_{k})$
因此：
$$\bar{\mu}(A) \le \sum_{k=1}^n \bar{\mu}(F_k) \le \sum_{k=1}^n \bar{\mu}(B_k)$$
因此有限次可加性也是成立的。

# 7. Lebesgue-Stieltjes 测度定理 和 高维情形下的测度

## 7.1 证明

回到 [[01 概率空间-Probability Spaces#^thm-6e288c | 定理 1.1.1]] ，这个重新声明定理的内容如下：

>[!theorem] 定理 1.1.3 Lebesgue-Stieltjes 测度定理
>若 $F$ 是 $\mathbf{R}$ 上的一个单调递增且右连续的函数，则存在一个唯一的测度 $\mu$ ，满足：
>
>$$
>	\mu((a,b])=F(b)-F(a)
>$$

有了测度延拓定理作为工具，此时我们就能证明这个定理了。

因为 $(a,b]$ 这类区间构成的集合族 $\mathcal{S}$ 实际上是一个半代数，因此要验证这个 $\mu$ 成立，根据 [[01 概率空间-Probability Spaces#^thm-fc9001|定理 1.1.2]]， 我们只需要验证这个测度在半代数上满足有限可加性和可数次可加性即可。

先证明满足有限可加性：
考虑将 $(a,b]$ 拆称有限个互不相交的半开区间的并：
$$
	(a,b]=\sum_{i=1}^{n}(a_{i},b_{i}]
$$
此时我们就有 $a_{i}=b_{i-1}$ 这个关系，我们对其求测度的和：
$$
	\mu((a,b])=\sum_{i=1}^{n}\mu((a_{i},b_{i}])=\sum_{i=1}^{n}[F(b_{i})-F(a_{i})]
$$
化简右侧的式子，消去相同的项，即可得到：
$$
	\mu((a,b])=F(b)-F(a)
$$

接下来证明可数次可加性：
假设可数无穷个半开区间覆盖了目标区间：
$$
	(a, b] \subset \bigcup_{i \ge 1} (a_i, b_i]
$$
此时要证明可数次可加性，即证：
$$
	F(b) - F(a) \le \sum_{i=1}^\infty [F(b_i) - F(a_i)]
$$
此时考虑对这个区间进行放缩，对于左边界，取 $\delta>0$ ，得到一个新的区间 $[a+\delta,b]$ ，使得对于任意的 $\epsilon>0$ 有：
$$
	F(a+\delta)<F(a)+\epsilon
$$
此时考虑右边界，对每一个 $i$ ，取 $\eta_{i}>0$ 得到新的区间 $(a_{i},b_{i}+\eta_{i})$ 让 $\eta_{i}$ 足够小，使得有：
$$F(b_i + \eta_i) < F(b_i) + \epsilon 2^{-i}$$
综上我们就得到了一个区间的包含关系链：
$$
	[a+\delta,b]\subset(a,b]\subset\bigcup_{i \ge 1} (a_i, b_i]\subset\bigcup_{i \ge 1} (a_i, b_i+\eta_{i})
$$
关系链最右侧的这些可数无穷个开区间现在是最左侧的一个闭区间的覆盖，因此必然存在一个有限子覆盖 $J$ 使得：
$$
		[a+\delta,b]\subset\bigcup_{i\in J} (a_i, b_i+\eta_{i})
$$
因为显然有 $(a+\delta ,b)\subset [a+\delta,b]$ ，因此也显然有：
$$
			(a+\delta,b]\subset\bigcup_{i\in J} (a_i, b_i+\eta_{i})
$$
因为半开区间的集合均属于代数，因此根据 [[01 概率空间-Probability Spaces#^lem-b7b2b9 | 有限次可加性]] ，有：
$$
	F(b)-F(a+\delta) \leq \sum_{i\in J}[F(b_{i}+\eta_{i})-F(a_{i})]
$$
因为 $J$ 是一个有限集，其和必然小于可数无穷集的和，因此有：
$$
	F(b)-F(a+\delta) \leq \sum_{i\geq{1}}^{\infty}[F(b_{i}+\eta_{i})-F(a_{i})]
$$
根据我们的放缩关系，可以得到：
$$
	F(b) - F(a) \le \sum_{i=1}^\infty [F(b_i) - F(a_i)] + 2\epsilon
$$
（其中 $\sum_{i=1}^{\infty}\epsilon 2^{-i}=\epsilon$）
因为对于任意的 $\epsilon>0$ 均成立，我们不妨令 $\epsilon \downarrow 0$ ，即有：
$$
	F(b) - F(a) \le \sum_{i=1}^\infty [F(b_i) - F(a_i)]
$$
接下来考虑 $a = -\infty$ 或 $b = \infty$ 的情形。
假设 $(a, b] \subset \bigcup_{i \ge 1} (a_i, b_i]$ 成立，我们在其内部任取一个**有限**子区间 $(A, B] \subset (a, b]$（满足 $-\infty < A < B < \infty$），显然，这个有限区间也一定被相同的区间族覆盖： $$(A, B] \subset \bigcup_{i \ge 1} (a_i, b_i]$$ 既然 $A$ 和 $B$ 是有限的，我们就可以直接使用刚刚证出来的结论： $$F(B) - F(A) \le \sum_{i=1}^\infty [F(b_i) - F(a_i)]$$ 由于这个不等式对**任意**有限的 $(A, B] \subset (a, b]$ 都成立，我们只需令 $A \downarrow a$ 且 $B \uparrow b$，即可得到：
$$F(b) - F(a) \le \sum_{i=1}^\infty [F(b_i) - F(a_i)]$$
综上，可数次可加性成立，因此定理 1.1.3 成立。

## 7.2 在 $R^{d}$ 上的推广条件

上述的Lebesgue-Stieltjes 测度定理是定义在一维空间上的，只需要函数 $F$ 满足单调递增和右连续就可以定义测度。接下来要推广至多维空间，则需考虑在多维空间 $\mathbf{S}$ 上，定义测度 $\mu$ 需要满足什么条件。

不妨将一维条件下的条件迁移过来，即提出下面三个假设：
1. 满足单调性：对于 $x\leq y$ ，满足 $F(x)\leq F(y)$ 。
2. 满足右连续性： $\lim_{y\downarrow x}F(y)=F(x)$ 。
3. 若 $x_{n}\to-\infty$ 则 $F(x_{n})=0$ ，若 $x_{n}\to +\infty$ ，则 $F(x_{n}) = 1$ 。

我们来考察一下条件是否够用，显然是不够的，考虑下面这样一个反例：

定义 $F(x,y)$ ，满足：
$$
	F(x_1, x_2) = \begin{cases}  
1 & \text{若 } x_1, x_2 \ge 1 \\  
2/3 & \text{若 } x_1 \ge 1 \text{ 且 } 0 \le x_2 < 1 \\  
2/3 & \text{若 } x_2 \ge 1 \text{ 且 } 0 \le x_1 < 1 \\  
0 & \text{其他情况}  
\end{cases}
$$
此时它满足单调性，右连续性和边界值要求，我们来计算它的测度，根据容斥原理：
$$
	\mu(A) = F(b_1, b_2) - F(a_1, b_2) - F(b_1, a_2) + F(a_1, a_2)
$$
我们将点 $(1-\epsilon,1-\epsilon)$ ，$(1,1)$ 代入得到其测度 $\mu(\{1,1\})=-\frac{1}{3}<{0}$ ，这是不被允许的。

为了解决这个问题，我们需要引入高维矩形的体积，设 $d$ 维矩形 $A=(a_1, b_1] \times \dots \times (a_d, b_d]$ ，其拥有 $2^{d}$ 个顶点，我们记这些顶点构成的集合为 $V$ ，表示为：
$$
	V = \{a_1, b_1\} \times \dots \times \{a_d, b_d\}
$$
对于 $V$ 中的一个顶点 $v$ ，令
$$
	\mathrm{sgn}(v)=(-1)^{n}
$$
其中 $n$ 是 $v$ 中 $a$ 的个数。
（对于这个函数，我们需要引入高维度下的容斥原理，这里不展开。）

通过引入这个函数我们就能定义 $A$ 的体积 $\Delta_{A}F$ ：
$$
	\Delta_{A}F=\sum_{v\in V}\mathrm{sgn}(v)F(v)
$$
这就是对应高维情形下的测度 $\mu(A)=\Delta_{A}F$ 。

由测度的非负性，要想在高维情形下运用测度，则必须要进一步地满足：
4. $\Delta_{A}F\geq0$ 对于任意 $A$ 恒成立。

这便是推广的第四个条件，我们下面统称这四个条件为“推广条件”。

## 7.3 测度定理在 $\mathbf{R}^{d}$ 上的推广

我们在 7.2 讨论了测度定理要在 $\mathbf{R}^{d}$ 上推广需要满足的条件，接下来我们就可以在高维度下提出 Lebesgue-Stieltjes 测度定理了。

>[!theorem] 定理 1.1.4 高维 Lebesgue-Stieltjes 测度定理
>如果一个函数 $F:\mathbf{R}^{d}\to[0,1]$ 满足推广条件，则在波莱尔 $\sigma$-域（即 $(\mathbf{R}^{d},\mathcal{R}^{d})$）上，存在唯一的一个概率测度 $\mu$ 使得任何一个 $d$ 维有限矩形的测度都等于：
>
>$$
>	\mu(A)=\Delta_{A}F
>$$

## 7.4 高维度下的勒贝格测度 - Lebesgue Measure on $\mathbf{R}^{d}$ 

如果 $F(x)$ 可以被分解为各个坐标分量函数的乘积，即：
$$
	F(x)=\prod_{i=1}^{d}F_{i}(x_{i})
$$
则有：
$$
	\Delta_{A}F=\prod_{i=1}^{d}(F_{i}(b_{i})-F_{i}(a_{i}))
$$
这个可以将每个分量的测度展开因式分解来求证。

当每个坐标分量的分布函数都是函数 $F_{i}(x)=x$ 时，此时 $d$ 维空间矩形 $A$ 的测度就是：
$$
	\mu(A)=\prod_{i=1}^{d}(b_{i}-a_{i})
$$
这个测度即 $\mathbf{R}^{d}$ 上的勒贝格测度。

在三维空间下，这就是立方体的体积（长宽高相乘）。

## 7.5 测度性质的高维推广

这部分我们将从一维出发将测度的有限可加性和可数次可加性推广到 $\mathbf{R}^{d}$ 上。

在这之前，我们需要引入一个新的概念。

>[!definition] 定义 1.1.9 正则剖分
>定义 $A=+_{k}B_{k}$ 是 $D$ 维矩形 $A$ 的一个正则剖分当且仅当对于任意第 $i$ 维度上，在区间内插入分割点 $a_{i,x}$ 满足：
>$$
>	a_{i}=a_{i,0}<a_{i,1}<\dots<a_{i,n_{i}}=b_{i}
>$$
>将 $A$ 划分 $k$ 个小矩形 $B_{1},B_{2}\dots B_{k}$ ，使得对于任意一个矩形 $B_{j}$ 都有：
>
>$$B_{\vec{j}} = (\alpha_{1,j_1-1}, \alpha_{1,j_1}] \times (\alpha_{2,j_2-1}, \alpha_{2,j_2}] \times \dots \times (\alpha_{d,j_d-1}, \alpha_{d,j_d}]$$
> 其中每个指标 $j_i$ 满足 $1 \le j_i \le n_i$。

直观上而言，正则剖分是形如下图的剖分方式：

![[Pasted image 20260724170935.png | 200]]

我们接下来对有限可加性进行讨论：

对于正则剖分而言，显然存在 $\mu(A)=\sum_{i}\mu(B_{i})$ ，我们可以用类似于一维状态下的情形来证明，本质上也是使用相同部分消去求和的思想。
不过并不是所有的剖分都是正则剖分，此时我们只需要把分割线补齐就能构造一个正则剖分，使得任意有限剖分下的有限可加性成立。

然后是可数次可加性的证明：

在一维上，我们使用圆括号和方括号来表示开区间和闭区间，在高维上，我们用于分别表示开矩形和闭矩形，同时为了方便证明，我们定义全 1 向量：
$$
	\bar{1}=(1,1,\dots,1)
$$

考虑区间 $(a,b]$ ，我们可以在高维状态下使用全 1 向量对其进行放缩，即取一个 $\delta>0$ ，得到 $[a+\delta \bar{1},b]$ 。

假设可数无穷个半开区间覆盖了目标区间，我们不妨扩张覆盖矩形，对于每一个覆盖矩形，取 $\eta_{i}>0$ ，得到 $(a_{i},b_{i}+\eta_{i} \bar{1})$ 。

最终我们能得到：
$$\mu((a, b]) < \mu((a + \delta \bar{1}, b]) + \epsilon \le \mu([a + \delta \bar{1}, b]) + \epsilon$$

接下来的步骤和一维时的相同，取一个有限子覆盖 $J$ ，然后对这个有限子覆盖使用有限次可加性，进一步地推广到可数无限情形下即可：
$$\mu([a + \delta \bar{1}, b]) \le \sum_{j=1}^J \mu((\alpha^j, \beta^j]) \le \sum_{i=1}^\infty \mu((a^i, b^i + \eta_i \bar{1}])$$
对右侧式子里的 $\epsilon 2^{-i}$ 提出来求无穷级数得到：
$$\sum_{i=1}^\infty \mu((a^i, b^i + \eta_i \bar{1}]) \le \sum_{i=1}^\infty \mu((a^i, b^i]) + \epsilon$$
即：
$$\mu((a, b]) \le \mu([a + \delta \bar{1}, b]) + \epsilon \le \sum_{i=1}^\infty \mu((a^i, b^i]) + 2\epsilon$$
由 $\epsilon$ 的任意性，令 $\epsilon \downarrow 0$，可数次可加性即得证。 $a = -\infty$ 或 $b = \infty$ 的情形也是和一维情形同理。
