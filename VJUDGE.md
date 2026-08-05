# Hydro VJudge 插件 — 需求与实现文档

> 版本：基于 `@hydrooj/vjudge` v1.10.0 修改  
> 日期：2026-07-22  
> 改动范围：仅 `packages/vjudge/`，核心 `hydrooj` 包零修改

---

## 目录

1. [架构概览](#1-架构概览)
2. [功能一：用户绑定个人 CF 账号](#2-功能一用户绑定个人-cf-账号)
3. [功能二：Codeforces 语言对齐](#3-功能二codeforces-语言对齐)
4. [功能三：手动导入题目](#4-功能三手动导入题目)
5. [功能四：提交结果查看优化](#5-功能四提交结果查看优化)
6. [Bug 修复汇总](#6-bug-修复汇总)
7. [安全设计](#7-安全设计)
8. [文件清单](#8-文件清单)
9. [安装部署](#9-安装部署)
10. [配置参考](#10-配置参考)
11. [接口文档](#11-接口文档)

---

## 1. 架构概览

```
packages/vjudge/
├── package.json                    # @hydrooj/vjudge v1.10.0
├── templates/
│   ├── vjudge_user_bind.html       # [新增] 用户绑定页面
│   └── vjudge_import.html          # [新增] 手动导入页面
└── src/
    ├── index.ts                    # [修改] VJudgeService + AccountService + 入口
    ├── interface.ts                # [修改] 类型定义 + 集合声明
    ├── userBinding.ts              # [新增] 用户绑定 Handler + 路由
    ├── importHandler.ts            # [新增] 手动导入 Handler + 路由
    ├── providers/
    │   └── codeforces.ts           # [修改] Langs + 语言拉取 + 判题修复
    ├── fetch.ts                    # [未改]
    ├── proxy.ts                    # [未改]
    └── verdict.ts                  # [未改]
```

### 核心流程

```
用户打开 CF 题目 → 提交代码
    │
    ▼
AccountService.judge(task)
    │
    ├→ task.uid 存在？
    │   ├→ 是 → getUserApi(type, uid) 查找用户绑定
    │   │   ├→ 绑定有效 → 用户独立账号提交 ✅
    │   │   └→ 未绑定/过期 → SYSTEM_ERROR + 提示绑定
    │   └→ 否 → SYSTEM_ERROR（异常）
    │
    ├→ 提交到 CF → 轮询结果（3s/次，15 分钟超时）
    │
    └→ 记录状态实时更新（排队/运行中/完成）
```

> **设计原则**：完全取消服务器共享账号。所有操作（提交代码、导入题目）均强制要求用户绑定个人账号。未绑定时返回明确错误提示，引导用户前往绑定页面。

---

## 2. 功能一：用户绑定个人 CF 账号

### 2.1 需求

- 每个 Hydro 用户可绑定自己的 Codeforces（或其他 OJ）账号
- **完全取消服务器共享账号**：提交代码和导入题目均强制使用用户个人账号
- 未绑定时拒绝操作并提示引导前往绑定页面
- 用户绑定页面可管理（绑定/解绑/查看状态）

### 2.2 数据结构

**MongoDB 集合：`vjudge.user_account`**

```typescript
interface UserRemoteAccount {
    _id: string;
    uid: number;          // Hydro 用户 ID
    domainId: string;
    type: string;         // 'codeforces' 等
    handle: string;       // CF 用户名（仅展示，不用于登录）
    cookie: string[];     // CF 登录 cookie（替换密码认证）
    enabled: boolean;
    error?: string;       // cookie 过期等错误信息
    updatedAt: Date;
}
```

**安全设计：不存储用户密码**

- 用户只需提供从浏览器复制的 cookie 字符串
- 密码字段永不为空，防止误用共享密码
- cookie 过期自动禁用绑定并提示重绑

### 2.3 Handler 路由

| 路由名 | URL | 方法 | 权限 | 功能 |
|--------|-----|------|------|------|
| `vjudge_user_bind` | `/vjudge/account/bind` | GET/POST | `PRIV_USER_PROFILE` | 绑定页面 + 绑定操作 |
| `vjudge_user_unbind` | `/vjudge/account/unbind` | POST | `PRIV_USER_PROFILE` | 解绑操作 |
| `vjudge_user_check_bind` | `/vjudge/account/check/:type` | GET | `PRIV_USER_PROFILE` | 查询绑定状态 |

### 2.4 绑定验证流程

```
用户输入 handle + cookie → POST /vjudge/account/bind
    │
    ▼
创建临时 Provider（password: ''）
    │
    ▼
api.ensureLogin() → 用 cookie 访问 CF 检测登录状态
    │
    ├→ 页面含 header-bell__img → cookie 有效 → 绑定成功 ✅
    └→ 不含 → cookie 无效 → BadRequestError 提示 ❌
```

### 2.5 提交时的账号选择（强制绑定）

```typescript
// AccountService.judge() 中的逻辑 — 无共享账号，强行要求绑定
const userId = task.uid;
if (!userId) {
    end({ status: STATUS.STATUS_SYSTEM_ERROR,
          message: 'No user associated with this submission.' });
    return;
}
const binding = await getUserApi(this.type, userId);
if (!binding) {
    end({
        status: STATUS.STATUS_SYSTEM_ERROR,
        message: `You must bind a ${this.type} account before submitting.
                  Go to User Menu → VJudge Account Binding to set it up.`,
    });
    return;
}
// 使用用户个人账号提交
const { api, handle } = binding;
await api.submitProblem(...);
```

**getUserApi() 辅助函数**（`userBinding.ts`）：
- 从 `vjudge.user_account` 查找用户绑定
- 用用户 cookie 创建 Provider 实例
- 调用 `ensureLogin()` 验证 cookie 有效性
- cookie 无效 → 自动标记 `enabled: false` → 返回 null
- cookie 有效 → 返回 `{ api, handle }`

### 2.6 页面截图描述

**绑定页面** (`vjudge_user_bind.html`)：
- 显示所有可用的 OJ 类型
- 已绑定：绿色 "Bound" + 用户名 + 更新时间 + 解绑按钮
- 未绑定：灰色 "Not Bound" + handle 输入框 + cookie 输入框 + 绑定按钮
- 操作成功：绿色横幅提示
- 无 provider：提示联系管理员

**入口**：用户下拉菜单 → "VJudge Account Binding"

---

## 3. 功能二：Codeforces 语言对齐

### 3.1 需求

- 提交 CF 题目时，可选语言应与 CF 实际支持的编译器一致
- CF 独有的编译器不应出现在本地评测题目中
- 语言列表应能自动更新，跟进 CF 的编译器变化

### 3.2 实现方案：双层语言源

```
┌──────────────────────────────────────────────┐
│ 第一层：static Langs（硬编码，启动时立即生效） │
│ → 30 种常见 CF 编译器，确保开箱即用            │
├──────────────────────────────────────────────┤
│ 第二层：fetchLangList()（动态拉取，登录后补充） │
│ → 访问 CF 提交页实时抓取最新编译器列表         │
│ → 增量添加新语言，不覆盖已有配置               │
└──────────────────────────────────────────────┘
```

### 3.3 static Langs（codeforces.ts）

```typescript
static Langs = {
    'codeforces.54': { display: 'GNU G++17 7.3.0', key: '54' },
    'codeforces.73': { display: 'GNU G++20 13.2 (64bit)', key: '73' },
    'codeforces.70': { display: 'GNU G++20 11.2.0 (64bit)', key: '70' },
    // ... 共 30 种语言
};
```

覆盖语言：C/C++/Python/PyPy/Java/Kotlin/Go/Node.js/Ruby/PHP/C#/D/Haskell/Scala/OCaml/Perl/Pascal

### 3.4 fetchLangList() 动态拉取

```typescript
async fetchLangList() {
    // 访问 CF 提交页抓取 <select name="programTypeId">
    const { document } = await this.html('/problemset/submit/1/A');
    const options = document.querySelectorAll('select[name="programTypeId"] option');
    for (const opt of options) {
        result[`codeforces.${opt.value}`] = { display: opt.text, key: opt.value };
    }
    return result;
}
```

- 触发时机：首次有用户绑定该 OJ 类型的账号时（仅执行一次）
- 失败处理：日志警告，继续使用 static Langs
- 去重机制：`langFetched` Set 确保多账号不重复拉取

### 3.5 语言隔离机制

CF 语言配置自带 `hidden: true`，天然实现隔离：

| 问题类型 | 语言列表来源 | CF 编译器可见？ | 本地编译器可见？ |
|----------|-------------|:---:|:---:|
| CF 远程评测 | `key.startsWith('codeforces.')` | ✅ | ❌ |
| 本地评测 | `!hidden && !remote` | ❌ | ✅ |

### 3.6 Bug 修复：validAs 导致语言 ID 丢失

**问题**：`validAs` 把 `codeforces.73` 映射为 `73`，然后 `submitProblem` 中 `includes('codeforces.')` 检测失败 → 始终回退到 G++17

**修复**：

```typescript
// 修复前
const programTypeId = lang.includes('codeforces.') ? lang.split('codeforces.')[1] : '54';
// 修复后
const programTypeId = lang.includes('codeforces.') ? lang.split('codeforces.')[1] : lang;
```

---

## 4. 功能三：手动导入题目

### 4.1 需求

- 管理员可通过输入题号手动导入单个 CF 题目
- **使用导入者自己的绑定账号**（而非共享账号）爬取题目
- 仅管理员/题目创建者可操作
- 未绑定账号时拒绝导入并提示

### 4.2 路由

| 路由名 | URL | 方法 | 权限 | 功能 |
|--------|-----|------|------|------|
| `vjudge_import` | `/vjudge/import` | GET/POST | `PERM_CREATE_PROBLEM` | 导入表单 + 导入操作 |

**入口**：`ProblemAdd` 菜单 → "Import From Remote OJ"

### 4.3 导入流程

```
选择 OJ 类型 → 输入题号（如 4A 或 P1000A）→ 可选 ID 前缀
    │
    ▼
1. getUserApi(type, uid) → 获取导入者的绑定 API
   ├→ 未绑定 → BadRequestError + 提示绑定
   └→ 绑定有效 → 继续
2. api.getProblem(fullId) → 爬取题目详情
3. ProblemModel.add() → 录入 Hydro
4. 自动挂载域名（如未挂载）
5. 重定向到题目详情页
```

### 4.4 导入内容明细

| 内容 | 来源 | 存储位置 |
|------|------|---------|
| 标题 | CF 题目标题 | `ProblemDoc.title` |
| 题目描述 | HTML 题面（数学公式转换为 katex） | `ProblemDoc.content` |
| 输入/输出格式 | input-specification / output-specification | `ProblemDoc.content` |
| 样例 | HTML `<pre>` 块，解析分段样例 | `ProblemDoc.content` |
| 提示 | note 部分 | `ProblemDoc.content` |
| 标签 | `.tag-box` 元素 | `ProblemDoc.tag` |
| 难度 | *800 等评分标签 → 1-10 等级 | `ProblemDoc.difficulty` |
| 时限/内存 | CF 题目配置 | `config.yaml` (testdata) |
| 图片 | CF CDN 图片 → 本地存储 | `ProblemDoc.additional_file` |

### 4.5 错误处理

| 场景 | 提示 |
|------|------|
| 用户未绑定账号 | `You must bind a codeforces account before importing problems. Go to User Menu → VJudge Account Binding to set it up.` |
| 题号不存在 | `Problem P4A not found or not available on codeforces.` |
| 题目已存在 | `Problem P4A already exists in this domain.` |
| OJ 类型未知 | `Unknown remote OJ type: xxx.` |

---

## 5. 功能四：提交结果查看优化

### 5.1 需求

- 提交后实时显示排队/运行状态
- 运行中的测试点不应误标为 WA
- 完整展示每个测试点的时间和内存消耗
- 防止轮询死循环

### 5.2 各阶段用户看到的内容

| CF API 返回 | 用户看到 | 进度 |
|------------|---------|------|
| `waiting:true, testCount:0` | `judgeTexts: "In queue..."` | `progress: 0%` |
| `waiting:true, testCount:4` | `judgeTexts: "Running test 4..."` + 测试点结果 | `progress: 20%` |
| `waiting:false` | 最终判题结果 | `progress: 100%` |
| 测试点 "TESTING" 或空 | 状态显示 **Judging**（而非 WA） | - |

### 5.3 关键修复

**进行中的测试点状态**：

```typescript
// 修复前
const mappedStatus = VERDICT[verdictStr] || STATUS.STATUS_WRONG_ANSWER;
// "TESTING" → VERDICT 未命中 → 错误显示为 WA ❌

// 修复后
if (!verdictStr || verdictStr === 'TESTING') {
    mappedStatus = STATUS.STATUS_JUDGING;   // 正确显示为评测中 ✅
} else {
    mappedStatus = VERDICT[verdictStr] || STATUS.STATUS_WRONG_ANSWER;
}
```

**进度消息**：

```typescript
if (body.waiting === 'true') {
    const progressMsg = totalTests > 0
        ? `Running test ${totalTests}...`
        : 'In queue...';
    await next({ message: progressMsg, progress: Math.min(totalTests * 5, 95) });
    continue;
}
```

---

## 6. Bug 修复汇总

### 6.1 CF 限流时间反向 🐛

```typescript
// 修复前
if (Date.now() - start < 16000) await sleep(Date.now() - start);
// 耗时 2s → sleep(2000) → 总计仅 4s

// 修复后
const elapsed = Date.now() - start;
if (elapsed < 16000) await sleep(16000 - elapsed);
// 耗时 2s → sleep(14000) → 总计 16s ✅
```

### 6.2 normalize(undefined) 崩溃 🐛

```typescript
// 修复前
const status = VERDICT[Object.keys(VERDICT).find(
    (k) => normalize(body.verdict).includes(k)  // body.verdict 可能 undefined
)];

// 修复后
const matchedKey = Object.keys(VERDICT).find(
    (k) => normalize(body.verdict || '').includes(k)  // 安全处理空值
);
const status = matchedKey ? (VERDICT[matchedKey] || STATUS.STATUS_SYSTEM_ERROR) : STATUS.STATUS_SYSTEM_ERROR;
```

### 6.3 轮询无超时 🐛

```typescript
// 新增 15 分钟超时保护
const MAX_WAIT_TIME = 15 * 60 * 1000;
if (Date.now() - start > MAX_WAIT_TIME) {
    await end({
        status: STATUS.STATUS_SYSTEM_ERROR,
        message: 'Submission timed out waiting for result.',
        score: 0, time: 0, memory: 0,
    });
    break;
}
```

### 6.4 validAs 语言 ID 丢失 🐛

见 [3.6 节](#36-bug-修复validas-导致语言-id-丢失)

---

## 7. 安全设计

### 7.1 用户密码不存储

`UserRemoteAccount` 仅存储 `handle` + `cookie`，无 `password` 字段。

### 7.2 绑定验证

- 仅在绑定时通过 `ensureLogin()` 验证 cookie 有效性
- 验证失败用 `BadRequestError`（用户友好错误页），不暴露堆栈
- 提交/导入时验证失败 → `getUserApi()` 自动标记 `enabled: false` + 返回 null → 拒绝操作并提示用户重新绑定

### 7.3 权限控制

| 操作 | 权限 | 需绑定账号？ |
|------|------|:---:|
| 查看绑定页 | `PRIV_USER_PROFILE`（需登录） | — |
| 绑定/解绑 | `PRIV_USER_PROFILE` | — |
| 查询绑定状态 | `PRIV_USER_PROFILE` | — |
| 手动导入 | `PERM_CREATE_PROBLEM` | ✅ 必须 |
| 提交代码 | 无额外权限 | ✅ 必须 |

### 7.4 无共享账号架构

```
每个用户独立绑定 → 所有 CF 操作使用个人 cookie
                     ├── 提交代码
                     ├── 导入题目
                     └── 语言列表拉取（用首个已绑定用户的账号）

无需配置 MongoDB vjudge 集合
无需存储任何服务器的 CF 密码
VJudgeService 按 type 创建单例 AccountService（无凭证）
```


### 7.5 MongoDB 错误处理

```typescript
try {
    await collUserAccount.updateOne(...);
} catch (e) {
    throw new BadRequestError('Failed to save binding due to a database error.');
}
```

### 7.6 无循环依赖

```
index.ts → userBinding.ts → providers/index
    │            │                  ↑
    └────────────┴──────────────────┘
```

---

## 8. 文件清单

| 文件 | 状态 | 行数 | 说明 |
|------|:---:|------|------|
| `src/index.ts` | 修改 | ~480 | VJudgeService + AccountService + apply() |
| `src/interface.ts` | 修改 | ~75 | 新增 UserRemoteAccount 接口和集合声明 |
| `src/userBinding.ts` | **新增** | ~115 | 3 个 Handler + 路由注册 + 通知注入 |
| `src/importHandler.ts` | **新增** | ~85 | 手动导入 Handler + 路由 + UI 注入 |
| `src/providers/codeforces.ts` | 修改 | ~460 | static Langs + fetchLangList() + 判题 Bug 修复 |
| `templates/vjudge_user_bind.html` | **新增** | ~80 | 用户绑定/解绑页面 |
| `templates/vjudge_import.html` | **新增** | ~55 | 手动导入表单页面 |
| **其他核心包** | **未修改** | 0 | hydrooj/hydrojudge/ui-default 均无改动 |

---

## 9. 安装部署

### 9.1 安装 Hydro

```bash
# Linux (Debian 12 推荐)
LANG=zh . <(curl https://hydro.ac/setup.sh)
```

### 9.2 部署修改后的 vjudge 插件

**方式 A：本地 addon（推荐）**

```bash
# 1. 复制到服务器
scp -r packages/vjudge root@服务器:~/.hydro/addons/

# 2. 注册并重启
hydrooj addon add ~/.hydro/addons/vjudge
hydrooj restart
```

**方式 B：开发模式（本机运行）**

```bash
cd Hydro
yarn build
hydrooj restart
```

### 9.3 开始使用

**无需配置 MongoDB 集合！** 安装后直接使用：

1. 管理员/用户登录 Hydro
2. 点击右上角用户名 → **VJudge Account Binding**
3. 输入 CF handle + 浏览器 cookie → 绑定成功
4. 回到题目页面 → ProblemAdd → **Import From Remote OJ** 导入题目
5. 用户提交代码时自动使用绑定的个人账号

> 不再需要配置 `vjudge` 集合或 `vjudge.mount` 集合。导入题目时会自动创建域名挂载。

---

## 10. 配置参考

### 环境变量

| 变量 | 说明 |
|------|------|
| `VJUDGE_DEBUG` | 逗号分隔的 OJ 类型列表，只启用指定的（如 `codeforces,poj`） |
| `HYDRO_CLI` | 设为真时跳过 vjudge 初始化（CLI 模式） |
| `NODE_APP_INSTANCE` | 非 `0` 时跳过（多实例部署） |

### 用户绑定示例

用户在页面输入：
- **Handle**: `tourist`
- **Cookie**: `X-User-Sha1=abc123...; 39ce7=def456...`

MongoDB 存储：
```json
{
    "uid": 1,
    "type": "codeforces",
    "handle": "tourist",
    "cookie": ["X-User-Sha1=abc123...", "39ce7=def456..."],
    "enabled": true,
    "updatedAt": "2026-07-22T10:00:00Z"
}
```

### 系统设置

- `vjudge.builtin-codeforces-disable`：设为 `true` 禁用 CF VJudge
- `hydrooj.langs`：自动注入 CF 编译器列表（启动时 static Langs + 首次有用户绑定时动态拉取）

---

## 附录：改动对比表

| 需求 | 修改前（原版） | 修改后 |
|------|--------|--------|
| 账号使用 | 仅服务器共享账号 | **纯用户个人绑定**，无共享账号 |
| 未绑定行为 | 不存在（只有共享账号） | 拒绝操作 + 友好提示引导绑定 |
| CF 语言 | 管理员手动配置 | 30 种预置 + 首次绑定自动爬取更新 |
| 手动导入 | 无 | ProblemAdd → Import From Remote OJ |
| 自动同步 | 需要配置 vjudge+vjudge.mount | **已移除**（全改为手动按需导入） |
| 安装配置 | MongoDB 手动插入账号 | **零配置**：安装即用，用户自行绑定 |
| 提交进度 | 排队/运行中无提示 | "In queue..." / "Running test N..." |
| 测试点状态 | "TESTING" 显示为 WA | 显示为 Judging |
| 轮询超时 | 无限轮询 | 15 分钟超时 |
| CF 限流 | sleep 时间反向 | 正确保证 16s 间隔 |
| 未知判题 | normalize(undefined) 崩溃 | 返回 SYSTEM_ERROR |
| 用户提示 | throw Error → 500 白页 | BadRequestError → 友好错误页 |
| 错误处理 | MongoDB 异常无捕获 | try/catch + 用户提示 |

---

## 11. 接口文档

> 以下文档基于设计描述推导，与源码可能存在细微差异。建议以 `userBinding.ts` 和 `importHandler.ts` 中的实际代码为准。

### 11.1 用户绑定相关接口

#### 11.1.1 绑定页面 + 绑定操作

```
  GET/POST  /vjudge/account/bind
```

| 属性 | 说明 |
|------|------|
| 路由名 | `vjudge_user_bind` |
| 权限 | `PRIV_USER_PROFILE`（需登录） |
| 文件 | `src/userBinding.ts` |

**GET — 渲染绑定页面**

无请求参数。返回 `vjudge_user_bind.html` 模板渲染的 HTML 页面。

页面渲染上下文（模板变量）：

| 变量 | 类型 | 说明 |
|------|------|------|
| `providers` | `Array<{type: string, name: string}>` | 所有可用的 OJ 类型列表（如 `[{type:'codeforces', name:'Codeforces'}]`） |
| `bindings` | `Record<string, {handle: string, enabled: boolean, error?: string, updatedAt: Date}>` | 当前用户已有绑定的映射表，key 为 OJ type |

**POST — 执行绑定**

| 参数 | 位置 | 类型 | 必填 | 说明 |
|------|------|------|:---:|------|
| `type` | body | `string` | ✅ | OJ 类型，如 `codeforces` |
| `handle` | body | `string` | ✅ | 用户在 CF 上的用户名（仅用于展示） |
| `cookie` | body | `string` | ✅ | 从浏览器复制的 CF cookie 字符串 |

**成功响应**：页面显示绿色横幅 `Binding updated successfully.`，列表中该 OJ 变为绿色 `Bound` 状态。

**错误响应**：

| HTTP 状态 | 错误类型 | 触发条件 | 用户看到的提示 |
|-----------|---------|---------|---------------|
| 400 | `BadRequestError` | cookie 验证失败（`ensureLogin()` 未检测到 `header-bell__img`） | `Cookie verification failed. Please ensure you copied the full cookie string from a logged-in browser session.` |
| 400 | `BadRequestError` | MongoDB 写入失败 | `Failed to save binding due to a database error.` |

---

#### 11.1.2 解绑操作

```
  POST  /vjudge/account/unbind
```

| 属性 | 说明 |
|------|------|
| 路由名 | `vjudge_user_unbind` |
| 权限 | `PRIV_USER_PROFILE`（需登录） |
| 文件 | `src/userBinding.ts` |

| 参数 | 位置 | 类型 | 必填 | 说明 |
|------|------|------|:---:|------|
| `type` | body | `string` | ✅ | 要解绑的 OJ 类型，如 `codeforces` |

**成功响应**：页面显示绿色横幅 `Binding removed successfully.`，列表中该 OJ 恢复灰色 `Not Bound` 状态。

**错误响应**：

| HTTP 状态 | 错误类型 | 触发条件 |
|-----------|---------|---------|
| 400 | `BadRequestError` | MongoDB 删除操作失败 |

> 解绑仅从 `vjudge.user_account` 中删除记录，不主动使当前正在进行的提交失效。

---

#### 11.1.3 查询绑定状态

```
  GET  /vjudge/account/check/:type
```

| 属性 | 说明 |
|------|------|
| 路由名 | `vjudge_user_check_bind` |
| 权限 | `PRIV_USER_PROFILE`（需登录） |
| 文件 | `src/userBinding.ts` |

| 参数 | 位置 | 类型 | 必填 | 说明 |
|------|------|------|:---:|------|
| `type` | path | `string` | ✅ | OJ 类型，如 `codeforces` |

**成功响应**（JSON）：

```json
// 已绑定且 cookie 有效
{
    "bound": true,
    "handle": "tourist",
    "enabled": true,
    "updatedAt": "2026-07-22T10:00:00Z"
}

// 已绑定但 cookie 过期（getUserApi 会标记 enabled=false，下次调用返回 null）
{
    "bound": false
}

// 从未绑定
{
    "bound": false
}
```

| 字段 | 类型 | 说明 |
|------|------|------|
| `bound` | `boolean` | 是否存在有效绑定 |
| `handle` | `string?` | CF 用户名（仅 `bound=true` 时返回） |
| `enabled` | `boolean?` | cookie 是否通过验证 |
| `updatedAt` | `string?` | 最后更新时间（ISO 格式） |
| `error` | `string?` | cookie 过期等错误原因 |

> **注意**：此接口只做数据库查询，不实时验证 cookie。要获取实时验证结果，应调用 `getUserApi()` 内部函数（见 11.3 节）。

---

### 11.2 手动导入题目接口

#### 11.2.1 导入表单 + 执行导入

```
  GET/POST  /vjudge/import
```

| 属性 | 说明 |
|------|------|
| 路由名 | `vjudge_import` |
| 权限 | `PERM_CREATE_PROBLEM`（仅管理员/题目创建者） |
| 文件 | `src/importHandler.ts` |

**GET — 渲染导入表单**

无请求参数。返回 `vjudge_import.html` 模板渲染的 HTML 页面。

**POST — 执行导入**

| 参数 | 位置 | 类型 | 必填 | 说明 |
|------|------|------|:---:|------|
| `type` | body | `string` | ✅ | OJ 类型，如 `codeforces` |
| `pid` | body | `string` | ✅ | 题号，如 `4A`、`P1000A`、`1000A` |
| `prefix` | body | `string` | ❌ | 题号前缀，生成最终的 Hydro 题目 ID（如 `CF` → `CF4A`） |

**成功响应**：HTTP 302 重定向到导入后的题目详情页。

**错误响应**：

| HTTP 状态 | 触发条件 | 用户看到的提示 |
|-----------|---------|---------------|
| 400 | 用户未绑定该 OJ 类型 | `You must bind a codeforces account before importing problems. Go to User Menu → VJudge Account Binding to set it up.` |
| 400 | 题号不存在 | `Problem P4A not found or not available on codeforces.` |
| 400 | 题目已存在（同一 domain 内） | `Problem P4A already exists in this domain.` |
| 400 | OJ 类型不在 provider 列表中 | `Unknown remote OJ type: xxx.` |
| 400 | MongoDB 写入失败 | 数据库错误提示 |

---

### 11.3 内部 API：getUserApi()

此函数是 `userBinding.ts` 导出的核心辅助函数，被 `AccountService.judge()` 和 `importHandler` 调用，不属于 HTTP 接口但定义了关键的内部契约。

```typescript
/**
 * 获取指定用户的 OJ Provider 实例
 * @param type   OJ 类型，如 'codeforces'
 * @param uid    Hydro 用户 ID
 * @returns      { api: Provider, handle: string } | null
 */
async function getUserApi(type: string, uid: number): Promise<{
    api: Provider;    // 用该用户 cookie 初始化的 Provider 实例
    handle: string;   // 用户在 CF 的用户名
} | null>
```

**处理流程**：

```
getUserApi(type, uid)
  │
  ├→ collUserAccount.findOne({ type, uid })
  │   └→ 无记录 → return null
  │
  ├→ 用 cookie 创建 Provider 实例
  │
  ├→ api.ensureLogin()
  │   ├→ 成功 → return { api, handle }
  │   └→ 失败 → 标记 enabled: false + 记录 error
  │        └→ return null
  │
  └→ 异常（网络/解析错误）
       └→ 标记 enabled: false + 记录 error
            └→ return null
```

**返回值语义**：

| 返回值 | 含义 | 调用方行为 |
|--------|------|-----------|
| `{ api, handle }` | 绑定有效，cookie 通过验证 | 正常执行提交/导入 |
| `null` | 未绑定 / cookie 过期 / 网络异常 | 拒绝操作，提示用户绑定/重绑 |

**副作用**：cookie 验证失败时自动将 `vjudge.user_account` 中该记录的 `enabled` 设为 `false`、写入 `error` 字段。用户下次访问绑定页面时能看到错误原因并重新绑定。

---

### 11.4 提交判题响应格式（AccountService.judge）

提交代码后，Hydro 通过 `end()` / `next()` 回调向用户推送的进度与结果数据。

#### 进度推送（next）

由轮询循环中每次调用 `next()` 产生，Hydro 前端实时展示：

```typescript
interface JudgeProgress {
    message: string;   // 用户可见的状态文本
    progress: number;  // 进度百分比 0-100
}
```

| CF API 状态 | `message` | `progress` | 说明 |
|-------------|-----------|:---:|------|
| `waiting=true, testCount=0` | `"In queue..."` | 0 | 排队中 |
| `waiting=true, testCount=N` | `"Running test N..."` | `min(N*5, 95)` | 第 N 个测试点执行中 |

#### 最终结果（end）

```typescript
interface JudgeResult {
    status: number;        // Hydro STATUS 枚举值
    message?: string;      // 人类可读的判题结果
    score: number;         // 得分
    time: number;          // 总运行时间 (ms)
    memory: number;        // 总内存消耗 (KB)
    compiler_text?: string;// 编译器输出（CE 时）
    cases?: Array<{        // 各测试点详情
        status: number;
        time: number;
        memory: number;
        message: string;
    }>;
}
```

| 场景 | `status` | `message` | 特殊处理 |
|------|----------|-----------|---------|
| AC（Accepted） | `STATUS.STATUS_ACCEPTED` | CF 返回的 verdict 文本 | — |
| WA（Wrong Answer） | `STATUS.STATUS_WRONG_ANSWER` | CF 返回的 verdict 文本 | — |
| TLE | `STATUS.STATUS_TIME_LIMIT_EXCEEDED` | CF 返回的 verdict 文本 | — |
| CE（Compile Error） | `STATUS.STATUS_COMPILE_ERROR` | — | 额外返回 `compiler_text` |
| 测试点 "TESTING"/空 | `STATUS.STATUS_JUDGING` | — | 仅进度推送中出现，不在最终结果中 |
| 未匹配的 verdict | `STATUS.STATUS_WRONG_ANSWER` | — | 兜底值 |
| `verdict` 为 undefined | `STATUS.STATUS_SYSTEM_ERROR` | — | 6.2 修复后的行为 |
| 轮询超时（>15 分钟） | `STATUS.STATUS_SYSTEM_ERROR` | `"Submission timed out waiting for result."` | `score/time/memory` 均置 0 |
| 未绑定账号 | `STATUS.STATUS_SYSTEM_ERROR` | 提示绑定信息 | 见 2.5 节 |
| 缺少 uid | `STATUS.STATUS_SYSTEM_ERROR` | `"No user associated with this submission."` | — |

---

### 11.5 路由注册与 UI 注入

**路由注册**（`userBinding.ts` 和 `importHandler.ts` 的 `apply()` 中）：

```typescript
// userBinding.ts
ctx.Route('vjudge_user_bind',       '/vjudge/account/bind',        userBindHandler);
ctx.Route('vjudge_user_unbind',     '/vjudge/account/unbind',      userUnbindHandler);
ctx.Route('vjudge_user_check_bind', '/vjudge/account/check/:type', userCheckBindHandler);

// importHandler.ts
ctx.Route('vjudge_import', '/vjudge/import', importHandler);
```

**UI 菜单注入**：

| 注入点 | 注入内容 | 来源 |
|--------|---------|------|
| 用户下拉菜单 (`UserMenu`) | "VJudge Account Binding" 入口 | `userBinding.ts` 的 `apply()` |
| 题目添加菜单 (`ProblemAdd`) | "Import From Remote OJ" 入口 | `importHandler.ts` 的 `apply()` |
| 全局通知 (`Notifications`) | "请绑定账号" 提示 | `userBinding.ts` 注入到 `NotificationService` |
