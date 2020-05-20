# 1. Game Tree (博弈树) 

**Description:**

下棋属于一种博弈游戏，博弈过程可以用树（博弈树）来表示。假设游戏由两个人（ A 和 B ）玩，开始由某个人从根结点开始走，两个人轮流走棋，每次只能走一步， 下一步棋只能选择当前结点的孩子结点，谁先走到叶子结点为胜。例如，对于下图所示的博弈树，若 A 先走，可以选 f ， B 若选 h ，则 A 选 j 胜。

![tree](http://cms.bit.edu.cn/moodle/file.php?file=/142/%E8%AF%BE%E7%A8%8B%E4%B8%8B%E8%BD%BD/zhonghong/play1.gif)

编写一程序，让计算机和人下棋。当计算机走下一步时，可以根据以下情况决定下一步：

（1） 若存在可以确保取胜的一个孩子结点，则选择该结点作为下一步；

（2） 若存在多个可以确保取胜的孩子结点，则选择其中高度最小的结点作为下一步（若有多个选择，则选最左边的结点）；

（3） 若不存在可以确保取胜的一个孩子结点，则选择高度最大的孩子结点作为下一步（若有多个选择，则选最左边的结点）；

**Example:**

- Input:

```
(a,(b,(x)),(c,(d),(e,(g),(h)),(f)))
1
c
y
1
x
b
y
0
f
n
```

- Output:

```
a
b
x
c
d
e
g
h
f
Who play first(0: computer; 1: player )?
player:
computer: d
Sorry, you lost.
Continue(y/n)?
Who play first(0: computer; 1: player )?
player:
illegal move.
player:
computer: x
Sorry, you lost.
Continue(y/n)?
Who play first(0: computer; 1: player )?
computer: c
player:
Congratulate, you win.
Continue(y/n)?
```
