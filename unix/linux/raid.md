# raid

## 在Ubuntu上构建raid5

mdadm

```bash
sudo mdadm -Cv /dev/md0 -a yes -n 4 -l 5 /dev/sdb /dev/sdc /dev/sdd /dev/sde
```

```bash
mdadm
-a 检测设备名称
-n 指定设备数量
-l 指定raid级别
-C 创建
-v 显示过程
-f 模拟设备损坏
-r 移除设备
-Q 查看摘要信息
-D 查看详细信息
-S 停止RAID磁盘阵列
# 查看创建进度
cat /proc/mdstat
```



如果出现``/dev/sdb1: Device or resource busy``,是因为磁盘已经被挂载, 需要取消挂载在构建raid阵列

```bash
umount /dev/sdb1
```



格式化已经raid的磁盘

```bash
mkfs.ext4 /dev/md0
```

挂载raid到目录

```bash
mkdir ~/md0
mount /dev/md0 ~/md0
```

配置开机挂载

```
vim /etc/fstab

/dev/md0 /home/blank/md0 ext4 defaults 0 0 
```

