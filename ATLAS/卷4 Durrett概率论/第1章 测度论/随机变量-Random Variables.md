---
tags:
  - 概率论
  - 测度论
---

# 1. 可测映射 - Measurable Map

上一节（[[分布-Distributions|§1.2]]）我们把随机变量定义成「满足可测条件的函数 $X:\Omega\to\mathbf{R}$」——即对任意 Borel 集 $B$，都有 $X^{-1}(B)\in\mathcal{F}$。这一节（Durrett §1.3）沿着这条主线做三件事：

1. **推广**：把「可测」从实数轴推广到任意可测空间之间的映射，得到可测映射与随机向量；
2. **给判定工具**：证明判断可测性只需在一个「生成集族」上验证，不必逐集检查；
3. **建立封闭性**：随机变量经复合、加乘、取上下确界、取极限后仍是随机变量——这是后续整个概率论的运算地基。

## 1.1 可测映射与随机变量

§1.2 的定义依赖「实数轴上的 Borel 集」这个具体对象，但仔细看就会发现，可测性的本质并不在于 $\mathbf{R}$，而在于「原像保持可测结构」这个抽象关系——只要给出两个可测空间 $(\Omega,\mathcal{F})$ 和 $(S,\mathcal{S})$，就能定义同样的概念。Durrett 据此把它推广为一般的可测映射。

>[!definition] 定义 1.3.1 - 可测映射（Measurable Map）
>设 $(\Omega,\mathcal{F})$ 和 $(S,\mathcal{S})$ 是两个可测空间。称函数 $X:\Omega\to S$ 是从 $(\Omega,\mathcal{F})$ 到 $(S,\mathcal{S})$ 的**可测映射**，如果：
>
>$$
>	X^{-1}(B)\equiv\{\omega:X(\omega)\in B\}\in\mathcal{F},\quad \forall B\in\mathcal{S}
>$$
>
> ^def-5e8a2c

**直觉**：把 $X$ 想成一台「观测仪器」，它把复杂的样本 $\omega$ 压缩成 $S$ 中的一个值 $X(\omega)$。可测性说的是这台仪器「信息友好」——$S$ 上任一可测集 $B$，顺着仪器反推回 $\Omega$ 得到的原像 $\{\omega:X(\omega)\in B\}$ 仍是一个合法事件（$\in\mathcal{F}$）。反过来，若某个 $B$ 的原像不在 $\mathcal{F}$ 里，那么「$X$ 落在 $B$ 里」这件事就无法谈概率——仪器产生了一个测不了的盲区，这样的仪器在概率论里没法用。

当 $(S,\mathcal{S})=(\mathbf{R}^d,\mathcal{R}^d)$ 且 $d>1$ 时，$X$ 称为**随机向量**（random vector）；当 $d=1$ 时，$X$ 就是普通的**随机变量**（random variable）。

## 1.2 可测性的判定定理

**动机**：定义要求「对所有 $B\in\mathcal{S}$ 验证原像可测」，但 $\mathcal{S}$ 往往巨大到无法逐一检查（比如 Borel $\sigma$-域）。下面这个定理给出一个极其省力的判定法：**只需在生成 $\mathcal{S}$ 的一个小集族上验证即可**。

>[!theorem] 定理 1.3.1 - 可测性的生成类判定
>设 $\mathcal{A}$ 生成 $\mathcal{S}$（即 $\mathcal{S}=\sigma(\mathcal{A})$）。若对所有 $A\in\mathcal{A}$ 都有 $\{\omega:X(\omega)\in A\}\in\mathcal{F}$，则 $X$ 是可测映射。
>
> ^thm-3f7d1a

**证明的钥匙——「好性质会传染」**：原像运算有两条关键的交换律——它与可数并、补运算都交换：

$$
	\{X\in\bigcup_i B_i\}=\bigcup_i\{X\in B_i\},\qquad \{X\in B^c\}=\{X\in B\}^c
$$

这意味着：只要知道某些 $B$ 的原像可测，那么它们的并、补的原像也自动可测。「原像可测」这个好性质，在并、补运算下自动保持。

于是我们收集「所有好集合」成一个族

$$
	\mathcal{B}=\{B:\{X\in B\}\in\mathcal{F}\}
$$

并证明 $\mathcal{B}$ 是 $\sigma$-域（记 $\{X\in B\}$ 为 $\{\omega:X(\omega)\in B\}$ 的简写）：

- **可数并封闭**：$\{X\in\bigcup_i B_i\}=\bigcup_i\{X\in B_i\}$。若每个 $\{X\in B_i\}\in\mathcal{F}$，由 $\mathcal{F}$ 是 $\sigma$-域知它们的并也在 $\mathcal{F}$ 中，故 $\bigcup_i B_i\in\mathcal{B}$。
- **补封闭**：$\{X\in B^c\}=\{X\in B\}^c$，同理 $\{X\in B\}^c\in\mathcal{F}$，故 $B^c\in\mathcal{B}$。

