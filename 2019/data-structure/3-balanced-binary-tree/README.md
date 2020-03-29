# 3. Balanced Binary Tree (平衡二叉树) 

**Description:**

 程序输入一个字符串（只包含小写字母），请按照字符的输入顺序建立平衡二叉排序树，并分别输出二叉树的先序序列、中序序列和后序序列，最后输出该二叉树向左旋转 90 度后的结构。

例如：向左旋转 90 度后，以每层向里缩进 4 个空格的方式输出，输出结果为：

​    i
  g
​    f
a
​    d
  c
​    b

**Example:**

- Input:

```
agxnzyimk
```

- Output:

```
Preorder: xigamknzy
Inorder: agikmnxyz
Postorder: agknmiyzx
Tree:
    z
        y
x
            n
        m
            k
    i
        g
            a
```
