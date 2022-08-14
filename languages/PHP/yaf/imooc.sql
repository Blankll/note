-- phpMyAdmin SQL Dump
-- version 4.4.15.6
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: 2017-07-13 16:23:15
-- 服务器版本： 5.7.11-log
-- PHP Version: 7.0.7

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `imooc`
--

-- --------------------------------------------------------

--
-- 表的结构 `art`
--

CREATE TABLE IF NOT EXISTS `art` (
  `id` int(11) NOT NULL COMMENT '文章ID',
  `title` varchar(128) COLLATE utf8_unicode_ci NOT NULL COMMENT '文章标题',
  `contents` text COLLATE utf8_unicode_ci NOT NULL COMMENT '文章内容',
  `author` varchar(32) COLLATE utf8_unicode_ci NOT NULL COMMENT '作者名称',
  `cate` int(4) NOT NULL COMMENT '文章分类ID',
  `ctime` timestamp NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'create time',
  `mtime` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'modify time',
  `status` enum('delete','online','offline') COLLATE utf8_unicode_ci DEFAULT 'offline' COMMENT '是否被删除'
) ENGINE=InnoDB AUTO_INCREMENT=15 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='文章';

--
-- 转存表中的数据 `art`
--

INSERT INTO `art` (`id`, `title`, `contents`, `author`, `cate`, `ctime`, `mtime`, `status`) VALUES
(4, '测试文章标题', '12312312', 'yi', 1, '2017-05-13 14:18:00', '2017-05-13 14:18:00', 'offline'),
(5, '测试文章标题', '12312312', 'yi', 1, '2017-05-13 14:18:37', '2017-05-13 14:18:37', 'offline'),
(6, '测试文章标题', '12312312', 'yi', 1, '2017-05-13 14:18:38', '2017-05-13 14:18:38', 'offline'),
(7, '测试文章标题', '12312312', 'yi', 1, '2017-05-13 14:21:01', '2017-05-13 14:21:01', 'offline'),
(10, '测试文章标题', '12312312', 'yi', 1, '2017-05-13 14:21:20', '2017-05-13 14:21:20', 'offline'),
(14, '测试文章 testId:31801Changed444', '测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493测试内容1807888493151', 'yi1948226284152', 1, '2017-05-13 14:54:38', '2017-05-13 14:55:51', 'offline');

-- --------------------------------------------------------

--
-- 表的结构 `bill`
--

