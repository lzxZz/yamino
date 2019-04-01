# 目的
完成一个自动化管理cpp项目的软件

其主要功能为,按照参数指定的内容,创建一系列的模板文件.

另外对项目进行简单的管理比如,添加类,添加单元测试等,并对应的调整cmake文件




# 使用说明

## 创建项目
```
project new (project_name) -args...
```
参数
    -i(ignore)选择忽略的部分, 包括doc, test, exmp, git, 多个参数使用逗号分割

此时默认情况下需要按照下面的文件结构来创建
```
./project_name/
    ---proejct_name     //放置源代码和头文件的部分
        --- lib.cc
        --- CMakeLists.txt
    ---example/         // 放置示例代码的地方
        ---project_name/
            ---main.cc  // 包含一个普通main的示例,输出为hello, 
        ---CMakeLists.txt
    ---srcipt/          // 放置项目使用的一些脚本,不包括测试脚本
        ---build.sh     // 简单的脚本, 用于最外层的Makefile调用,来构建项目
    ---test/            // 放置项目测试代码
        ---main.cc      // 基本的测试main函数,初始化getst
        ---test.cc      // EQ(2+2, 4)
        ---CMakeLists.txt
    ---CMakeLists.txt
    ---Makefile
    ---README.md
```

## 添加测试



### 单元测试
### 集成测试


## 添加类

