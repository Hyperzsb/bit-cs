# 3. Things Happened in the Company (公司里的那点事儿) 

**Description:**

对于一间公司来说，它成立之时所做的第一件事恐怕就是任命CEO了。之后，CEO就会开始雇用员工，也会有员工离职去别的公司。假设公司中的每一个员工（包括 CEO在内）都可以直接雇用新的员工，而公司中的所有员工（包括CEO）也都可能会跳槽离开，则某公司在成立一段时间之后的的组织结构如图1：

![图1](http://lexue.bit.edu.cn/pluginfile.php/212406/mod_programming/intro/%E5%85%AC%E5%8F%B8%E9%82%A3%E7%82%B9%E4%BA%8B1.JPG)

图1

VonNeumann是公司的CEO，他直接雇用了两个人，分别是Tanenbaum和Dijkstra。在公司中，某员工的几个直接下属，他们的职位是由员工们的工龄决定的，在图中即表现为从从左至右职位越来越低，譬如Tanenbaum的职位就比Dijkstra要高。

当一个员工雇用了新的下属时，该下属在该员工雇佣的所有下属中，职位是最低的。假设VonNeumann又雇用了Shannon，则VonNeumann的三名下属职位从高到低分别是Tanenbaum、Dijkstra和Shannon。

当公司中的员工离职，则有两种情况。若他没有雇用任何下属，则他会被从公司的组织结构中拿掉。若他有直接的下属，则他的直接下属中职位较高的人，会升职并补上缺位。而该下属若也有下属，则他的下属中职位最高的，会补上他升值后空出的位子。以此类推，直到某个尚未雇用下属的员工升职。

假设图1中的Tanenbaum跳槽离开了，则Stallings会补上它的位置，而Knuth会补上Stallings的位置。图2展示了变化后的结果：(1) VonNeumann雇用了Shannon，(2) Tanenbaum跳槽。

![图2](http://lexue.bit.edu.cn/pluginfile.php/212406/mod_programming/intro/%E5%85%AC%E5%8F%B8%E9%82%A3%E7%82%B9%E4%BA%8B2.JPG)

图2

**Input:**

输入的第一行是 CEO 的姓名。题目中所有的人名的长度都在2-20之间，且由大小写字母、数字和短线（减号）组成。每个名字都包含至少一个大写和一个小写字母。

在第一行后会有很多行内容，他们由如下的规则构成：

- [老员工] hires [新员工]
- fire [老员工]
- print

[老员工] 是已经在公司工作的人的名字，而[新员工]是即将被雇用的员工的名字。以上三种规则组成的内容可能会按照任何顺序出现。但公司中会至少有一名员工（CEO），且公司的规模最大不会超过 1000 人。

**Output:**

对于每一个打印命令，按照如下规则输出当前公司的结构信息：

- 每一行包含一个人名

- 第一行是CEO的名字，从第一列开始

- 图3形式的结果，

  ![图3](http://lexue.bit.edu.cn/pluginfile.php/212406/mod_programming/intro/%E5%85%AC%E5%8F%B8%E9%82%A3%E7%82%B9%E4%BA%8B3.JPG)

  图3

  会输出为图4

  ![图4](http://lexue.bit.edu.cn/pluginfile.php/212406/mod_programming/intro/%E5%85%AC%E5%8F%B8%E9%82%A3%E7%82%B9%E4%BA%8B4.JPG)

  图4

- 在每次print之后，输出一行60个字符的减号，整个输出中没有任何空行。

**Example:**

- Input:

```
VonNeumann
VonNeumann hires Tanenbaum
VonNeumann hires Dijkstra
Tanenbaum hires Stallings
Tanenbaum hires Silberschatz
Stallings hires Knuth
Stallings hires Hamming
Stallings hires Huffman
print
VonNeumann hires Shannon
fire Tanenbaum
print
fire Silberschatz
fire VonNeumann
print
```

- Output:

```
VonNeumann
+Tanenbaum
++Stallings
+++Knuth
+++Hamming
+++Huffman
++Silberschatz
+Dijkstra
------------------------------------------------------------
VonNeumann
+Stallings
++Knuth
+++Hamming
+++Huffman
++Silberschatz
+Dijkstra
+Shannon
------------------------------------------------------------
Stallings
+Knuth
++Hamming
+++Huffman
+Dijkstra
+Shannon
------------------------------------------------------------
```
