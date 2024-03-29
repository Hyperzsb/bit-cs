# 计算机网络复习提纲

## 概述

### 计算机网络概述

1. **计算机网络的定义：**
   - Tanenbaum 的定义：Interconnected collection of autonomous computers
   - 一般的定义：A system that interconnecting multiple autonomous computers in different locations with communication equipment, trunks, and communication software (OS, protocols, etc.), for resource sharing, is so called computer network
   - 同分布式系统的区别：
     - 对于分布式系统而言，多个计算机对于用户是透明的，用户只能看到一个虚拟的计算机；是一个在网络基础之上构件的软件系统，提供了高度的一致性和透明性；Web 就是一个分布式系统
     - 对于网络而言，用户必须显式地登陆一台机器
2. **计算机网络的功能：**
   - 商业网络应用
   - 家庭网络应用：
     - Business-to-Business（B2B）：工业原料采购
     - Business-to-Comsumer（B2C）：网上购物
     - Government-to-Consumer（G2C）：电子税收
     - Consumer-to-Consumer（C2C）：二手商品交易
     - Peer-to-Peer（P2P）：文件共享
   - 移动应用
3. **计算机网络的分类：**
   - 按照地域大小分：
     - Personal Area Network（PAN）
     - Local Area Network（LAN）
     - Metropolitan Area Network（MAN）
     - Wide Area Network（WAN）：
       - 资源子网：包括主机、终端和程序等；负责信息处理
       - 通信子网：包括通信线路和交换设备等；负责信息传递和分发
   - 根据拓扑结构分：
     - 总线型
     - 环型
     - 星型
     - 混合型
4. **计算机网络的组成：**
   - 计算机网络的组成元素分为两大类：网络节点，通信链路
   - 从逻辑功能上分为：资源子网和通信子网

### Internet

1. **定义：**
   - Internet 把很多网络连接在了一起
2. **协议：**
   - 定义：为进行网络中的数据交换而建立的规则、标准或约定
   - 协议定义了在网络实体之间传递的消息格式和消息顺序，以及在消息发送和接收时执行的动作
   - 协议分层（Layering）
   - 三个要素：
     - 语法：数据与控制信息的结构或格式
     - 语义：需要发出何种控制信息，完成何种动作以及做出何种响应
     - 同步：事件实现顺序的详细说明
3. **......**

### 计算机网络的性能

1. **速率（Data Rate）：**
   - 即数据率或比特率（Bit Rate），是计算机网络中最重要的一个性能指标
   - 速率的单位是 b/s、kb/s、Mb/s、Gb/s
2. **带宽（Bandwidth）：**
   - 本来是指信号具有的频带宽度，单位是 Hz
   - 现在是指数字信道所能传送的最高数据率，单位同数据率
3. **吞吐量（Throughput）：**
   - 吞吐量是指单位时间内通过网络的数据量
   - 吞吐量受网络的带宽或网络的额定速率的影响
4. **延迟（Delay、Latency）：**
   - 发送时延
   - 传输时延
   - 处理时延
   - 排队实验
   - 数据经历的总时延就是上述四者的总和
5. **时延带宽积：**
   - 指发送端发送的第一个比特即将到达终点时，发送端已经发出了多少个比特
6. **利用率：**
   - 信道利用率指出信道有百分之几的时间是被利用的
   - 网络利用率则是全网的信道利用率的加权平均值
   - 信道利用率并非越高越好

### 计算机网络体系结构

1. **OSI 参考模型：**
   - 物理层（Physical Layer）：在物理传输介质上可靠、透明地进行比特位收发
   - 数据链路层（Data Link Layer）：在相邻节点之间可靠地传输数据帧
   - 网络层（Network Layer）：实现通信子网的控制，控制路由选择、差错控制、拥塞控制等，把分组从源地址传输到目的地址
   - 传输层（Transport Layer）：为高层用户提供可靠的端到端通信服务
   - 会话层（Session Layer）：允许不同主机上的各进程之间会话通信
   - 表示层（Presentation Layer）：为上层用户提供格式转换、编码、压缩、加密等服务
   - 应用层（Application Layer）：定义应用的框架
2. **TCP/IP 参考模型：**
   - 物理层
   - 数据链路层
   - 网络层
   - 传输层
   - 应用层：包括 OSI 模型中的会话层、表示层和应用层

## 物理层

- 物理层的主要任务为确定与传输媒体的接口的一些特性，利用传输介质实现数据传输
  - 机械特性：指明接口所用接线器的形状和尺寸、引线数目和排列、固定和锁定装置等
  - 电气特性：指明在接口电缆的各条线上出现的电压范围
  - 功能特性：指明某条线上出现的某一电平的电压表示何种意义
  - 功能特性：指明对于不同功能的各种可能事件的出现顺序
- 基本概念：
  - 码元：承载信息的基本信号单位；一个码元能够承载的信息量多少，是由码元信号所能表示的数据有效值状态个数决定的
  - 信道：信道用来表示向某一方向传送消息的媒体；一条通信线路往往包含一条发送信道和一条接收信道
  - 带宽：通常指通信信道允许通过的信号频率范围，体现为传输信道的最高频率和最低频率之差，单位是 Hz
  - 基带信号：即基本频带信号；来自信源的信号；基带传输
  - 带通信号：基带信号经过载波调制后的信号；通带传输
- 波特率（Baud Rate）和比特率（Bit Rate）：
  - 波特是信号传输率（又称为调制速率或码元速率）的单位
  - 波特率：是线路上单位时间内传送的波形个数，即单位时间信号波形变化的次数
  - 比特率
  - 比特率和波特率的关系：
- 奈奎斯特定律（Nyquist Theory）：
  - 在无噪声的情况下
  - 带宽为 $H$ 的理想信道的最大波特率为 $Baud_{max}=2H$
  - 最大数据传输率为 $Bit_{max}=2H\log_2V$
- 香农定律（Shannon Theory）：
  - 把奈奎斯特定律扩展到有噪声的信道上
  - 带宽为 $H$，信噪比为 $S/N$ 的一般信道的最大数据传输率为 $Bit_{max}=H\log_2(1+S/N)$
  - 信噪比同分贝的转换关系为 $10\log_{10}(S/N)=x$ dB
- 传输介质：
  - 双绞线：屏蔽和非屏蔽
  - 同轴电缆：阻抗不同
  - 光纤：单模和多模
  - 无线传输介质：无线电、微波和红外等；卫星传输
- 编码与调制：
  - 编码：将数字数据转换为数字信号的过程
  - 解码：将编码后的数字信号还原成数字数据的过程
  - 调制：将数字数据转换成模拟信号的过程
    - 调幅（AM）：移幅键控法（ASK）
    - 调频（FM）：移频键控法（FSK）
    - 调相（PM）：移相键控法（PSK）
  - 解调：将调制后的模拟信号还原为数字数据的过程
- 编码方式：
  - 归零制：正脉冲
  - 不归零制：正电平代表1，负电平代表0
  - 曼彻斯特编码：:book:
  - 差分曼彻斯特编码：:book:
- 信道复用技术：:book:
  - 频分复用（FDM）
  - 时分复用（TDM）
  - 波分复用（WDM）
  - 码分复用（CDM）

## 数据链路层

### 概述

