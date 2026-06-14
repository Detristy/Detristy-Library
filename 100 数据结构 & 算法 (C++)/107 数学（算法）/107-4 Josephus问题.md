---
tags:
  - 约瑟夫问题
  - 算法
---
# 1. Josephus问题
考虑下面这个问题：
$n$ 个人标号 $0,1,\dots,n-1$ ，令他们逆时针站成一圈，从编号 $0$ 开始，每一次从当前的人逆时针数 $k$ 个，令这个人出局，求最后一个出局的人。

# 2. 环形链表
我们通过引入环形链表来解决这个问题，考虑直接枚举，在环形链表模拟枚举删除的过程，只需要重复 $n-1$ 次即可。复杂度是 $O(n^2)$ 的。

```cpp
#include <iostream>

using namespace std;

// 1. 定义链表节点
struct Node {
    int id;
    Node *next;
    Node(int val) : id(val), next(NULL) {}
};

void josephus(int n, int m) {
    if (n <= 0 || m <= 0) return;

    // 2. 建立循环单链表
    Node* head = new Node(1);
    Node* tail = head;
    for (int i = 2; i <= n; i++) {
        tail->next = new Node(i);
        tail = tail->next;
    }
    tail->next = head; // 🌟 核心：首尾相连，织网成环！

    // 3. 开始模拟“数数出局”
    Node* prev = tail;  // prev 始终指向当前点 p 的前驱节点
    Node* p = head;     // p 是当前的数数起点

    cout << "出局顺序为: ";
    while (n--) {
        // 数 m-1 步，走到要出局的那个节点 p
        for (int i = 0; i < m - 1; i++) {
            prev = p;
            p = p->next;
        }

        // 此时 p 就是要出局的人，prev 是他前面的那个人
        cout << p->id << " ";

        // “外科手术”：让前驱跳过 p，拉住 p 的下一个节点
        prev->next = p->next;
        delete p; // 释放内存

        // 下一次数数，从被删节点的下一个节点开始
        p = prev->next;
    }
    cout << endl;
}

int main() {
    // 提速咒语
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (cin >> n >> m) {
        josephus(n, m);
    }

    return 0;
}
```

# 3. 对数算法
考虑每次走 $k$ 个删一个，那么一圈能删 $\left\lfloor  \frac{n}{k}  \right\rfloor$ 个，此时剩余 $n-\left\lfloor  \frac{n}{k}  \right\rfloor$ 个人，指针在 $\left\lfloor  \frac{n}{k}  \right\rfloor \times k$ 个人的位置上，此时其等价于 $n-n\mod k$ ，我们继续递归处理，算完后还原其相对位置。复杂度是 $O(k\log n)$ 的。

```cpp
int josephus(int n, int k) {
  if (n == 1) return 0;
  if (k == 1) return n - 1;
  if (k > n) return (josephus(n - 1, k) + k) % n;  // 线性算法
  int res = josephus(n - n / k, k);
  res -= n % k;
  if (res < 0)
    res += n;  // mod n
  else
    res += res / (k - 1);  // 还原位置
  return res;
}
```