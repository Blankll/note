# threads

## 互斥锁使用步骤

- 创建互斥锁 ``pthread_mutex_t mutex``
- 初始化锁 ``pthread_mutex_init(&mutex, NULL)``
- 在操作共享资源前加锁``pthread_mutex_lock(&mutex)``
- 操作共享资源``临界区``
- 在操作共享资源结束之后释放锁``pthread_mutex_unlock(&mutex)``
-  临界区尽量小