- 要完成的功能：
  - 向网络层提供一个定义良好的接口
  - 处理传输错误
  - 调节数据流，确保慢速的接收方不会被快速的发送方淹没
- 连接方式：
  - 点对点连接
  - 多点连接（广播）
- 向网络层提供的服务：
  - 无确认的无连接服务
  - 有确认的无连接服务
  - 有确认的有连接服务

### 分帧



### 错误检测和恢复



### 停等协议



### 滑动窗口协议



### HDLC 和 PPP



## MAC子层

### 媒体访问控制



### 局域网



### 以太网



### 无线局域网



### 扩展以太网和交换以太网

- 不同层之间使用不同的设备实现互连：
  - 物理层：传递电信号，使用中继器（Repeater）和集线器（Hub）
  - 数据链路层：传递帧，使用网桥（Bridge）和交换机（Switch）
  - 网络层：传递包，使用路由器
  - 传输层及以上：传递消息，使用网关（Gateway）
- 集线器：
  - 工作在物理层上
  - 一个集线器或一组集线器具有一个广播域和一个冲突域
  - 需要共享带宽
  - 不能支持不同速率或不同类型的 LAN
- 网桥：
  - 工作在数据链路层上
  - 连接两个或多个 LAN 并在这些网络之间转发帧
  - 每个 LAN 都有独立的冲突域
  - 工作原理：网桥转换了位于 MAC 子层之上的 LLC 子层中的帧内容
  - 由网桥互连而成的 LAN 被称为扩展局域网
- 交换机：
  - 连接主机或共享介质
  - 具有独立的交通道路
  - 全双工
  - 无碰撞
  - 每一个网段具有独立的冲突域和全局的广播域
- 学习网桥：
  - 工作在混杂模式下
  - 通过后向学习法可以知道所有目标地址对应的端口
  - 入境帧的转发过程：
    - 如果去往目的地址的端口与源端口相同，则丢弃该帧
    - 如果去往目的地址的端口与源端口地址不同，则转发该帧到目标端口
    - 如果目标端口未知，则使用泛洪法，将该帧发往除了源端口之外的所有端口
  - 直通式交换（Cut-Through Switching）：在完整一帧被接收之前、仅仅是看到了 MAC 地址就开始转发工作
  - 在任何情况下，网桥都不能查看帧的内部，以及了解帧携带的是否是一个 IP 数据包，因为这与网桥的处理毫不相干，而且违反了协议分层原则
- 生成树网桥：
  - 简单的学习算法在泛洪时会造成循环
  - 让网桥之间相互通信，得到生成树，在得到树之后，所有的转发工作将根据树的结构进行
  - 网桥根据自己的 MAC 地址生成标识符，网桥之间选择具有最低标识符的网桥作为生成树的根（Root Bridge）
  - 算法的具体流程 :book:

### VLAN

- 虚拟局域网（Virtual Local Area Network）
- 不被地理位置的分割而限制，是一种逻辑上的成组
- VLAN 是在交换机上通过软件配置而实现的
- 使用 VLAN 的意义：
  - 分离的广播域
  - 更好的安全性
  - 更便于管理：
    - 在主机移动时不需要更改 IP 地址
    - 可以无视地理位置的限制
    - 有均衡的带宽
- 不同 VLAN 之间的主机想要通信则必须使用路由器
- 每一个 VLAN 都是一个由一个或多个交换机组成的广播域
- VLAN 的种类：
  - 基于交换机端口的：最常见的方式
  - 基于协议的
  - 基于 MAC 层的
  - 基于网络层的
  - 使用多播分组的
  - 使用应用分组的
  - 使用规则分组的
- VLAN Trunk：
  - Trunk 是一个介于一个或多个以太网交换机之间的点对点的连接
  - Trunk 在单一链路之上携带了多个 VLAN 的交通
  - Trunk 允许你在整个网络上扩展 VLAN
  - VLAN Tagging：
    - 用于标记一条链路中不同 VLAN 的流量
    - 当一个帧需要被一个交换机转发给其它交换机时，标签将被自动插入以太网帧中
    - 由于 VLAN 对于主机是透明的，在转发给主机之前，标签需要被交换机移除
  - VTP：
    - VLAN Trunking Protocol
    - VTP 减小了管理和监控 VLAN 的复杂度
    - VTP 允许 VLAN 使用混合的介质来组合

## 网络层

### 网络层设计问题

- 网络层的职责：

  - 主机到主机的传输
  - 通过路由器和交换机路由数据包

- 网络层设计目标：

  - 向上提供的服务应该独立于路由器技术
  - 应该向传输层屏蔽路由器的数量、类型和拓扑关系
  - 传输层可用的网络地址应该有一个统一编址方案（甚至可以跨越 LAN 和 WAN）

- 关于网络服务类型的争论：

  - 提供无连接的服务：数据报交换（Datagram Switching）

    - 每一个数据包都会被独立对待
    - 数据包可能会乱序到达
    - 没有初始化和 VC 标识的必要
    - 使用源地址和目的地址进行路由转发
    - 路由器中没有维护端到端的连接信息

  - 提供面向连接的服务：虚电路交换（Virtual Circuit Switching）

    - 每一个路由器需要在虚电路表（Virtual Circuit Table），也称转发表（Forwarding Table）中维护每一对通信的状态
    - 包在传输过程中会携带虚电路号（Virtaul Circuit Number）作为唯一标识：同一 VC 在传输的不同阶段会有不同的虚电路号

  - 两者的对比：

    |       问题       |                数据报网络                |               虚电路网络               |
    | :--------------: | :--------------------------------------: | :------------------------------------: |
    |     电路建立     |                  不需要                  |                  需要                  |
    |       寻址       |     每个包使用完整的源地址和目的地址     |         每个包使用简短的 VC 号         |
    |     状态信息     |           路由器不维护状态信息           |      路由器维护每个连接的状态信息      |
    |     路由方式     |           每个数据包被单独路由           | 建立 VC 时选择路由，所有包都遵循该路由 |
    | 路由器失效的影响 | 除了在路由器失效时丢失的包，没有其他影响 |      经过失效路由器的 VC 都将中断      |
    |     服务质量     |                 很难保证                 |                容易保证                |
    |     拥塞控制     |                 很难实施                 |                容易实施                |

- 管理路由器并做出路由选择的算法称为路由算法（Routing Algorithm）

### 路由算法

