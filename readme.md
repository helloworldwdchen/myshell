这是一个简单的shell，用于操作系统相关知识的学习

**使用方法**

1. 确保您在linux环境下

2. 下载

    ```
    git clone https://github.com/helloworldwdchen/myshell.git
    ```

    或者下载压缩包解压

3. 编译

    进入所在目录，在命令行中输入并回车：

    ```
    make
    ```

    编译完成后在该目录下产生 `myshell`文件

4. 运行

    在命令行输入并回车：

    ```
    ./myshell
    ```

5. 输入 `help` 以获得帮助

6. 退出后，可以在目录下命令行输入 `make clean` 清除编译产生的文件



**内部函数目标：**

- [ ] cd
- [x] cls
- [ ] dir
- [ ] environ 列出所有环境变量
- [ ] echo
- [x] help
- [ ] pause 停止shell操作直到按下回车
- [x] quit

**其他目标：**

- [x] 外部函数调用
- [ ] 环境变量
- [ ] 重定向
- [x] 运行外部程序或函数后返回shell
- [x] shell包含当前路径

**开发日志**

4.16 

完成shell基本框架，能够按照 读取输入->解析输入->执行输入的步骤运行。接下来就是内部函数以及环境变量的实现。

更新文件结构

```
.
├── makefile
├── myshell.c
├── myshell.h
├── readme.md
└── utility.c
```

4.17

调整makefile，增加cls的内部函数实现