CREATE TABLE IF NOT EXISTS `bill` (
  `id` int(11) NOT NULL COMMENT '账单id',
  `itemid` int(11) NOT NULL COMMENT '商品id',
  `uid` int(11) NOT NULL COMMENT '用户id',
  `price` int(11) NOT NULL DEFAULT '0' COMMENT '商品价格，单位为分',
  `status` enum('paid','unpaid','failed','') COLLATE utf8_unicode_ci NOT NULL DEFAULT 'unpaid' COMMENT '支付状态',
  `transaction` text COLLATE utf8_unicode_ci COMMENT '交易ID',
  `ctime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
  `mtime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间',
  `ptime` timestamp NULL DEFAULT NULL COMMENT '支付时间'
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- 转存表中的数据 `bill`
--

INSERT INTO `bill` (`id`, `itemid`, `uid`, `price`, `status`, `transaction`, `ctime`, `mtime`, `ptime`) VALUES
(1, 1, 1, 10, 'paid', '9223372036854775807', '2017-07-06 14:30:13', '2017-07-06 15:02:52', '2017-07-06 15:02:52');

-- --------------------------------------------------------

--
-- 表的结构 `cate`
--

CREATE TABLE IF NOT EXISTS `cate` (
  `id` int(11) NOT NULL COMMENT '自增ID',
  `name` varchar(64) COLLATE utf8_unicode_ci NOT NULL COMMENT '类目名'
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='分类信息';

--
-- 转存表中的数据 `cate`
--

INSERT INTO `cate` (`id`, `name`) VALUES
(1, '啊哈哈哈');

-- --------------------------------------------------------

--
-- 表的结构 `item`
--

CREATE TABLE IF NOT EXISTS `item` (
  `id` int(11) NOT NULL COMMENT '商品ID',
  `name` varchar(128) COLLATE utf8_unicode_ci NOT NULL COMMENT '商品名',
  `description` text COLLATE utf8_unicode_ci NOT NULL COMMENT '商品描述',
  `price` bigint(20) NOT NULL DEFAULT '0' COMMENT '商品价格，单位为分',
  `stock` int(11) NOT NULL COMMENT '商品数量',
  `ctime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
  `etime` timestamp NOT NULL COMMENT '过期时间',
  `mtime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '修改时间'
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='商品';

--
-- 转存表中的数据 `item`
--

INSERT INTO `item` (`id`, `name`, `description`, `price`, `stock`, `ctime`, `etime`, `mtime`) VALUES
(1, '测试商品123', '商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！商品描述信息！！！', 10, 99, '2017-07-06 14:08:37', '2017-07-31 14:22:29', '2017-07-06 14:30:13');

-- --------------------------------------------------------

--
-- 表的结构 `sms_record`
--

CREATE TABLE IF NOT EXISTS `sms_record` (
  `id` int(11) NOT NULL COMMENT '主键',
  `uid` int(11) NOT NULL COMMENT '用户id',
  `contents` text COLLATE utf8_unicode_ci NOT NULL COMMENT '消息内容',
  `template` int(11) NOT NULL,
  `ctime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '发送时间'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='短信发送记录';

-- --------------------------------------------------------

--
-- 表的结构 `user`
--

CREATE TABLE IF NOT EXISTS `user` (
  `id` int(10) unsigned NOT NULL COMMENT 'user id',
  `name` varchar(64) COLLATE utf8_unicode_ci NOT NULL COMMENT 'user name',
  `pwd` varchar(32) COLLATE utf8_unicode_ci NOT NULL COMMENT 'user password',
  `email` text COLLATE utf8_unicode_ci COMMENT '用户邮箱',
  `mobile` bigint(11) DEFAULT NULL COMMENT '用户手机号',
  `reg_time` timestamp NOT NULL COMMENT 'user register time',
  `update_time` timestamp NULL DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP COMMENT 'information change time'
) ENGINE=MyISAM AUTO_INCREMENT=7 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='用户注册信息表';

--
-- 转存表中的数据 `user`
--

INSERT INTO `user` (`id`, `name`, `pwd`, `email`, `mobile`, `reg_time`, `update_time`) VALUES
(1, 'pangee', '64166e7bf41c7ada0f8c5b6e18301554', NULL, NULL, '2017-07-06 14:28:49', NULL),
(5, 'test', 'c8bb9401addc891f66b7a6f4c2e85691', NULL, NULL, '2017-07-08 16:20:02', NULL),
(4, 'apitest_uname_1300224274', '71788eccd0aaf996b569db61fb74b1d7', NULL, NULL, '2017-07-08 15:08:29', NULL),
(6, 'apitest_uname_757319156', 'cd86831cae7a1624a93e2b4fe77025ea', NULL, NULL, '2017-07-08 16:47:49', NULL);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `art`
--
ALTER TABLE `art`
  ADD PRIMARY KEY (`id`),
  ADD KEY `Title index` (`title`),
  ADD KEY `分类索引` (`cate`);

--
-- Indexes for table `bill`
--
ALTER TABLE `bill`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `cate`
--
ALTER TABLE `cate`
  ADD PRIMARY KEY (`id`),
  ADD KEY `name` (`name`);

--
-- Indexes for table `item`
--
ALTER TABLE `item`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `sms_record`
--
ALTER TABLE `sms_record`
  ADD PRIMARY KEY (`id`),
  ADD KEY `uid` (`uid`);

--
-- Indexes for table `user`
--
ALTER TABLE `user`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `id` (`id`),
  ADD UNIQUE KEY `name` (`name`) USING BTREE;

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `art`
--
ALTER TABLE `art`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '文章ID',AUTO_INCREMENT=15;
--
-- AUTO_INCREMENT for table `bill`
--
ALTER TABLE `bill`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '账单id',AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT for table `cate`
--
ALTER TABLE `cate`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '自增ID',AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT for table `item`
--
ALTER TABLE `item`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '商品ID',AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT for table `sms_record`
--
ALTER TABLE `sms_record`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '主键';
--
-- AUTO_INCREMENT for table `user`
--
ALTER TABLE `user`
  MODIFY `id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT 'user id',AUTO_INCREMENT=7;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