1. **概述：**
   - 对于 VC 来说，只有在新建立 VC 时，才需要进行路由选择，也称为会话路由（Session Routing）
   - 路由（Routing）和转发（Forwarding）：
     - 路由：对使用哪一条路径做出决策；负责生成和更新路由表
     - 转发：当一个数据包到达时采取什么动作；在路由表中查找该数据包所对应的出境线路
   - 路由算法的设计要求：
     - 正确性
     - 简单性
     - 鲁棒性：可以抵抗网络环境中硬件或软件的失效
     - 稳定性：能够达到平衡，并且保持平衡状态；应当收敛迅速
     - 公平性
     - 有效性
   - 路由算法的分类：
     - 非自适应算法（Non-Adaptive Algorithm）：
       - 不会根据当前测量或估计的流量和拓扑结构，来调整它们的路由决策
       - 所有路由是预先在离线情况下算好的，并在网络启动时下载到路由器中的
       - 也称为静态路由（Static Routing）
       - 无法响应故障
     - 自适应算法（Adaptive Algorithm）：
       - 会改变它们的路由决策以反映出拓扑结构的变化，通常也会反映出流量的变化
       - 也称为动态路由（Dynamic Routing）
       - 有中心化、隔离和分布式算法三类
   - 汇集树（Sink Tree）：
     - 从所有源到一个指定目标的最优路径的集合构成了一颗以目标节点为根的树
     - 汇集树不一定是唯一的，有可能存在具有相同路径长度的其他汇集树
   - 路由算法分类：
     - 静态算法：
       - 最短路路由算法（Shortest Path Routing）
       - Flooding 路由算法
       - 基于流的路由算法（Flow Based Routing）
     - 动态算法：
       - 距离向量路由算法（Distance Vector Routing）
       - 链路状态路由算法（Link State Routing）
       - 层次路由算法（Hierarchical Routing）
2. **Dijsktra 算法：**
   - 算法过程：:book:
   - 特点：
     - 非自适应算法
3. **Flooding 算法：**
   - 算法过程：:book:
   - 特点：
     - 非自适应算法
     - 不需要网络信息
     - 每一个入境包将被转发给所有邻居（发方除外）
     - 具有较好的鲁棒性
   - 问题：
     - 在网络中产生大量重复数据包；采用跳计数器（Hop Counter）解决这一问题
     - 循环
     - 广播风暴
4. **距离向量路由算法（Distance Vector Routing）：**
   - 算法过程：:book:

   - 特点：
     - 分布式路由算法
     - 是 RIP、IGRP 和 EIGRP 路由算法的基础
     - 好消息传得快，坏消息传得慢：“Count to infinity”称之为“慢收敛”，解决方式：
       - 有限计数：用有限数代表无穷大（RIP协议采用16）
       - Split horizon：避免消息传递中的回路，不传播回路信息
       - Poisoned Reverse：传播回路信息，但是标记为无穷远
5. **链路状态路由算法（Link State Routing）：**
   - 已经取代距离向量算法，常用的有 IS-IS 或 OSPF
   - 使用 Dijsktra 算法
   - 步骤：
     - 检查所有邻居：发送一个 Hello 包给所有端到端的网络线，用于发现周围的邻居
     - 测试所有邻居的路程（开销）：发送一个 ECHO 包给所有邻居，用以测试开销（round-trip time、traffic load、line bandwitdh）。测试开销时，不能仅仅凭借时间花费的多少来评价距离，还需要考虑包的排队时间，否则会造成不平衡和抖动
     - 构建状态数据结构，包含所有刚刚获知的链路信息
     - 使用泛洪方法分发状态结构信息到所有路由器，并接收来自所有其他路由器的信息，每个路由器维护整个网络的完整拓扑结构
     - 计算出到每个其他路由器的最短路径
   - 在这种算法中，LAN 结构经常被当作一个路由来看待
   - 数据包中包含的内容：
     - 发送者 ID
     - 序列号（Sequence）
     - 年龄（Age）
     - 邻居列表和对应的开销
   - 何时触发 Flooding：
     - 拓扑结构变化
     - 配置变化
     - 周期性触发
6. **层次路由算法（Hierarchical Routing）：**
   - 随着网络规模的增长，路由器的路由表也随之增长，为每个其他的路由器维护路由表是不现实的
   - 在分层路由中，路由器被划分成区域（Region），每个路由器知道如何将数据包路由到自己所在的区域内的目标地址，但对于其他区域的内部结构毫不知情；将每个网络当作一个独立的区域，一个网络中的路由器不必知道其他网络的拓扑结构
   - 选择较好（不一定最好）的路由
   - 对于一个节点数为 $N$ 的网络，最优的层数是 $\ln{N}$ 个，每个路由器所需 的路由表项是 $e\ln{N}$ 个
   - 由于分层路由而导致的平均路径长度实际增长非常小，通常是可以接受的

### 拥塞控制

1. **概述**：
   - 当数据量达到数据链路承载能力时，会遇到拥塞崩溃（Congestion Collapse）吞吐量会急剧下降；出现高延迟和高丢失
   - 拥塞控制和流量控制
     - 拥塞控制的任务是确保网络能够承载所有到达的流量，这是一个全局性的问题
     - 流量控制只与特定的发送方和特定的接收方之间的点到点流量有关
     - 但是两个问题的最好处理方式都是迫使主机慢下来
   - 反馈类型：
     - 显式反馈：路由器明确向各端发送拥塞状态信息
     - 隐式反馈：各端通过数据包的延迟和丢失判断拥塞是否出现
2. **方法：**
   - 端到端拥塞控制：采用隐式反馈
   - 网络协助拥塞控制：采用显式反馈
3. **控制方法：**
   - 基于数据窗口的方法：TCP
   - 基于数据率的方法：ATM
4. **评价标准：**
   - 效率
   - 公平性
   - 分布性
5. **解决方式：**
   - 增加资源：增加多少？在什么地方增加？
     - 使用更快的链路
     - 增加额外的链路
   - 减少网络请求：
     - 告知发送端减少流量的发送
     - 拒绝某些用户的服务请求
     - 减少某些或全部用户的服务
     - 指定使用计划以实现负载均衡
6. **解决机制**：
   - 开环方法：
     - 阻止拥塞的发生而不是修正
     - 不利用运行时的系统反馈
   - 闭环方法：
     - 利用系统运行时的系统反馈
     - 闭环方法的基本原则：
       - 监视网络系统以发现何时何地发生了拥塞（丢包率、队列长度、超时重传次数、平均延迟）
       - 将相关信息发送给可以采取措施的地方
       - 调整系统行为以修正拥塞
7. **虚电路网络中的拥塞控制：**
   - 原则：在建立 VC 时，就已经确保拥塞可以被避免
   - 准入控制（Admission Control）：除非网络可以携带额外流量而不会变得拥塞，否则不再建立新的 VC
   - 选择另外的路径
   - 在建立 VC 前协商链路质量
8. **数据报网络中的拥塞控制：**
   - 抑制包（Choke Packet）：
     - 通知拥塞发送方的最直接方式是直接告诉发送方
     - 路由器选择一个被拥塞的数据包，给该包的源主机返回一个抑制包，在抑制包头添加标记
     - 源主机收到抑制包后，需要按照要求减少发送给指定目标的流量
   - 显示拥塞通知（Explict Congestion Notification，ECN）
   - 逐跳后压（Hop-by-Hop Choke Packet）：让抑制包在沿途的每一跳都发挥作用，而不仅是在源主机收到抑制包后从源主机开始减少流量
9. **负载脱落（Load Shedding）：**
   - 当其他方法都无法消除拥塞时，可以使用这个杀手锏
   - 指当路由器因为来不及处理数据包而面临被这些数据包淹没的危险时，就将它们丢弃
   - 策略：
     - 葡萄酒策略（Wine Policy）：对于文件传输，旧的数据包价值要高于新的数据包
     - 牛奶策略（Mile Policy）：对于流媒体，新的数据包价值要高于旧的数据包
   - 随机早检测（Random Early Detection，RED）：在路由器缓冲区耗尽之前就开始丢弃数据包

### IP

