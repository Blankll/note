# Handler

使用异步任务AsyncTask

- Android是一个单线程模型的多线程操作系统
- 主线程更新ui,耗时操作在子线程中执行

异步任务中需要重写的方法

- doInBackground
- onPostExecute
- onPreExcute(非必须)
- onProgressUpdate(非必须)

异步任务中的三个泛型

- prams

- progress

- reesult

Handler:

- 在启动的线程中发送消息
- 在主线程中获取,处理消息
- 子线程中不能更新ui

Handler的主要作用:

- 合理调度安排信息和ruannable对象,使他们在将来的摸个点上执行
- 将一个动作放入消息队列中,使其在非当前线程执行