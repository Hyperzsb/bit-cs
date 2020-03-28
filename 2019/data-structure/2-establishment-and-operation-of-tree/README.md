# 2. Establishment and Operation of Tree (树的建立与基本操作) 

**Description:**

程序的输入是一个表示树结构的广义表。假设树的根为 root ，其子树森林 F ＝ （ T1 ， T2 ， … ， Tn ），设与该树对应的广义表为 L ，则 L ＝（原子，子表 1 ，子表 2 ， … ，子表 n ），其中原子对应 root ，子表 i （ 1<i<=n ）对应 Ti 。例如：广义表 (a,(b,(c),(d)),(f,(g),(h ),(i))) 表示的树如图所示：

![img](http://lexue.bit.edu.cn/pluginfile.php/212397/mod_programming/intro/zhong1.jpg)



程序的输出为树的层次结构、树的度以及各种度的结点个数。

在输出树的层次结构时，先输出根结点，然后依次输出各个子树，每个子树向里缩进 4 个空格，如：针对上图表示的树，输出的内容应为：

a

  b

​    c

​    d

  f

​    g

​    h

​    i

Degree of tree: 3

Number of nodes of degree 0: 5

Number of nodes of degree 1: 0

Number of nodes of degree 2: 2

Number of nodes of degree 3: 1

**Example:**

- Input:

```
(a,(b),(c,(d),(e,(g),(h)),(f)))
```

- Output:

```
a
    b
    c
        d
        e
            g
            h
        f
Degree of tree: 3
Number of nodes of degree 0: 5
Number of nodes of degree 1: 0
Number of nodes of degree 2: 2
Number of nodes of degree 3: 1
```
