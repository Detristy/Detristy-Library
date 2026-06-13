# Wiki Schema

## Domain
个人知识库 — 数据结构与算法 (C++)、高等数学、大学物理、Python 编程。

## Vault Structure
```
Obsidian Vault/
├── SCHEMA.md                # 本文件
├── index.md                 # 内容索引
├── log.md                   # 操作日志
├── 100 数据结构 & 算法 (C++)/   # DSA + 引述/证明
├── 200 数学/                   # 高数 (重积分、级数、微分方程等)
├── 300 大学物理/               # 物理
├── 400 Python/                # 语法 & 项目日志
└── Assets/                    # 图片附件
```

## Conventions
- 文件名：`NNN-N 子题名.md`（如 `210-1-6 偏导数 全微分.md`）
- YAML frontmatter 必带 `tags:`（中文分类标签，精简到 3-4 个核心标签）和 `aliases:`（1-2 个搜索关键词）
- 使用 Obsidian callouts：`[!definition]`、`[!corollary]`、`[!example]`、`[!warning]`、`[!NOTE]`、`[!tip]`、`[!proposition]`
- 人称统一用「我们」
- LaTeX `$$` 公式，`^block-anchors` 做交叉引用
- 当前 Wiki 文件是 Obsidian Vault 的子集；所有已存在的 Obsidian 笔记自动纳入 wiki

## Frontmatter
```yaml
---
tags:
  - 高数
  - 多元函数
  - 偏导数
aliases:
  - 偏导数
---
```

- `tags:` 最多 4 个，只用顶层分类
- `aliases:` 保留 1-2 个核心搜索词

## Tag Taxonomy
| Tag | 用途 |
|-----|------|
| 数据结构 | DSA 笔记 |
| 算法 | 算法分析、策略 |
| 高数 | 高等数学 |
| 多元函数 | 多元微积分 |
| 物理 | 大学物理 |
| Python | Python 编程 |

## Page Thresholds
- **不新建** 超过 20 行的独立页面——优先补充到现有笔记
- **不删除** 任何内容——这是用户自己的笔记，AI 只补充不删改
- **交叉链接** 新内容必须与至少 1 篇已有笔记互链

## Update Policy
- 发现矛盾：标注 `[!warning]` 而不是覆盖
- 补充内容：追加新的 `>[!example]` 或 `>[!NOTE]`，不重写已有定义
- 每次修改追加到 log.md

## Wiki ↔ Cloud Sync
- 云端同步走 Git（本仓库）
- 备份由 cron 定时脚本 `scripts/hermes_backup.sh` 处理（保留 5 天）
