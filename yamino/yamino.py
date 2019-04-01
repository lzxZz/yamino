#!/usr/bin/env python3

'''
目前只支持创建lib项目, 同时会自动带上bin目录
创建的项目结构如下
project/
   -doc/
   -example/
   -script/
      build.sh
   -test/
      main.cc
      CMakeLists.txt
   -project/
      -bin/
         CMakeLists.txt
      -project/
         lib.cc
         CMakeLists.txt
      CMakeLists.txt
   .gitignore
   MakeFile
   CMakeLists.txt
   README.md
'''

import sys;
import os;
import yamino.string

basic_dirs = ["doc", "example", "script", "tests"]

def CreateDirectories(directory):
   cmd = "mkdir -p " + directory
   os.system(cmd);
   print("创建文件夹" + directory)

def CreateFileWithContent(file, content):
   cmd =  'echo "' + content + '" > ' + file
   os.system(cmd)
   print("创建文件" + file);

def InitGit(subdir):
   cmd = "cd " + subdir + " && git init"
   os.system(cmd)
   CreateFileWithContent(subdir + "/.gitignore", yamino.string.gitIgnoreContent);
   print("初始化git")
def GetSubDirString(directory):
   return 'add_subdirectory(' + directory + ')'
def main(argc, argv):
   print("当你在凝视深渊的时候, 深渊也在凝视你!\n\n\n");
   if (argc < 3):
      print("参数错误")
      print("调用帮助函数") # TODO
      exit(-1)
   
   cmd_type = argv[1]      # 获取命令
   project = argv[2]       # 获取要创建的项目的名称 TODO,对于.后期添加特殊处理


   # 检测根目录是否存在, 防止覆盖
   if (yamino.string.FileExist(project)):
      print("项目目录 >> " + project + " << 已经存在,请重新指定")
      exit(-1)
   CreateDirectories(project)
   
   # 读取参数,判断是否有需要省略的文件夹
   ignore = False
   ignore_list = []
   if (argc >= 5): #可能存在-i选项
      if (argv[3] == "-i"):
         ignore = True
         for str in argv[4].split(','):
            ignore_list.append(str);
   
   print(ignore_list)

   cmakeSubDir = []
   cmakeSubDir.append(project)
   cmakeVersion = "cmake_minimum_required(VERSION 3.0)"


   if not "git" in ignore_list:
      InitGit(project);
   
   if not "doc" in ignore_list:
      CreateDirectories(project + "/" + "doc")
   
   if not "test" in ignore_list:
      CreateDirectories(project + "/" + "test")
      # 添加基本main.cc, cmake文件, test.cc
      testMain_path = project + "/test/main.cc"
      test_cmake_path = project + "/test/CMakeLists.txt"
      CreateFileWithContent(testMain_path, yamino.string.testMainContent)

      testcmakeContent = cmakeVersion + "\n" + '''
         link_libraries(
            pthread  
            gtest
         )  

         aux_source_directory(. SRCS)

         add_executable(test_main ${SRCS})
         '''
      CreateFileWithContent(test_cmake_path, testcmakeContent);
      cmakeSubDir.append("test");
   
   if not "exmp" in ignore_list:
      CreateDirectories(project + "/" + "example")
      cmakeSubDir.append("example")
   # 创建构建系统文件
   script = project + "/script"
   CreateDirectories(script)
   CreateFileWithContent(script + "/build.sh", yamino.string.buildContent);

   CreateFileWithContent(project + "/README.md", "# 项目简介");
   CreateFileWithContent(project + "/Makefile", yamino.string.makefileContent);

   # 创建项目文件夹
   CreateDirectories(project + "/" + project)
   CreateDirectories(project + "/" + project + "/bin")  
   CreateDirectories(project + "/" + project + "/" + project)  

   # 创建基本文件

   # 开始构建CMake树
   cmakeVersion = "cmake_minimum_required(VERSION 3.0)"
   rootCMakeContent = cmakeVersion + "\n\n" + "project(" + project + " CXX)"
   
   for subdir in cmakeSubDir:
      rootCMakeContent += "\n\n" + GetSubDirString(subdir)
   
   
   CreateFileWithContent(project + "/CMakeLists.txt", rootCMakeContent)



   # os.system('echo "' + yamino.string.buildContent + '" > build.sh');

if __name__ == "__main__":
   argv = sys.argv
   main(len(argv), argv)