---
tags:
  - 概率论
  - 测度论
---

# 1. 积分 - Integration

上一节（[[随机变量-Random Variables|§1.3]]）我们把「随机变量」定义为满足可测条件的函数，并证明了它们的运算封闭性——加、乘、取上下确界、取极限都不会破坏可测性。这一节（Durrett §1.4）要回答概率论中的第二个根本问题：**如何对一个可测函数求积分？** 也就是如何定义 $\int f\,\mathrm{d}\mu$。

设 $\mu$ 是 $(\Omega,\mathcal{F})$ 上的一个 [[概率空间-Probability Spaces#^def-ea2971|测度]]。我们最关心的是 $\mu$ 为概率测度的情形，但积分对一般的 $\sigma$-有限测度同样能定义，而且并不更费力，所以直接在一般情形下展开。

直接对任意可测函数下定义是困难的，Durrett 的做法是「由简入繁」分四步走，每一步只比上一步多放松一点限制：

1. **简单函数**：只取有限个值，且每个非零值都落在有限测度的集合上；
2. **有界函数**：在某有限测度集合 $E$ 外取 $0$、且在 $E$ 上有界；
3. **非负函数**：$f\geq 0$，允许无界、允许处处非零；
4. **一般函数**：把 $f$ 拆成「正部」与「负部」之差。

每一步都要重新证明积分的三条基本性质（非负性、数乘、加法），从而保证最终得到的积分是「好」的。这个四步构造法本身也是证明积分公式的通用套路，后文（定理 1.6.9、定理 1.7.2）会反复借用。

## 0. 符号速查

这一节的记号比前面几节密集，先把新出现的符号集中列一张表；读到不认识的记号随时回来查即可：

| 符号 | 读法 | 含义 |
|:---|:---|:---|
| $1_A(x)$ | 「$A$ 的示性函数」 | 若 $x\in A$ 则取 $1$，否则取 $0$——像一个「$A$ 内开、$A$ 外关」的开关 |
| $E^c$ | 「$E$ 的补集」 | $\Omega$ 中所有不在 $E$ 里的点 |
| $\sup$ / $\inf$ | 「上确界 / 下确界」 | 一堆数里的「最小上界 / 最大下界」 |
| $a\vee b$ | 「$a$ 与 $b$ 取大」 | $\max(a,b)$ |
| $a\wedge b$ | 「$a$ 与 $b$ 取小」 | $\min(a,b)$ |
| $f\wedge n$ | 「$f$ 在 $n$ 处截断」 | $\min(f,n)$，把 $f$ 超过 $n$ 的部分削平到 $n$ |
| $E_n\uparrow\Omega$ | 「$E_n$ 递增趋于 $\Omega$」 | $E_1\subseteq E_2\subseteq\cdots$ 且并集为 $\Omega$ |

其中 $1_A$、$\vee$、$\wedge$ 三个记号几乎贯穿全书，务必先记住它们。

## 1.1 简单函数

第一步只处理结构最简单的函数。简单函数就是「阶梯函数」：把样本空间切成有限块互不相交的集合，每一块上函数取一个常数。

>[!definition] 定义 1.4.1 - 简单函数（Simple Function）
>称 $\phi$ 是**简单函数**，如果它可以写成
>
>$$
>	\phi(\omega)=\sum_{i=1}^{n}a_i\,1_{A_i}(\omega)
>$$
>
>其中 $A_i$ 是互不相交的集合，且每个 $\mu(A_i)<\infty$。此时定义 $\phi$ 的积分为
>
>$$
>	\int\phi\,\mathrm{d}\mu=\sum_{i=1}^{n}a_i\,\mu(A_i)
>$$
>
> ^def-5b7c9d

**直觉**：积分就是「每块的值 $a_i$ 乘上这块的测度 $\mu(A_i)$，再求和」——这正是离散情形下「取值 × 概率求和」的连续类比。若 $A_i$ 的测度无限，那么「常数 $a_i$ 乘上一个无限大的区域」会出现 $\infty\cdot a_i$ 的麻烦，所以要求每块支撑 $\mu(A_i)<\infty$。

这里有个技术细节：$a_i$ 没有被要求两两不同，所以同一个简单函数有多种表示（比如 $1_A$ 也可以写成 $1_A+1_A-1_A$）。好在可以验证这些不同表示给出的积分值相同，所以上面的定义不会自相矛盾。

在陈述性质之前，先约定一个贯穿全书的记号——「几乎处处」：

>[!definition] 定义 1.4.2 - 几乎处处（Almost Everywhere）
>称 $\phi\geq\psi$ $\mu$-a.e.（几乎处处成立），如果
>
>$$
>	\mu\big(\{\omega:\phi(\omega)<\psi(\omega)\}\big)=0
>$$
>
>即「不等号不成立」的那些点构成的集合测度为 $0$。当所指的测度 $\mu$ 不会引起歧义时，简写为 $\phi\geq\psi$ a.e.。
>
> ^def-6c8d0e

**直觉**：a.e. 说的是「可能有个别坏点不满足，但这些坏点加起来测度为 0，可以忽略」。在概率语言里，测度 $0$ 对应「概率为 $0$ 的事件」，所以「a.e. 成立」就是「以概率 1 成立」的测度论版本——这与 [[随机变量-Random Variables#^def-2f7b3d|几乎必然收敛]] 里的「a.s.」是同一个精神。

现在证明简单函数积分的三条基本性质：

>[!lemma] 引理 1.4.1 - 简单函数积分的线性
>设 $\phi,\psi$ 是简单函数，则：
>1. 若 $\phi\geq 0$ a.e.，则 $\int\phi\,\mathrm{d}\mu\geq 0$；
>2. 对任意 $a\in\mathbf{R}$，$\int a\phi\,\mathrm{d}\mu=a\int\phi\,\mathrm{d}\mu$；
>3. $\int(\phi+\psi)\,\mathrm{d}\mu=\int\phi\,\mathrm{d}\mu+\int\psi\,\mathrm{d}\mu$。
>
> ^lem-7d9e1f

前两条几乎就是定义的字面推论，关键在于第三条（加法），我们拆开来看。

设 $\phi=\sum_{i=1}^{m}a_i\,1_{A_i}$，$\psi=\sum_{j=1}^{n}b_j\,1_{B_j}$。

为了让两个函数的「分块」对齐，我们补上两个零块：令 $A_0=\bigcup_j B_j-\bigcup_i A_i$、$B_0=\bigcup_i A_i-\bigcup_j B_j$，并令 $a_0=b_0=0$。这样 $\phi$ 与 $\psi$ 就「共享同一套划分」了，于是

$$
	\phi+\psi=\sum_{i=0}^{m}\sum_{j=0}^{n}(a_i+b_j)\,1_{A_i\cap B_j}
$$

而诸 $A_i\cap B_j$ 两两不相交，所以

$$
	\int(\phi+\psi)\,\mathrm{d}\mu=\sum_{i=0}^{m}\sum_{j=0}^{n}(a_i+b_j)\,\mu(A_i\cap B_j)
$$

把求和拆成两项，并利用 $A_i=\bigcup_j(A_i\cap B_j)$、$B_j=\bigcup_i(A_i\cap B_j)$（这里 $\bigcup$ 表示不相交并）分别对 $j$ 和 $i$ 求和，即得 $\int\phi\,\mathrm{d}\mu+\int\psi\,\mathrm{d}\mu$。

**这个「补零对齐」的技巧很关键**：两个函数的分块不一样，就先通过补零把它们拉到同一套分块上再做加法。后面每一步推广时，这个加法证明都会原样重演一遍。

由这三条性质，立刻推出另外三条常用性质——而且它们的证明与「具体是哪种函数」无关，所以一次性证完，后三步直接套用：

>[!lemma] 引理 1.4.2 - 由线性推出的三个性质
>若 (1)(3) 两条性质成立，则：
>4. 若 $\phi\leq\psi$ a.e.，则 $\int\phi\,\mathrm{d}\mu\leq\int\psi\,\mathrm{d}\mu$；
>5. 若 $\phi=\psi$ a.e.，则 $\int\phi\,\mathrm{d}\mu=\int\psi\,\mathrm{d}\mu$；
>6. 若 (2) 对 $a=-1$ 也成立，则 $\left|\int\phi\,\mathrm{d}\mu\right|\leq\int|\phi|\,\mathrm{d}\mu$。
>
> ^lem-8e0f2a

证明 (4)：由 (3)，$\int\psi\,\mathrm{d}\mu=\int\phi\,\mathrm{d}\mu+\int(\psi-\phi)\,\mathrm{d}\mu$，而 $\psi-\phi\geq 0$ a.e.，由 (1) 知第二项 $\geq 0$，故 $\int\phi\leq\int\psi$。

证明 (5)：$\phi=\psi$ a.e. 意味着 $\phi\leq\psi$ a.e. 且 $\psi\leq\phi$ a.e.，用两次 (4) 即得两边相等。

证明 (6)：$\phi\leq|\phi|$，由 (4) 得 $\int\phi\leq\int|\phi|$；又 $-\phi\leq|\phi|$，由 (4) 和 (2)（取 $a=-1$）得 $-\int\phi\leq\int|\phi|$。而 $|y|=\max(y,-y)$，故 $\left|\int\phi\right|\leq\int|\phi|$。

## 1.2 有界函数

第二步把简单函数放宽到「有界函数」，但暂时只处理「在一个有限测度集合 $E$ 外取 $0$」的 $f$。函数「不为零的那些点」构成的集合叫它的**支撑**（support）；这里要求支撑落在测度有限的集合 $E$ 里，所以叫「紧支撑」。这个条件保证不会出现 $\infty$ 的麻烦——因为 $f$ 只在「有限大小」的区域里活动，乘以任何有界系数都不会溢出。

**定义的想法**：我们希望 $\int f$ 夹在「所有不超过 $f$ 的简单函数的积分」和「所有不低于 $f$ 的简单函数的积分」之间，于是自然想到用上确界与下确界来夹：

>[!definition] 定义 1.4.3 - 有界函数的积分
>设 $E$ 满足 $\mu(E)<\infty$，$f$ 在 $E^c$ 上取 $0$ 且有界。定义
>
>$$
>	\int f\,\mathrm{d}\mu=\sup_{\phi\leq f}\int\phi\,\mathrm{d}\mu=\inf_{\psi\geq f}\int\psi\,\mathrm{d}\mu
>$$
>
>其中 $\phi,\psi$ 都取「在 $E^c$ 上取 $0$」的简单函数。
>
> ^def-9f102b

这里必须证明「上确界等于下确界」，定义才是良定的。

所谓「良定」（well-defined），说的是：如果一个定义依赖某种「选择」或「表示方式」，就必须先证明这个选择无关紧要，否则同一个对象会被算出两个不同的值，定义就自相矛盾了。这里 $\int f$ 同时用上确界和下确界两种写法给出，所以得先证明它们给出同一个数。记 $\sup_{\phi\leq f}\int\phi=\alpha$、$\inf_{\psi\geq f}\int\psi=\beta$。

**先证 $\alpha\leq\beta$**：任取 $\phi\leq f\leq\psi$，由 [[#^lem-8e0f2a|引理 1.4.2]] 的 (4) 得 $\int\phi\leq\int\psi$，两边分别取上确界和下确界，即 $\alpha\leq\beta$。

**再证 $\alpha\geq\beta$**：设 $|f|\leq M$，把值域 $[-M,M]$ 等分成 $2n$ 段，构造一对「逼近 $f$」的简单函数：

$$
	E_k=\Big\{x\in E:\frac{kM}{n}\geq f(x)>\frac{(k-1)M}{n}\Big\},\qquad -n\leq k\leq n
$$

$$
	\psi_n=\sum_{k=-n}^{n}\frac{kM}{n}\,1_{E_k},\qquad \phi_n=\sum_{k=-n}^{n}\frac{(k-1)M}{n}\,1_{E_k}
$$

**直觉**：$\psi_n$ 和 $\phi_n$ 就是把 $f$ 的值域切成宽度 $\frac{M}{n}$ 的小格，$\psi_n$ 取每格的上端、$\phi_n$ 取每格的下端，于是 $\phi_n\leq f\leq\psi_n$，且两者的差是个常数：$\psi_n-\phi_n=\frac{M}{n}1_E$。因此

$$
	\int(\psi_n-\phi_n)\,\mathrm{d}\mu=\frac{M}{n}\mu(E)
$$

这个差距当 $n\to\infty$ 时趋于 $0$。再由 $\phi_n\leq f\leq\psi_n$ 和 [[#^lem-7d9e1f|引理 1.4.1]] 的 (3)：

$$
	\alpha=\sup_{\phi\leq f}\int\phi\,\mathrm{d}\mu\geq\int\phi_n\,\mathrm{d}\mu=-\frac{M}{n}\mu(E)+\int\psi_n\,\mathrm{d}\mu\geq-\frac{M}{n}\mu(E)+\beta
$$

令 $n\to\infty$ 即得 $\alpha\geq\beta$。综合两个方向，$\alpha=\beta$，定义良定。

>[!lemma] 引理 1.4.3 - 有界函数积分的六条性质
>设 $E$ 满足 $\mu(E)<\infty$，$f,g$ 都在 $E^c$ 上取 $0$ 且有界，则：
>1. 若 $f\geq 0$ a.e.，则 $\int f\,\mathrm{d}\mu\geq 0$；
>2. 对任意 $a\in\mathbf{R}$，$\int af\,\mathrm{d}\mu=a\int f\,\mathrm{d}\mu$；
>3. $\int(f+g)\,\mathrm{d}\mu=\int f\,\mathrm{d}\mu+\int g\,\mathrm{d}\mu$；
>4. 若 $g\leq f$ a.e.，则 $\int g\,\mathrm{d}\mu\leq\int f\,\mathrm{d}\mu$；
>5. 若 $g=f$ a.e.，则 $\int g\,\mathrm{d}\mu=\int f\,\mathrm{d}\mu$；
>6. $\left|\int f\,\mathrm{d}\mu\right|\leq\int|f|\,\mathrm{d}\mu$。
>
> ^lem-a1b2c3

(1) 显然（取 $\phi\equiv 0$）。

(2) 要分 $a>0$ 与 $a<0$ 讨论：$a>0$ 时「$a\phi\leq af\iff\phi\leq f$」，上确界可提出因子 $a$；$a<0$ 时「$a\phi\leq af\iff\phi\geq f$」，上确界变成了下确界，仍能提出 $a$。

(3) 用「$\psi_1\geq f,\ \psi_2\geq g\Rightarrow\psi_1+\psi_2\geq f+g$」先证一个方向，再把结论用于 $-f,-g$ 并配合 (2) 反推另一个方向。

(4)-(6) 由 (1)-(3) 套用 [[#^lem-8e0f2a|引理 1.4.2]] 即得。

## 1.3 非负函数

第三步去掉「有界」和「紧支撑」两个限制，只要求 $f\geq 0$。此时的积分仍用「从下方逼近」来定义：

>[!definition] 定义 1.4.4 - 非负函数的积分
>若 $f\geq 0$，定义
>
>$$
>	\int f\,\mathrm{d}\mu=\sup\Big\{\int h\,\mathrm{d}\mu:\ 0\leq h\leq f,\ h\ \text{有界},\ \mu\big(\{x:h(x)>0\}\big)<\infty\Big\}
>$$
>
> ^def-b2c3d4

**直觉**：想象把 $f$ 的图形从下面一点一点「填满」——所有不超过 $f$、且只在有限区域上非零的有界函数 $h$，它们的积分取上确界，就是 $f$ 的积分。这个定义的好处是良定性一目了然（上确界总是存在），代价是不好直接算。下面这个引理就专门帮我们把「上确界」变成「能算的极限」。

>[!lemma] 引理 1.4.4 - 截断逼近
>设 $E_n\uparrow\Omega$ 且 $\mu(E_n)<\infty$，令 $a\wedge b=\min(a,b)$，则当 $n\to\infty$ 时
>
>$$
>	\int_{E_n}f\wedge n\,\mathrm{d}\mu\uparrow\int f\,\mathrm{d}\mu
>$$
>
> ^lem-c3d4e5

**直觉**：$f\wedge n$ 是「把 $f$ 超过 $n$ 的部分削平」，$1_{E_n}$ 是「把 $E_n$ 外的部分砍掉」，两者配合就把无界、无紧支撑的 $f$ 变成了一列「有界且在有限区域上非零」的函数。引理说的是：这列函数的积分单调上升，极限恰好就是 $\int f$。（这里正是用到了 $\mu$ 的 $\sigma$-有限性——所谓 $\sigma$-有限，就是整个空间 $\Omega$ 能拆成可数多个测度有限的碎片，于是总能找到一列 $E_n\uparrow\Omega$ 且每块 $\mu(E_n)<\infty$。概率测度自动满足这一点，因为 $\Omega$ 本身就有测度 $1$，一块就够了。）

证明：左边随 $n$ 递增是显然的（[[#^lem-a1b2c3|引理 1.4.3]] 的 (4)），且每一项都 $\leq$ 右边的积分（因为 $h=(f\wedge n)1_{E_n}$ 是定义里的合法候选）。反过来，任取定义里的一个候选 $h$（$0\leq h\leq f$、$h\leq M$、$\mu(\{x:h(x)>0\})<\infty$），当 $n\geq M$ 时：

$$
	\int_{E_n}f\wedge n\,\mathrm{d}\mu\geq\int_{E_n}h\,\mathrm{d}\mu=\int h\,\mathrm{d}\mu-\int_{E_n^c}h\,\mathrm{d}\mu
$$

而 $0\leq\int_{E_n^c}h\,\mathrm{d}\mu\leq M\,\mu\big(E_n^c\cap\{x:h(x)>0\}\big)\to 0$（因为 $E_n\uparrow\Omega$ 意味着 $E_n^c\downarrow\emptyset$）。故 $\liminf_{n\to\infty}\int_{E_n}f\wedge n\,\mathrm{d}\mu\geq\int h\,\mathrm{d}\mu$。由于 $h$ 是定义里的任意候选，取上确界即得极限 $\geq\int f$。与前述的 $\leq$ 合并，两边相等。

>[!lemma] 引理 1.4.5 - 非负函数积分的性质
>设 $f,g\geq 0$，则：
>1. $\int f\,\mathrm{d}\mu\geq 0$；
>2. 若 $a>0$，则 $\int af\,\mathrm{d}\mu=a\int f\,\mathrm{d}\mu$；
>3. $\int(f+g)\,\mathrm{d}\mu=\int f\,\mathrm{d}\mu+\int g\,\mathrm{d}\mu$；
>4. 若 $0\leq g\leq f$ a.e.，则 $\int g\,\mathrm{d}\mu\leq\int f\,\mathrm{d}\mu$；
>5. 若 $0\leq g=f$ a.e.，则 $\int g\,\mathrm{d}\mu=\int f\,\mathrm{d}\mu$。
>
>（这里省略了 (6)，因为 $f\geq 0$ 时 $\left|\int f\right|=\int f$，它退化为显然的事实。）
>
> ^lem-d4e5f6

(1)(2) 显然。关键是 (3)（加法）：用「$f\geq h,\ g\geq k\Rightarrow f+g\geq h+k$」取上确界，先得 $\int(f+g)\geq\int f+\int g$；反方向利用 $(a+b)\wedge n\leq(a\wedge n)+(b\wedge n)$ 以及 [[#^lem-a1b2c3|引理 1.4.3]]、[[#^lem-c3d4e5|引理 1.4.4]]：

$$
	\int_{E_n}(f+g)\wedge n\,\mathrm{d}\mu\leq\int_{E_n}f\wedge n\,\mathrm{d}\mu+\int_{E_n}g\wedge n\,\mathrm{d}\mu
$$

令 $n\to\infty$ 即得 $\int(f+g)\leq\int f+\int g$。(4)(5) 由 (1)(3) 套用 [[#^lem-8e0f2a|引理 1.4.2]]。

# 2. 一般函数 - General Functions

最后一步处理既可能取正、也可能取负的一般可测函数。核心思想是老办法——**把 $f$ 拆成「正的部分」和「负的部分」**，分别积分再相减。

## 2.1 正部与负部

>[!definition] 定义 1.4.5 - 正部与负部
>对函数 $f$，定义其**正部**与**负部**为
>
>$$
>	f^{+}(x)=f(x)\vee 0,\qquad f^{-}(x)=(-f(x))\vee 0
>$$
>
>其中 $a\vee b=\max(a,b)$。直观地说，$f^{+}$ 是「只保留 $f$ 的正值、把负值全部抹成 $0$」，$f^{-}$ 是「把 $f$ 负的部分翻成正的、正的部分抹成 $0$」——两者都是非负函数。显然 $f=f^{+}-f^{-}$（正的部分减去负的部分），$|f|=f^{+}+f^{-}$（正负两部分的绝对值之和），且 $f^{+},f^{-}\geq 0$。
>
> ^def-e5f6a7

>[!definition] 定义 1.4.6 - 可积（Integrable）与一般函数的积分
>称 $f$ 是**可积**的，如果 $\int|f|\,\mathrm{d}\mu<\infty$。此时定义 $f$ 的积分为
>
>$$
>	\int f\,\mathrm{d}\mu=\int f^{+}\,\mathrm{d}\mu-\int f^{-}\,\mathrm{d}\mu
>$$
>
> ^def-f6a7b8

**为什么要求 $\int|f|<\infty$？** 因为右端是「$\infty-\infty$」型的差，只有当两个被减数都有限时差才有意义。而 $f^{+},f^{-}\leq|f|$，由 [[#^lem-d4e5f6|引理 1.4.5]] 的 (4)，$\int|f|<\infty$ 恰好保证 $\int f^{+}$、$\int f^{-}$ 都有限，于是 $\int f^{+}-\int f^{-}$ 良定。

一个自然的顾虑是：$f$ 拆成非负函数之差的方式有很多（$f=f_1-f_2$ 并不唯一），换一种拆法会不会得到不同的积分值？下面这个引理说：不会。

>[!lemma] 引理 1.4.6 - 分解的无关性
>若 $f=f_1-f_2$，其中 $f_1,f_2\geq 0$ 且 $\int f_i\,\mathrm{d}\mu<\infty$，则
>
>$$
>	\int f\,\mathrm{d}\mu=\int f_1\,\mathrm{d}\mu-\int f_2\,\mathrm{d}\mu
>$$
>
> ^lem-a7b8c9

证明：由 $f=f_1-f_2$ 和 $f=f^{+}-f^{-}$，两边移项得 $f_1+f^{-}=f_2+f^{+}$。四个函数都非负，由 [[#^lem-d4e5f6|引理 1.4.5]] 的 (3)：

$$
	\int f_1\,\mathrm{d}\mu+\int f^{-}\,\mathrm{d}\mu=\int(f_1+f^{-})\,\mathrm{d}\mu=\int(f_2+f^{+})\,\mathrm{d}\mu=\int f_2\,\mathrm{d}\mu+\int f^{+}\,\mathrm{d}\mu
$$

移项即得 $\int f_1-\int f_2=\int f^{+}-\int f^{-}=\int f$。得证。

## 2.2 可积函数的基本性质

最后把这六条性质对一般可积函数完整地证一遍，作为四步构造的收官：

>[!theorem] 定理 1.4.7 - 积分的六条基本性质
>设 $f,g$ 可积，则：
>1. 若 $f\geq 0$ a.e.，则 $\int f\,\mathrm{d}\mu\geq 0$；
>2. 对任意 $a\in\mathbf{R}$，$\int af\,\mathrm{d}\mu=a\int f\,\mathrm{d}\mu$；
>3. $\int(f+g)\,\mathrm{d}\mu=\int f\,\mathrm{d}\mu+\int g\,\mathrm{d}\mu$；
>4. 若 $g\leq f$ a.e.，则 $\int g\,\mathrm{d}\mu\leq\int f\,\mathrm{d}\mu$；
>5. 若 $g=f$ a.e.，则 $\int g\,\mathrm{d}\mu=\int f\,\mathrm{d}\mu$；
>6. $\left|\int f\,\mathrm{d}\mu\right|\leq\int|f|\,\mathrm{d}\mu$。
>
> ^thm-b8c9d0

(1) 显然（$f\geq 0$ 时 $f^{-}=0$）。(2) 注意 $a>0$ 时 $(af)^{+}=af^{+}$、$(af)^{-}=af^{-}$，代入定义即可。(3) 利用 $f+g=(f^{+}+g^{+})-(f^{-}+g^{-})$，由 [[#^lem-a7b8c9|引理 1.4.6]] 和 [[#^lem-d4e5f6|引理 1.4.5]] 的 (3) 展开即得。(4)-(6) 照例由 (1)-(3) 套用 [[#^lem-8e0f2a|引理 1.4.2]]。

**总结**：这六条性质在四步构造里被证明了四次，每一次的证明骨架完全相同——这正体现了「简单 → 有界 → 非负 → 一般」四步法的威力：每放松一层限制，只需处理「新出现的那一点麻烦」，其余性质自动继承。最终我们得到的是一个满足线性性、非负性、单调性、三角不等式的积分，它是后续所有期望计算（§1.6）和 Fubini 定理（§1.7）的地基。

# 3. 积分的记法 - Notation

不同测度空间下的积分各有传统记法，统一列表如下：

| 情形 | 测度空间 | 记法 |
|:---|:---|:---|
| $\mathbf{R}^d$ 上的 Lebesgue 测度 | $(\mathbf{R}^d,\mathcal{R}^d,\lambda)$ | $\int f(x)\,\mathrm{d}x$ |
| $\mathbf{R}$ 上区间 $[a,b]$ | $(\mathbf{R},\mathcal{R},\lambda)$，$E=[a,b]$ | $\int_a^b f(x)\,\mathrm{d}x$ |
| Stieltjes 测度 | $\mu((a,b])=G(b)-G(a)$ | $\int f(x)\,\mathrm{d}G(x)$ |
| 计数测度 | $\Omega$ 可数，$\mathcal{F}$ 为幂集 | $\sum_{i\in\Omega}f(i)$ |

其中「计数测度」这一行值得强调：**求和是积分的特例**。一个可数集上的无穷级数 $\sum_{i\in\Omega}f(i)$，就是「每个点权为 $1$」的计数测度下的积分 $\int f\,\mathrm{d}\mu$。于是关于级数的一切结果，都能从关于积分的结果直接导出——这正是 Durrett 把求和统一进积分框架的用意所在。

至于测度为概率测度 $P$ 的特殊情形，即期望 $\int f\,\mathrm{d}P$，留到 §1.6 再展开。
