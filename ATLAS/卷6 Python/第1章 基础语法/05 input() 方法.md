---
tags:
  - Python
---
# 1. 语法

函数语法如下：
```python
input([prompt])
```

> [!warning] 返回值
> 无论输入什么内容，input()  返回的始终是一个字符串，如果有需要，则必须进行手动的类型转换。

# 2. input().split()

通过使用 `split()` 可以将输入按空格拆分为字符串数组。

通过搭配使用 `map()` 来方便地接收多个数据，例如：

```python
listName = map(int,input().split())
```

可以一次性获取多个整数并且存入一个列表中。