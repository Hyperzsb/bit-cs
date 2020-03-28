# 4. Breadth First Traversal of Graphs (图的广度优先遍历) 

**Description:**

本实验实现邻接表表示下无向图的广度优先遍历。

**Input:**

图的顶点序列和边序列(顶点序列以*为结束标志，边序列以-1,-1为结束标志)。

**Output:**

图的邻接表和广度优先遍历序列。

**Example:**

- Input:

```
a
b
c
d
e
f
*
0,1
0,4
1,4
1,5
2,3
2,5
3,5
-1,-1
```

- Output:

```
the ALGraph is
a 4 1
b 5 4 0
c 5 3
d 5 2
e 1 0
f 3 2 1
the Breadth-First-Seacrh list:aebfdc
```
