# MHA

MHA(Master High Availability)



## MHA 主从切换

1. 运行过程中对master进行监控
2. 发现master故障之后尝试使用sh的方式保存mster的二进制日志
3. 从多个slave中选举出最新的数据库作为备选主服务器，可以认为设置不参与选举的slave服务器
4. 在备选主服务器和其他slave服务器之间同步差异数据
5. 应用从原master上保存的二进制日志(当发生诸如主键重复等错误时会使MHA停止进行故障转移)
6. 提升备选master为新的master，虚拟ip切换
7. slave节点修改为新master的slave节点



<font color="red">MHA 支持GTID复制</font>

<font color="red">MMM不支持GTID复制</font>



### 操作步骤

1. 配置集群内的所有主机SSH免认证登陆

2. MHA-node软件包和MHA-manaer软件包

   ```bash
   yum -y install perl-Config-Tiny.noarch perl-Time-HiRes.x86_64 perl-Parallel-ForkManager perl-Log-Dispatch-Perl.noarch perl-DBD-MySQL ncftp
   ```

3. 建立主从复制集群

4. 配置mha管理节点

5. 使用masterha_check_ssh 和master_check_repl对配置进行检验