1. **IP 数据报格式：**

   - 数据报格式：

     <img src="/Users/hyperzsb/Library/Application Support/typora-user-images/image-20210614204344141.png" alt="image-20210614204344141" style="zoom:50%;" />

   - 版本（Version）：数据报属于哪个版本的 IP 协议

   - 头长度（Head Length）：由于头的长度不固定，该字段说明了头到底有多长（以）；该字段的最小值为5，表明头没有可选项；最大值为15，即头的最大长度为60字节，选项字段长度最长40字节

   - 区分服务（Differentiated Services）：也称为服务类型（Type of Service），用来区分不同的服务种类；最后两位用来显示拥塞通知信息

   - 总长度（Total Length）：头和数据的长度，最大长度是65535

   - 标识（Identification）：让目标主机确定一个新到达的分段属于哪一个数据报。同一个数据报的所有段包含同样的标识值

   - 标志（Flags）：共三位

     - 第一位未使用
     - DF（Don't Fragment）：是一条针对路由器的命令，不允许路由器分割该数据报
     - MF（More Fragment）：除了最后一个段外，其他所有段都必须设置这一位。用于告知接收方什么时候一个数据报的所有分段都已经到达了

   - 分段偏移量（Fragment Offset）：指明了该段在当前数据报中的位置；除了最后一个段，其他所有的段长必须是8字节的整数倍；由于该字段有13位，所以每个数据报最多有8192个段

   - 生存期（Time to Live）：用于限制数据包生存周期的计数器，最大值为255；在每一跳上，该计数器必须被递减，而且，当数据包在一台路由器上排队时间较长时，该计数器必须多倍递减；当它递减到0时，数据包就被丢弃

   - 协议（Protocol）：指明了该将它交给哪个传输进程

   - 头校验和（Header Checksum）：所有的16位（半字）累加起来，然后再取结果的补码，这样的目的是到达数据包的头校验和计算结果应该为0；在每一跳必须重新计算头校验和，因为有字段发生了改变

   - 源 IP 地址（Source IP Address）

   - 目的 IP 地址（Destination IP Address）

   - 选项（Options）：提供一种途径，允许后续版本协议包含一些原设计中没有出现的信息，以便实验人员尝试新的想法、避免为那些不常使用的信息分配头字段

2. **IP 地址：**

   - 32位地址；点分十进制表示法
   - 前缀（Prefix）：
     - 每个32位地址由高位的可变长网络和低位的主机两部分数据组成；同一网络上的所有主机，其地址的网络值是相同的，意味着一个网络对应一块连续的地址空间，这块地址空间就称为地址的前缀
     - 子网掩码（Subnet Mask）：
       - 1对应网络地址
       - 0对应主机地址
       - 子网掩码无需匹配字节边界
       - 可以使用非连续的子网掩码，但是会造成网络管理更困难
   - 子网：
     - Internet 域名和地址分配机构（Internet Corporation for Assigned Names and Number，ICANN）：一次性把部分空间授权给各区域机构，这些机构再把 IP 地址发放给 ISP 和其他公司；管理 DNS；分配域名
     - 在网络外部，子网的划分是不可见的
     - 路由聚合（Route Aggregation）：把多个小前缀的地址块合并成一个大前缀的地址块
     - 最长匹配前缀（Longest Matching Prefix）：前缀允许重叠，规则是数据包按最具体路由方向发送，即具有最少 IP 地址
   - 分类寻址（Classful Addressing）：
     - A 类：0+7位网络地址+24位主机地址（0～127）；128个网络，每个网络1600万台主机
     - B 类：10+14位网络地址+16位主机地址（128～191）；16384个网络，每个网络65536台主机
     - C 类：110+21位网络地址+8位主机地址（192～223）；200万个网络，每个网络256台主机
     - D 类：1110+组播地址（Multicast）（224～239）；多播地址只能当作目标地址，而不能作为源地址
     - E 类：1111+保留地址（240～255）
     - 分类地址的目的：
       - 可以根据区域和需要分配地址
       - 提高可伸缩性
       - 地址相近的主机来自于同一个子网，便于路由转发
       - 便于加入新的主机，而无需更新路由器
     - 分类地址的问题：
       - 不同类型的网络数量差异很大
       - 不同类型的网络被使用的差异很大：B 类已经快被耗尽而 C 类基本没有被使用
       - 骨干路由器路由表的增长
   - 特殊地址：
     - 本机地址：网络号全0，主机号全0
     - 本地网络的主机地址：网络号全0，主机号任意；用于访问本网络下的主机
     - 本地网络广播地址：网络号全1，主机号全1
     - 远程网络广播地址：网络号任意，主机号全1
     - 回环网络地址：127.xxx.xxx.xxx；用于回环测试，发送到该地址的数据包并没有被真正放到线路上，而是被当作入境数据包一样在本地处理
   - IP 地址的层次结构：
     - 两级层次结构：网络地址（Net）和主机地址（Host）
     - 优点：路由器只需为每一个网络对应一个入口，而无需为每一台主机对应一个入口
   - 子网划分（Subnetting）：
     - 如果只采用分类地址划分，会导致不灵活和浪费等问题
     - 将已有的网络域划分成子网，同时外界只需要知道主网的地址
     - 这就构成了一个三级层次结构：
       - 站点地址（Site）：即二级层次结构中的网络地址
       - 子网地址（Subnet）：即二级层次结构中的主机地址的高地址部分
       - 主机地址（Host）：即二级层次结构中的主机地址的低地址部分
     - 在网络外部，路由器根据网络地址进行路由
     - 在网络内部，路由器根据子网地址进行路由
   - 无类域间路由（Classless Inter-Domain Routing，CIDR）：
     - 使用 CIDR，一个组织可以混合多个 C 类地址组成一个大的地址空间
     - 称之为超网（Supernetting）
     - 优势：
       - 在分配不同大小的地址空间时具有很大的灵活性
       - 允许分配连续的地址块（地址的数量必须是2的幂次）
       - 便于管理
       - 便于地址聚合，减小路由表大小
   - 网络地址转换（Network Address Translation，NAT）：
     - NAT 是一种解决 IP 地址耗尽的快速方法
     - 只给每一个组织分配一个 IP 地址：
       - 在组织内部，每一个主机都有用于内部通信的唯一的 IP 地址（局域网 IP）
       - 当内部主机向外发送消息时，地址转换发挥作用，所有数据包都使用相同的 IP 地址，不同的端口号
     - 为了实现 NAT，有三部分的网络地址被用做局域网地址：
       - 10.0.0.0～10.255.255.255/8（16777216个主机）
       - 172.16.0.0~172.31.255.255/12（1048576个主机）
       - 192.168.0.0～192.168.255.255/16（65536个主机）
     - 地址转换过程：:book:
     - 优势：
       - 没有必要分配一定范围的 IP 地址，只需要一个公共域的 IP 地址即可
       - 16 位的端口号允许多达60000个主机共享一个 IP 地址
       - 可以在不更换内部地址的情况下更改外部地址
       - 内部设备对于外部来说是不可见的
     - 劣势：
       - 如果两个主机都位于 NAT 之后，在它们之间建立连接是困难的
       - NAT 是有争议的：
         - 违反了 IP 的结构模型：IP 结构声明每个 IP 地址均唯一标识了世界上的一台主机
         - 打破了端到端的连接模型
         - 将无连接网络改变成了一个面向连接的特有形式：NAT 盒子必须维护连接必要的信息
         - 违反了最基本的协议分层规则：下层协议不应当对上层协议做出任何假设
   
