# 1. n维超立方体

**Description:**

n维超立方体是在n维空间中对三维空间立方体的类比，下图便是一个4维超立方体在三维空间中的投影及该立方体在三维空间的展开图

![四维超立方体及其展开图](http://lexue.bit.edu.cn/pluginfile.php/321835/mod_programming/intro/%E5%9B%9B%E7%BB%B4%E8%B6%85%E7%AB%8B%E6%96%B9%E4%BD%93%E5%8F%8A%E5%85%B6%E5%B1%95%E5%BC%80%E5%9B%BE.jpg)

给超立方体的各顶点编号后，就可以按照一定规则写出其邻接矩阵。请同学们根据下图寻找规律，对于给定的顶点编号序列，写出对应的超立方体的邻接矩阵。

![低维立方体示意图](http://lexue.bit.edu.cn/pluginfile.php/321835/mod_programming/intro/%E4%BD%8E%E7%BB%B4%E7%AB%8B%E6%96%B9%E4%BD%93%E7%A4%BA%E6%84%8F%E5%9B%BE.png)

**Input:**

维数n，顶点的编号序列a（0<=n<=7）

**Output:**

对应的超立方体的邻接矩阵（顶点顺序需与a一致）

**Example:**

- Input:

```
2
0 1 2 3
```

- Output:

```
0 1 1 0
1 0 0 1
1 0 0 1
0 1 1 0
```

