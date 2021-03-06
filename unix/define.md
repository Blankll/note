# C语言中的宏

## 宏替换的基础知识

\#define 宏名称 字符串

\#define 宏名称(形参列表) 字符串

允许宏带有参数,在宏定义中的参数称为形式参数,在宏调用中的参数称为实际参数

### c宏展开的几个注意事项

- 每次宏展开的结果都会被重复扫描,直到没有任何可展开的宏为止
- 每展开一个宏,都会记住这次展开,在这个宏展开的结果及其后续展开中,不再对相同的宏做展开
- 带参数的宏,先对参数做展开,除非宏定义中包含#或##
  - \# 表示将后续标识转换为字符串
  - \##表示将两个标识符连接成一个标识符
  - 注意参数展开的结果中即使有逗号(,), 也不视为参数的分隔符
- 如果宏定义中带有参数,而代码中出现同样标识符时没有参数,不视为宏
- \#与##不能同时在一个宏中使用