3. **IP 包路由和转发：**

   - 直接交付和间接交付：
     - 源和目的主机连接在同一个子网中，则将 IP 分组封装到数据链路层的帧中，利用数据链路层功能直接发送给目的主机
     - 源和目的主机不在同一个子网中，则将 IP 分组发送下一跳路由器，有路由器转发给目的主机
   - 路由方式：
     - 下一跳路由（Next-Hop Routing）
     - 特定网络路由（Network-Specific Routing）
     - 特定主机路由（Host-Specific Routing）
   - 路由表的结构：:book:
   - 路由表的构造：:book:

4. **Internet 消息控制协议（Internet Message Control Protocol，ICMP）：**

   - 用于在路由器和主机之间交流 IP 状态和错误信息
   - ICMP 数据被当作 IP 协议的负载而传输
   - ICMP 协议格式：:book:
   - ICMP 协议数据类型：
     - 目的地不可达（Destination Unreachable，3）：
       - 当路由器不能定位一个目标
       - 目的地址发现指定的上层协议不可用
       - DF 标志被设置但是只有分段才能继续传输
     - 源抑制（Source Quench，4）：
       - 用于抑制那些发送太多数据包的主机
       - 很少使用；拥塞控制主要交由传输层来完成
     - 回显（Echo，8）和回显应答（Echo Replay，0）：
       - 用来判断一个指定的目标是否可达，是否还活着
       - 被 Ping 工具用于探测 Internet 上是否存在某一台特定主机
     - 超时（Time Exceeded，11）：
       - 往往预示着数据包进入了路由循环，或者计时器的超时值设置得太小；也有可能是主机在超时前没有收到所有的分段
       - 用于 Traceroute 工具

5. **地址解析协议（Address Resolution Protocol，ARP）：**

   - ARP 或 RARP 协议实现了 IP 地址（32位）和 MAC 地址（48位）之间的转换
   - 数据链路层硬件网卡根据 MAC 地址来发送和接收帧
   - ARP 提供一种动态的映射关系
   - ARP 协议工作流程：:book:
   - ARP 应用举例：:book:

6. **自治系统（Autonomous System，AS）：**

   - 全球互联网由许多互相连接的自治系统构成：
     - 在内部，一个组织可以使用自己的内部路由算法，也称域内路由算法（Intradomain Routing、Interior Routing）；域内路由协议也被称为内部网关协议（Interior Gateway Protocol）
     - 在外部，需要在独立运营商网络之间使用域间路由算法（Interdomain Routing、Exterior Routing）；域间路由协议也被称为外部网关协议（Exterior Gateway Protocol）
   - 自治系统：在单一管理者管理之下的一群网络或路由器
   - 内部网关协议有：
     - RIP
     - OSPF
     - IGRP

7. **路由信息协议（Routing Information Protocol，RIP）：**

   - 基于距离向量算法
   - 使用 UDP
   - RIP 协议工作流程：:book:

8. **开放最短路径优先（Open Shortest Path First，OSPF）：**

   - 基于链路状态算法（Dijkstra）
   - 通过泛洪的方式通知
   - 优点：
     - 安全：每个 OSPF 消息都被认证，且使用 TCP 连接
     - 允许使用多个等价最短路，也称为等价成本多路径（Equal Cost MultiPath，ECMP），以便实现负载均衡
     - 使用层次化结构
     - 支持 IP 隧道连接

9. **边界网关协议（Border Gateway Protocol，BGP）：**

   - BGP 考虑了很多经济、政治和其他因素，需要使用多种路由策略
   - BGP 给每个自治系统提供了：
     - 维护邻居自治系统中子网的可达性信息
     - 传递自己的可达性信息给所有外部路由
   - 使用 TCP
   - 具体实现和策略：:book:

10. **IPv6：**

    - IPv4 的局限性：

      - 地址空间耗尽
      - 尽最大努力的服务是不够的
      - 商业化互联网

    - 128位地址

    - IPv6 协议头：

      <img src="/Users/hyperzsb/Library/Application Support/typora-user-images/image-20210615175527269.png" alt="image-20210615175527269" style="zoom:50%;" />

    - 协议头分析：:book:

    - IPv6 地址表示法：:book:

      - 传统表示法
      - 缩写

    - IPv6 和 IPv4 的地址转换：:book:

## 传输层

### 传输层概述

- 传输层协议负责提供进程到进程（端到端）的通信，依赖于网络层的服务
- 在传输层内，完成这项工作的硬件和（或）软件称为传输实体（Transport Entity），而一个传输实体向另一个传输实体发送的消息称为传输协议数据单元（Transport Protocol Data Unit，TPDU），现在多用段（Segment）来表示该消息
- 向上层服务提供有效、高效且可靠的服务；传输层承担了把上层服务与技术、设计和各种缺陷隔离的关键作用
- 有两种服务类型：
  - 面向连接的服务类型：一般需要三个过程
    - 建立连接
    - 数据传输
    - 释放连接
  - 无连接的服务类型
- 传输服务原语：
  - 监听（Listen）：阻塞，直到某个进程试图与其连接；没有消息发出
  - 连接（Connect）：主动尝试建立一个连接；发出 Connection Request 消息
  - 发送（Send）：发送信息；发出数据消息
  - 接受（Receive）：阻塞，直到接收到一个数据消息；没有消息发出
  - 断开连接（Disconnect）：请求释放连接；发出 Disconnection Request 消息
- 注意帧（Frame）、包（Packet）和段（Segment）的嵌套关系：数据链路层 $\rightarrow$ 网络层 $\rightarrow$ 传输层
- Berkeley 套接字：
  - 地址分配原语：
    - Socket：创建一个新的通信端点
    - Bind：将套接字与一个本地地址关联
  - 服务端原语：
    - Listen：声明愿意接受连接，并给出队列长度
    - Accept：被动创建一个连接
    - Send & Receive：通过连接发送和接受一些数据
    - Close：释放连接
  - 客户端原语：
    - Connect：主动创建一个连接
    - Send & Receive：通过连接发送和接受一些数据
    - Close：释放连接

### 传输协议的要素

1. **地址分配：**
   - 当一个进程希望与另一个远程进程建立连接时，需要使用传输服务访问点（Transport Service Access Point，TSAP）来表示对方的地址端点
   - 如何获取到 TSAP：
     - 静态的 TSAP 地址：通常用于关键服务（Web 服务器、邮件服务器等），不适用于用户进程（存在时间短，地址数量有限）
     - 端口映射：根据服务名称对应到相应端口
     - 初始连接协议（Initial Connection Protocol）：避免多个等待的服务器进程浪费资源。将多个 TSAP 交给一个进程管理，当有某个 TSAP 接收到连接请求，派生出相应的服务进程
   - 地址分配方式：
     - 分级地址：例如 IP + 端口，但是将 TSAP 同主机绑定
     - 平坦地址空间：TSAP 不同主机绑定
