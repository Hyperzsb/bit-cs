# 内存监视

**Description:**

Windows的实验:

Windows设计一个内存监视器，要求：

实时地显示当前系统中内存的使用情况，包括系统地址空间的布局，物理内存的使用情况；

实时显示实验二进程控制(ParentProcess.exe)的虚拟地址空间布局和工作集信息 

相关的系统调用：GetSystemInfo, VirtualQueryEx,VirtualAlloc, GetPerformanceInfo, GlobalMemoryStatusEx ...

Linux实验：

用top命令查看系统，子命令P、T、M

用ps -A查看所有进程，找到ProcessParent的pid

用top -p pid查看ProcessParent程序的情况；

用pmap -d pid查看ProcessParent的内存使用情况