由条件知 $\mathcal{B}\supset\mathcal{A}$，而 $\mathcal{S}=\sigma(\mathcal{A})$ 是包含 $\mathcal{A}$ 的最小 $\sigma$-域，所以 $\mathcal{B}\supset\mathcal{S}$。即对所有 $B\in\mathcal{S}$ 都有 $\{X\in B\}\in\mathcal{F}$，$X$ 可测得证。

**这个论证法值得记牢**：把「满足某性质的集合」收集成一个族，再证明这个族是 $\sigma$-域（或单调类），从而把性质从生成元「传播」到全体——这是测度论里反复出现的套路，单调类定理、唯一性定理都是它的亲戚。

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

**最常用的结论**：判断 $X$ 是不是随机变量，几乎总是验证「对所有 $x$，$\{X\leq x\}\in\mathcal{F}$」这一条就够了（例 1.3.2），不必逐个检查 Borel 集。

## 1.3 $\sigma(X)$ — 由 $X$ 生成的 $\sigma$-域

上面证明中出现了一个副产品：原像族 $\{\{X\in B\}:B\in\mathcal{S}\}$ 本身也是一个 $\sigma$-域。它是让 $X$ 可测的**最小** $\sigma$-域，值得单独命名。

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

**直觉**：$\sigma(X)$ 收集的是「仅凭观察 $X$ 的取值就能判断是否发生」的所有事件。设想你只能看到数值 $X(\omega)$、却看不到 $\omega$ 本身——那么你能回答「事件 $A$ 是否发生」当且仅当 $A$ 能写成 $\{X\in B\}$ 的形式，即 $A\in\sigma(X)$。$X$ 区分样本的能力越强（携带的信息越多），$\sigma(X)$ 就越大。

# 2. 随机变量的运算封闭性

接下来回答一个贯穿全书的问题：**对随机变量做运算，结果还是随机变量吗？** 答案是肯定的，而且封闭范围极广。下面四个结论不是四条并列的孤立定理，而是一条清晰的逻辑链：

| 定理 | 内容 | 地位 |
|:---|:---|:---|
| [[#^thm-b2d7e4 | 定理 1.3.4]] | 可测映射的复合仍可测 | **总纲** |
| [[#^thm-c3e8f5 | 定理 1.3.5]] | 多元可测函数的复合仍可测 | 1.3.4 的多元推广 |
| [[#^thm-d4f9a6 | 定理 1.3.6]] | 和、积仍是随机变量 | 1.3.5 的特例 |
| [[#^thm-e5a0b7 | 定理 1.3.7]] | inf/sup/liminf/limsup 可测 | 独立，用判定定理直接证 |

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

**直觉**：复合就是「两台仪器串联」——第一台的输出直接喂给第二台。既然每一台都不产生信息盲区，串联之后自然也不产生。

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

**直觉**：套复合定理之前，得先证明 $(X_1,\dots,X_n)$ 本身是个随机向量。例 1.3.3 告诉我们只需验证「矩形」的原像可测；而矩形原像恰好是各分量原像的**交**，各分量可测，交也可测（$\mathcal{F}$ 对有限交封闭）。

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

**直觉与意义**：$\inf$、$\sup$、$\liminf$、$\limsup$ 都是「可数多次比较」的操作，判定定理（例 1.3.2）告诉我们只需验证某个不等式集合可测，而这些集合恰好能写成可数并/交。这个定理的深层意义在于：**随机变量序列的极限运算不破坏可测性**——这正是下一节定义「几乎必然收敛」的地基。

# 3. 几乎必然收敛 - Almost Sure Convergence

**动机**：定理 1.3.7 保证了极限运算不破坏可测性，于是「$X_n$ 逐点收敛」这件事本身能当作一个可测事件来谈概率。但「极限存在」是一个无穷过程，怎么把它写成一个可判定的等式？答案是借助 $\limsup$ 与 $\liminf$：两者相等当且仅当极限存在。

注意到：

$$
	\{\omega:\lim_{n\to\infty}X_n\ \text{存在}\} = \{\omega:\limsup_{n\to\infty}X_n - \liminf_{n\to\infty}X_n = 0\}
$$

由于 $\limsup$ 和 $\liminf$ 都是随机变量（[[#^thm-e5a0b7 | 定理 1.3.7]]），它们的差也是，所以极限存在的集合是一个可测集。记这个集合为 $\Omega_0$。

（严格地说，这里的「极限存在」允许 $\limsup=\liminf=\pm\infty$ 的广义情形，此时 $\limsup-\liminf$ 的差不再有定义；§4 引入扩展实值随机变量，正是为了把这一层含义补严密。）

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

**动机**：上一节用 $X_\infty=\limsup_n X_n$ 让极限处处有定义，但 $\limsup$ 可能取到 $\pm\infty$——而普通随机变量只许取实数值。为了名正言顺地处理取 $\pm\infty$ 的「随机变量」，我们把值域扩到 $[-\infty,\infty]$。

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