2. **连接建立：**
   - 存在问题：延迟重复（Delayed Duplicates）；一些不完善的解决方法：
     - 一次性传输地址：缺点是需要无限的地址；且首次建立连接会异常困难
     - 连接标识符：缺点是需要维护一张标识符表
   - 解决方式：设置一种机制杀死已经过期却仍在网络环境中传播的包
     - 限制网络设计
     - 给每个包设置跳计数器
     - 给每个包设置时间戳
   - Tomlinson 方法：
     - 两个相同标号的 TPDU 在同一时间段内不会重复出现；永远不要在生命周期 T 内为带有x的数据包重用序列号 x
     - 需要主机设置一个日时钟（time-of-day clock），即使主机停止时钟也不停止
     - 初始序列号：根据时钟低位设置序列号
     - 确保初始序列号合法：禁止区域 :question:
     - 确定初始序列号：三次握手（Three-way handshake）
       - 没有一种延迟包的组合可以导致一次错误的连接
       - 协议过程：:book:
3. **连接释放：**
   - 非对称释放：
     - 任意一方释放连接
     - 可能会导致数据丢失
   - 对称释放：
     - 双方均需要同意释放连接
     - 会产生两军对垒问题（Two-army Problem）：:book:
   - 三次握手 + 计时器：
     - 绝大部份情况是正确的
     - 但是在极端情况下可能导致半开（Half-open）的连接
4. **流控制和缓冲：**
   - 问题：在有很多连接的情况下，主机可能没有足够的资源来为每一个连接分配一个固定数量的窗口来执行一个合适的滑动窗口协议
   - 解决方式：
     - 动态缓冲区分配
     - 发送者和接受者协商 TPDU 的数量
       - 可能会有潜在的死锁：:book:
   - 还有一种基于网络承载容量而不是接收端缓冲容量的机制：:book:
5. **多路复用：**
   - 多路复用（Multiplexing）：假设一个主机只有一个网络地址可用，该机器的所有传输连接都必须使用这个地址使，就需要多路复用
   - 逆向多路复用（Inverse Multiplexing）：假设一个主机有多条网络路径可用，且用户所需的带宽和可靠性比其中任何一条路径所能提供的都多，则需要把一个连接的上的流量分摊到多条网络路径
6. **崩溃恢复：**
   - 从网络和路由器的崩溃中恢复是没有问题的
   - 但是从主机崩溃中恢复是有困难的，无论怎样修改协议都会有协议失败的情况
   - 在事件不同步的基本规则下，即单独的事件一个接着一个发生，而不是同时发生，那么主机的崩溃和恢复就无法做到对上层透明
   - 从第 N 层崩溃中的恢复工作只能由第 N+1 层完成，并且仅当高层保留了问题发生前的足够状态信息才有可能恢复

### TCP 和 UDP 的基本概念

- UDP：
  - 低层次，无连接
  - 无可靠性保证
- TCP：
  - 面向连接
  - 可靠性保证
  - 不如 UDP 高效
- IP 端口：16位（0～65535）
  - 可以认为端口就是 TSAP
  - 互联网数字分配机构（Internet Assigned Numbers Authority，IANA）维护了一张端口分配表
  - 0～1023：被 IANA 控制和分配
  - 1024～49151：为方便起见，IANA 为相关服务注册和控制这部分端口
  - 49152～65535：动态端口

### UDP

- 用户数据包协议（User Datagram Protocol，UDP）

- 尽最大努力交付的协议： 不可靠、无连接；在数据传送前没有进行发送者和接受者之间的握手；每一个数据包都是独立处理的

- 仅仅提供多路复用和解多路复用

- 经常被用于流媒体（具有错误容忍和数据率敏感等特性）；也用于 DNS 和 SNMP 等上层协议

- 协议头格式：

  - 固定大小：8B

  - 源端口（2B）、目的端口（2B）、数据包长度（2B）、校验和（2B）

  - 结构：

    <img src="/Users/hyperzsb/Library/Application Support/typora-user-images/image-20210610223942484.png" alt="image-20210610223942484" style="zoom:50%;" />

  - 数据包长度包括8B的 UDP 头长度，最小8B，最大65515B（由于 IP 协议的限制）:question: ；UDP 包长度 = IP 包长度 - IP 头长度

  - 计算校验和时需要一个假定的 IP 头；计算校验和流程 :book:

- 校验和在 UDP 中是可选的

- UDP 做了什么：

  - 只是提供了一个与 IP 协议的接口，并在此接口上增加通过端口号复用多个进程的功能
  - 可选的端到端错误检测功能

- UDP 没做什么：

  - 流量控制
  - 拥塞控制
  - 重传机制

### TCP

1. **TCP 概述：**

   - 传输控制协议（Transmission Control Protocol，TCP）
   - 在两个端点之间建立了虚拟的连接来发送数据（可靠的，按序到达的）
   - TCP 做了什么：
     - 面向连接的点对点通信
     - 多路复用和解多路复用
     - 全双工通信
     - 字节流传输：一个 TCP 连接就是一个字节流，而不是消息流，端到端之间不保留消息边界
     - 可靠的按序到达的数据传输
     - 流控制
     - 拥塞控制
   - 同 UDP 相同，TCP 使用了端口标识最终的目的地
   - 同 UDP 不同，TCP 使用连接作为数据传输的基础抽象；类似于虚拟链路（Virtual Circuit）；用一对 IP-端口对来表示，四元组（源地址，源端口，目的地址，目的端口）
   - 用于支持可靠通信的机制：
     - 校验和
     - 序列号：每一个段都有一个32位序列号；序列号从一个随机生成的数开始；
     - 重传机制

2. **TCP 段头：**

   - 起始部分是一个固定格式的20字节头，之后可能会有选项数据（Options and padding）

   - 选项之后是最多65495字节的数据

   - 没有任何数据的 TCP 段也是合法的，通常被用做确认和控制消息

   - 结构图：

     <img src="/Users/hyperzsb/Library/Application Support/typora-user-images/image-20210610223821383.png" alt="image-20210610223821383" style="zoom:50%;" />

   - 源端口、目的端口

   - 序列号：

   - 确认号：指定的是下一个期待的字节，而不是已经正确接受到的最后一个字节

   - 头长度：指明 TCP 头包含多少个32位的字（选项字段是变长的）

   - 控制字段：

     - URG（Urgent pointer is valid）：若该位被置1，则使用了紧急指针，这个指针从当前序号开始找到紧急数据的字节偏移量；这是设置中断消息的另一种方式；很少被使用
     - ACK（Acknowledgement is valid）：若该位被置1，则表示确认消息是有效的；若为0，确认字段信息可以被忽略
     - PSH（Request for push）：若该位被置1，则说明这是被推送的数据，接收端一旦接受到该消息后立即将数据递交给应用程序，而不是将其放入缓冲区直到缓冲区满为止，提高效率
     - RST（Reset the connection）：用于重置一个已经变得混乱的连接（由于主机崩溃等原因）
     - SYN（Synchronize sequence numbers）：用于建立连接的过程（根据 ACK 位的不同可以表示 CONNECTION REQUEST 和 CONNECTION ACCEPTED）
     - FIN（Terminate the connection）：用于释放一个连接；SYN 和 FIN 都有序号，避免两者冲突而出现混乱和错误

   - 窗口大小：指定了从被确认的字节算起可以发送多少个字节（为0是合法的）

   - 校验和：提供了额外的可靠性；校验头、数据和概念性伪头；在 TCP 中是强制使用的

   - 选项：针对头信息覆盖不到的方面；最多40字节；例如指定主机愿意接受的最大段长（Maximum Segment Size，MSS），所有主机都要求能够接受536+20=556字节的 TCP 段（至少）；窗口尺度（Window Scale）；时间戳（Timestamp），用于作为序列号的逻辑补充，防止序号回绕（Protection Against Wrapped Sequence numbers，PAWS）

