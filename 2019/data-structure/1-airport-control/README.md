# 1. Airport Control (飞机场调度)

**Description:**

在本实验中，需要同学们利用队列实现一个飞机场调度模拟，根据不同的输入参数得到不同的模拟结果。程序运行开始，首先需要输入以下参数：

*机场跑道数，飞机降落占用跑道时间（整数），* *飞机起飞占用跑道时间（整数）*

整个模拟的时间以分钟为单位，从 0 开始，每分钟的开始需要输入：

*该分钟要求降落飞机数，* *该分钟要求起飞飞机数*

机场调度原则是降落优先起飞，在此原则下按来的顺序排队；每驾飞机都有一个编号，要起飞飞机从 1 开始，要降落飞机从 5001 开始；每驾飞机需要等待的时间是从其提要求开始到分配跑道为止；每个跑道都有一个编号（从 1 开始），都可以用来降落和起飞，但同一时间只能被一架飞机占用，占用时间为该飞机降落（起飞）占用跑道时间。

当输入的要求降落飞机数和要求起飞飞机数都小于 0 时，表示机场关闭，不再接受新的请求，但余下没有降落（起飞）的飞机需照常进行。

模拟过程中需要随时输出以下数据：

1. 当前时间 (%4d)

2. 所有从占用变为空闲的跑道编号 （在输入降落、起飞飞机数前输出）

3. 可以降落（起飞）飞机编号（％ 04d ）、跑道编号（％ 02d ） （在输入降落、起飞飞机数后输出）

模拟结束后，程序需输出以下统计结果：

1. 模拟时间（％ 4d ）

2. 降落平均等待时间（％ 4.1f ）

3. 起飞平均等待时间（％ 4.1f ）

4. 每条跑道被占用时间（％ 4d ）

5. 跑道平均被占用的百分比（％ 4.1f ， 平均占用时间× 100/ 模拟时间）

**Example:**

- Input:

```
1 2 3
1 2
2 1
0 0
0 0
0 0
-1 -1
```

- Output:

```
Current Time:    0
airplane 5001 is ready to land on runway 01
Current Time:    1
Current Time:    2
runway 01 is free
airplane 5002 is ready to land on runway 01
Current Time:    3
Current Time:    4
runway 01 is free
airplane 5003 is ready to land on runway 01
Current Time:    5
Current Time:    6
runway 01 is free
airplane 0001 is ready to takeoff on runway 01
Current Time:    7
Current Time:    8
Current Time:    9
runway 01 is free
airplane 0002 is ready to takeoff on runway 01
Current Time:   10
Current Time:   11
Current Time:   12
runway 01 is free
airplane 0003 is ready to takeoff on runway 01
Current Time:   13
Current Time:   14
Current Time:   15
runway 01 is free
simulation finished
simulation time:   15
average waiting time of landing:  1.3
average waiting time of takeoff:  8.7
runway 01 busy time:   15
runway average busy time percentage: 100.0%
```

