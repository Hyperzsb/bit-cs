# 2. Establishment and Operation of Binary Tree (二叉树的建立与基本操作) 

**Description:**

编写程序实现二叉树的如下操作：
1) 建立二叉链表
2) 二叉树的先序、中序、后序遍历
3) 求二叉树的叶子结点个数
4) 将二叉树中所有结点的左、右子树相互交换

**Input:**

按完全二叉树的层次关系给出二叉树的遍历序列（#表示虚结点，数据结点为单一字符）。

**Output:**

二叉树的凹入表示

二叉树的先序序列、中序序列、后序序列

二叉树叶子结点个数

左、右子树相互交换后的二叉树的凹入表示

左、右子树相互交换后的二叉树的先序序列、中序序列、后序序列。

在输出凹入表示的二叉树时，先输出根结点，然后依次输出左右子树，上下层结点之间相隔 3 个空格。

**Example:**

- Input:

```
abc#de
```

- Output:

```
BiTree
a
    b
        d
    c
        e
pre_sequence  : abdce
in_sequence   : bdaec
post_sequence : dbeca
Number of leaf: 2
BiTree swapped
a
    c
        e
    b
        d
pre_sequence  : acebd
in_sequence   : ceadb
post_sequence : ecdba
```