3. **TCP 连接建立：**

   - 三次握手（Three-way Handshaking）
     - 主机 A 主动连接主机 B
     - A 向 B 发送：SYN (SEQ = x)（一个 SYN 段不能携带数据，但是它将消耗一个序列号）
     - B 向 A 回复：SYN (SEQ = y, ACK = x + 1)（同样的，一个 SYN + ACK 段不能携带数据，但是它将消耗一个序列号）
     - A 向 B 发送：(SEQ = x + 1, ACK = y + 1)（一个 ACK 段如果不携带任何数据，则不消耗序列号）

4. **TCP 连接释放：**

   - 两个端点彼此独立释放
   - 四次握手（Four-way Handshaking）
     - 主机 A 首先断开连接
     - A 向 B 发送：FIN (SEQ = x, ACK = y)（一个 FIN 段如果不携带数据，将消耗一个序列号）
     - B 向 A 回复：(SEQ = y, ACK = x + 1)（一个 ACK 段如果不携带任何数据，则不消耗序列号）
     - B 向 A 发送：FIN (SEQ = z, ACK = x + 1)（一个 FIN 段如果不携带数据，将消耗一个序列号）
     - A 向 B 发送：(SEQ = x + 1, ACK = z + 1)（一个 ACK 段如果不携带任何数据，则不消耗序列号）
   - 为了避免两军对垒问题，需要用到计时器。如果在两倍于最大数据包生存期内，针对 FIN 的相应没有出现，则 FIN 发送端直接释放连接，另一方最终也会发觉没有人在监听而超时

5. **TCP 连接管理模型：**:memo:

   - 共11种状态：

     - CLOSED：没有活跃的连接或者挂起
     - LISTEN：服务器等待入境呼叫
     - SYN RCVD：到达一个连接请求，等待 ACK
     - SYN SENT：应用已经启动了，打开一个连接
     - ESTABLISHED：连接已经建立，开始传送数据
     - FIN WAIT1：应用没有数据要发了
     - FIN WAIT2：另一端同意释放连接
     - TIME WAIT：等待所有数据包寿终正寝
     - CLOSING：两端同时试图关闭连接
     - CLOSE WAIT：另一端已经发起关闭连接
     - LAST ACK：等待所有数据包寿终正寝

   - 状态转换图：

     <img src="/Users/hyperzsb/Library/Application Support/typora-user-images/image-20210611100328806.png" alt="image-20210611100328806" style="zoom:50%;" />

6. **TCP 滑动窗口：**

   - 错误控制、流控制和拥塞控制：
     - 错误控制：回复和消除包丢失带来的影响
     - 流控制：防止发送者发送消息的速度超出接受者的接收速度
     - 拥塞控制：防止发送者堵塞网络
     - 在 TCP 中，这三种控制方式被混合成了滑动窗口方法
   - 不可靠 IP 包传输服务：
     - 优点：快速；节约资源
     - 缺点：丢包、包损坏、延迟、包重复、乱序；发送者可能比接收者更快地发送消息
   - TCP 提供的可靠性：
     - 校验和：检测内容错误
     - 序列号：检测序列错误；重复被忽略、乱序被调整、丢失被重传
     - 确认号
     - 超时：检测丢失错误
     - 重传：修复各类错误
   - ACK 被用来进行错误控制、流控制和拥塞控制
   - 包到达时可能是乱序的，但是这些包会被暂存起来，在提交给上层进程时，保证包的顺序
   - TCP 在每个端点有两个滑动窗口：
     - 发送窗口：发送窗口是可收缩的
     - 接收窗口
   - 接受者在 ACK 中需要指出目前可用窗口的大小
   - 具体过程：:book:
   - 发送端可以用窗口探测（Window Probe）方法来强制接收端宣告下一个期望的字节和窗口大小，来防止死锁的发生
   - 低能窗口综合症（Silly Window Syndrome）：
     - 由发送者造成：
       - 原因：发送者产生消息非常慢，以至于每次只能产生1字节的数据发送给接收者
       - 解决方式：:book:
         - 采用 Nagle 算法：缓冲到足够多的数据再发送
     - 由接收者造成：
       - 原因：接收者消耗数据非常慢，以至于每次只能空出1字节的窗口给发送者发送数据
       - 解决方式：:book:
         - 使用 Clark 的解决方式：强制接收端等待一段时间，直到缓冲区足够大
         - 针对低带宽的应用场景，可以使用延迟确认（Delayed Acknowledgement）技术来提高性能
   - 累计确认（Cumulative Acknowledgement）：可以减少因丢弃数据包而造成的性能浪费

7. **TCP 计时器管理：**

   - 超时时间的设置：
     - 对于 TCP 来说，RTT 具有更大的可变性
     - 太短：会导致大量不必要的重传
     - 太长：性能会受到影响

   - RTT 的测量：
     - Jacobson 算法
     - 使用公式：$SRTT=\alpha \times SRTT + (1- \alpha) \times RTT$，$RTT$ 是新测量的值，$\alpha$ 的典型值为0.875
   - 往返时间变化：:memo:

8. **TCP 拥塞控制：**

   - TCP 假定一个段的丢失是网络拥塞造成的。如果丢失的原因是拥塞，重传并不能解决问题，相反会加剧这一问题。此时，网络需要告知发送端放慢速度

   - TCP 的拥塞控制机制被部署于发送端

   - TCP 维护一个拥塞窗口（Congestion Window），并使用加法递增乘法递减（Additive Increase Multiplicative Decrease，AIMD）规则来控制窗口大小

   - 拥塞窗口：

     - 指明了在连接上可以发送的数据最大数量
     - 是对于网络承载能力的一个评估
     - 拥塞窗口的大小等于流控制窗口大小和拥塞窗口大小的最小值
     - 流控制窗口大小由接收端声明
     - 拥塞窗口大小由网络反馈改变

   - 拥塞检测：

     - 由发送方进行，发生了一下事件：
       - 重传超时
       - 收到多（3）个重复的 ACK 包而不管是否超时：进行快重传（Fast Retransmit）

   - TCP 的拥塞控制由两部分决定：

     - 拥塞窗口（cwnd）
     - 慢启动阈值（slow-start threshold value，ssthresh）：最初的值是$2^{16}-1$

   - TCP 的拥塞控制工作在两个阶段：

     - 慢启动阶段（$cwnd < ssthresh$）
     - 拥塞避免阶段（$cwnd \ge ssthresh$）

   - 慢启动：

     - 在第一次连接时或连接超时时
     - 设置初始 cwnd 为1
     - 每受到一个 cwnd 的 ACK 时，cwnd递增1（其结果就是每一轮后 cwnd 会翻倍）

   - 拥塞避免：

     - 当达到 ssthresh 时，cwnd 将开始线性增长：即当且仅当所有 cwnd 的段都被确认时，cwnd递增1（每接收一个包，增加 1/cwnd 个大小）
     - 所谓拥塞避免并不能完全避免拥塞发生，只是说在拥塞避免阶段把拥塞窗口控制为按线性规律增长，使网络比较不容易出现拥塞

   - 当出现丢包后：

     - ssthresh 被设置为之前的一半，整个慢启动过程重新开始；TCP Tahoe

   - 快速恢复（Fast Recovery）：TCP Reno

     - 只有第一次启动或者发生超时时才进入真正的慢启动
     - 当前的拥塞窗口将遵循一种锯齿（Sawtooth）模式

   - 状态转换图：

     <img src="/Users/hyperzsb/Library/Application Support/typora-user-images/image-20210611162106849.png" alt="image-20210611162106849" style="zoom:50%;" />

