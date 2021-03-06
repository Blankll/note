# 计算机操作系统第一章

## 关键术语

1. 地址寄存器

   ``存储器地址寄存器[Memory Address  Register]``:用于确定下一次读/写的地址

   ``存储器缓冲寄存器[Memory Buffer Register]``:存放要写入存储器的数据或从存储器中读取的数据

   ``输入输出地址寄存器[I/O Address Register]``:用于确定一个特定的输入/输出设备

   ``输入输出缓冲寄存器[I/O Buffer Register]``:用于在输入/输出模块和处理器间交换数据

2. 辅助寄存器

3. 高速缓存

4. 中央处理单元``CPU``

5. 芯片多处理器

6. 数据寄存器

7. 直接内存存取

8. 命中率

9. 输入/输出

10. 指令

11. 指令周期

12. 指令寄存器

13. 中断  中断可在主程序中的任何位置而非仅在一条特定指令处发生

    ``程序中断``在某些条件下由指令执行的结果产生，如算数溢出，除数为0，试图执行一条非法机器指令及访问用户不允许的存储位置

    ``时钟中断``  由处理器内部的计时器产生，允许操作系统以一定的规律执行函数

    ``I/O中断``   由I/O控制器产生，用于发信号通知一个操作的正常完成或各种错误条件

    ``硬件失效中断``   由诸如掉电或存储器奇偶校验错误之类的故障产生

14. 中断驱动I/O

15. I/O模块

16. 局部性

17. 分级存储体系

18. 内存

19. 多核

20. 多处理器

21. 处理器

22. 程序计数器

23. 可编程I/O

24. 寄存器

25. 辅存

26. 空间局部性

27. 栈

28. 堆栈结构

29. 栈指针

30. 系统总线``System bus``

31. 时间局部性



## pv

  P原语（阻塞原语）操作的动作是： 

​      (1)sem减1； 

​      (2)若sem减1后仍大于或等于零，则进程继续执行； 

​      (3)若sem减1后小于零，则该进程被阻塞后进入与该信号相对应的队列中，然后转进程调度。 

   V原语（唤醒原语）操作的动作是： 

​      (1)sem加1； 

​      (2)若相加结果大于零，则进程继续执行； 

​      (3)若相加结果小于或等于零，则从该信号的等待队列中唤醒一等待进程，然后再返回原进程继续执行或转进程调度。 



- 如果sem大于0，说明没有等待进程。 

- 如果sem小于或等于0，说明有等待进程队列，因为V操作释放了一个资源，就需要唤醒一个等待进程获得该资源 