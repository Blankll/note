# linux 网络管理

- ifconfig

  > - eth0 第一块网卡(网络接口)
  > - eno1 板载网卡
  > - ens33 pci-e网卡

- 修改网络接口名称
  - 

- 查看网卡物理连接情况

  ```bash
  mii-tool eth0
  ```

- 查看网关

  ```bash
  route -n // -n 不解析主机名
  ```

  - 添加网关

    ```bash
    route add default gw <网关ip>
    route add -host <指定ip> gw <网关ip>
    route add -net <指定网段> netmask <子网掩码> gw <网关ip>
    ```

- 检测端口是否可达

  ```bash
  telnet ip port
  ```

- 数据抓取

  ```bash
  tcpdump -i any -n port 80 # 抓取所有 请求80端口的数据
  ```

  