## 应用层

### C/S 和 P2P 应用架构

1. **C/S 架构**：
   - 特点：服务端和客户端
   - HTTP、FTP、Web services
   - 局限性：
     - 可伸缩性很难实现
     - 单点失效会导致整个服务的失效
     - 需要管理
     - 网络边缘有未使用的资源
2. **P2P 架构：**
   - 所有端点既是服务端也是客户端；任意主机之间可以相互通信
   - 无中心化数据源
   - 高度可伸缩但是难以管理
   - 每个加入端在增加需求的同时也增加了服务能力

### DNS

- 一个分层的、基于域名的命名方案和一个分布式数据库系统，用于将主机名和电子邮件目的地映射到 IP 地址
- 映射方式：
  - 本地文件（Local File）
  - 中心服务器（Central Server）：
    - 存储了所有的域名 IP 对
    - 所有请求都会发送给中心服务器
    - 缺点：
      - 单点失效问题
      - 高流量
      - 远距离中心化数据库
      - 单点更新
      - 无法伸缩
  - 域名系统（Domain Name System）：部署在层次结构的多个名称服务器上的分布式数据库

- DNS 由三部分组成：
  - 名字空间：
  - 服务器：
  - 解析器：
- Fully Qualified Domain Name（FQDN）
- 域名结构是一个树结构，叶子结点就是单台计算机
- 域（Zones）和授权（Delegation）
  - 将一个域授权给一个法人实体，即给一个域设置一个名称服务器
  - 授权之后，名称服务器可以独立地管理主机名和下级域名
  - 权力又父节点传递给字节点
- 一个单独的名称服务器可以配置多个域
- DNS 服务器的层次结构：
  - 根服务器
  - 顶级域名（Top-Level Domain，TLD）服务器：负责一般的顶级域名和所有国家的顶级域名
  - 权威 DNS 服务器：组织的 DNS 服务器，为组织的服务器提供权威的主机名到 IP 的映射；可以被组织或者服务提供商维护
- 每一个节点都知道根服务器的地址
- 每一个节点都知道其直接子节点的地址
- 使用 DNS 的两个部分：
  - 本地 DNS 服务器（Local DNS Server）：
    - 又称为默认名称服务器（Default Name Server）
    - 靠近于终端主机位置
    - 每个服务提供商或组织都会有一个
    - 每一个 DNS 解析请求将被首先发给本地 DNS 服务器
  - 主机上的解析软件
- 三种查询方式：
  - 递归式：服务器将向外围递归查询，直到返回一个值或“Not Found”
  - 迭代式：返回“我不知道，但是可以问它”
  - 混合式：本地 DNS 服务器进行递归，根 DNS 服务器进行迭代
- 缓存

### FTP

- 文件传输协议（File Transfer Protocol，FTP）
- FTP 使用分离的两个 TCP 连接来传输文件：
  - 控制连接：用于在两个主机之间传输控制信息，诸如用户标识、口令、改变远程目录命令、Put、Get 以及其他相关命令；控制连接贯穿于整个用户会话期间，对应的服务端口号是21
  - 数据连接：用于准确地传输一个文件。数据连接是非持久的，即针对会话中的每一次文件传输都需要建立一个新的数据连接。数据连接对应的服务端口是20
- 因为 FTP 使用一个分离的控制连接，所以也称 FTP 的控制信息是“带外”传送的
- 匿名 FTP：
  - 某些场合提供一组公共文件
  - 用户名：annoymous；口令：guest 或邮箱
  - 限制：只允许用户使用命令的一个子集

### E-Mail 和 SMTP/POP/IMAP

- 三个主要组成部分：
  - 用户端代理（User Agent，UA）：是用户与电子邮件系统的接口，具有撰写、回复、转发、显示和处理功能
  - 邮件传输代理（Mail Transfer Agent，MTA）：是电子邮件系统的核心组件，其功能是发送和接收邮件，并向发送人报告邮件传送情况
    - 为了发邮件，系统必须有一个客户端 MTA
    - 为了收邮件，系统必须有一个服务端 MTA
    - 定义客户端 MTA 和服务端 MTA 的协议是 SMTP
  - 邮件访问代理（Mail Access Agent，MAA）：从服务器拉取消息

- 一些使用场景：:book:
- Simple Mail Transfer Protocol（SMTP）：
  - 基于文本的协议
  - C/S 协议
  - 使用 TCP 端口 25 到 2525
  - 是一个 Push 协议，即只允许上传不允许下载
  - 传输的三个阶段：
    - 握手
    - 数据传输
    - 关闭连接
  - SMTP 使用坚持的 TCP
  - 使用 <Ctrl + F>.<Ctrl + F> 作为邮件内容结束
- Multipurpose Internet Mail Extensions（MIME）：
  - 用于发送非文本数据
- Post Office Protocol（POP）：
  - 本地 Email 客户端需要使用它下载邮件
  - 两个阶段：
    - 认证
    - 下载
- Internet Mail Access Protocol（IMAP）

- 基于 Web 的 Email：使用 HTTP 协议

### WWW 和 HTTP

- 统一资源定位符（Uniform Resource Locator，URL）
- 超文本传输协议（Hypertext Transfer Protocol，HTTP）：
  - 请求-响应协议
  - 无状态协议
  - C/S 模式

### DHCP

- 动态主机配置协议（Dynamic Host Configuration Protocol，DHCP）
- 动态分配和静态分配
- 客户端负责地址的更新和释放
- 优势：
  - 在有很多移动用户的场景下十分有用
  - 可以适应网络参数的变化
  - 共享一个有限的 IP 池
  - 有多种分配方式可以选择和混合
- 劣势：
  - 不安全的 UDP 传输
  - 广播消息
  - 有错误配置的风险

## 题目

- 协议所属的层次：
  - Ethernet：数据链路层
  - PPP：数据链路层
  - HDLC：数据链路层
  - ARP：网络层协议
  - DHCP：基于 UDP 的应用层协议
  - ICMP：网络层协议，直接使用 IP 协议进行数据发送
  - RIP：基于 UDP 的应用层协议
  - OSPF：网络层协议，直接用 IP 数据报传送
  - BGP：基于 TCP 的应用层协议
  - DNS：基于 UDP 的应用层协议
  - FTP：基于 TCP 的应用层协议
  - SMTP：基于 TCP 的应用层协议
  - POP：基于 TCP 的应用层协议
  - HTTP：基于 TCP 的应用层协议
