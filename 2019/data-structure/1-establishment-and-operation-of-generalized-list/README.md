# 1. Establishment and Operation of Generalized List (广义表的建立与基本操作) 

**Description:**

采用"头尾法存储广义表，实现以下广义表的操作：
  1．Status CreateGList( GList &L, char *S ) // 根据字符串 S 表示的广义表内容建立广义表数据结构；
  2．GList GetHead( GList L) // 取表头运算
  3．GList GetTail( GList L) // 取表尾运算
  4．void DestroyGList( GList &L) // 销毁广义表 L
  5．void PrintGList( GList L) // 显示广义表 L 内容

程序运行时，首先输入一个广义表，表中的原子是小写字母。随后可以交替输入取表头或取表尾指令（分别用 1 和 2 表示），取的结果替代当前广义表，并释放相应的资源（需将释放资源信息输出）。当广义表是空或是原子时，程序停止运行。

**Example:**

- Input:

```
(a,(b,(c,d)),e,f)
2
1
2
1
1
```

- Output:

```
generic list: (a,(b,(c,d)),e,f)
free head node
free list node
generic list: ((b,(c,d)),e,f)
destroy tail
free list node
generic list: (b,(c,d))
free head node
free list node
generic list: ((c,d))
destroy tail
free list node
generic list: (c,d)
destroy tail
free list node
generic list: c
```
