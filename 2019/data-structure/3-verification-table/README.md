# 3. Verification Table (验证表) 

**Description:**

应用中有时需要验证来自不同地方的两个表的信息是否一致。本实验编写具有如下功能的程序：输入两个学生记录表LIST1，LIST2，在表LIST2中找出所有没有在表LIST1中出现的学生记录（设表LIST1为基础数据表，非空）。

每一个学生记录元素包含两个数据项：学号(整数)，姓名；

如果学生记录表LIST2中的记录都包含在LIST1中，则输出the records of LIST2 are all in the LIST1.

如果学生记录表LIST2中的存在学号，姓名不能与表LIST1完全匹配的记录，则输出 学号（%8d）姓名（%15s）is not in LIST1.

如果LIST2为空表，则输出the LIST2 is NULL.

**Example:**

- Input:

```
5
20120001 zhangli
20120002 wanglei
20120003 duyang
20120004 lixin
20120005 liufan
3
20120002 wanglei
20120001 zhangli
20120004 lixin
```

- Output:

```
the records of LIST2 are all in the LIST1.
```
