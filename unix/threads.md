# threads

## 互斥锁

### 使用方法

- 创建互斥锁 ``pthread_mutex_t mutex``
- 初始化锁 ``pthread_mutex_init(&mutex, NULL)``
- 在操作共享资源前加锁``pthread_mutex_lock(&mutex)``
- 操作共享资源``临界区``
- 在操作共享资源结束之后释放锁``pthread_mutex_unlock(&mutex)``
-  临界区尽量小

## 读写锁

- 阻塞线程 通过使用while等进行忙等待

## 条件变量

- 不是锁,在不满足条件时可以阻塞线程,消耗比忙等待更小
- 与互斥锁配合使用 ``互斥锁保护一块共享数据 条件变量可以进行阻塞``

## 信号量

- 信号量的资源个数不为一

- 信号量既可以做进程的同步,也可以呢做线程的同步

- 信号量类型 sem_t sem ``加强版的互斥锁``

- 主要函数

  ```c
  // 信号量类型
  sem__t sem;
  /**
   * 初始化信号量
   * sem 信号量类型的变量
   * pshared 类型 线程还是进程
   * 0 线程同步
   * 1 进程同步
   * int value 资源数量
   */
  sem_init(sem_t* sem, int pshared, unsigned int value);
  // 销毁信号量
  sem_destroy(sem_t *sem);
  // 加锁
  sem_wait(sem_t* sem);
  // 尝试加锁, 加锁失败不等待,直接返回
  sem_trywait(sem_t* sem);
  // 限时尝试加锁
  sem_timedwait(sem_t*sem, time);
  // 解锁++
  sem_post(sem_t* sem);
  ```

  

