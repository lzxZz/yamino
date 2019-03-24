#include "cmd.h"
#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::vector;
namespace yamino{
    namespace {
        const string make_file_content = "\".PHONY : build clean\n\nbuild:\n\t@./scripts/build.sh\n\n\nclean:\n\t@-rm -r build\"";
        const string build_script_file_content = "\"#!/bin/bash\n\nmkdir build\ncd build\npwd\ncmake ..\nmake\"";
        const string empty_cmake_file_content = "cmake_minimum_required(VERSION 3.0)\n\n";
        
    }
    void CreateDirectories(const string &project_name){
        // proejct_name, examples, scripts, tests
        vector<string> dirs = {
            project_name,
            project_name + "/" + project_name,
            project_name + "/example",
            project_name + "/tests",
            project_name + "/scripts",
            project_name + "/docs",
        };
        for (auto line : dirs){
            const string cmd = "mkdir -p " + line;
            system(cmd.c_str());
        }
        
    }
    void CreatMakeFile(const string project){
        system(("echo " + make_file_content + " > "+ project + "/Makefile").c_str());
    }

    void CreatBuildScript(const string project){
        system(("echo " + build_script_file_content + " > "+ project + "/scripts/build.sh").c_str());
    }

    string SubDirCMakeTerm(const string dir_name){
        return "add_subdirectory(" + dir_name + ")\n\n";
    }

    void CreatCMakeFile(const string project){
        string content =empty_cmake_file_content + 
                        "\n\nproject(" + project + ")\n\n" +
                        "#如果不需要测试代码,注释下面一行\n" + 
                        SubDirCMakeTerm("tests") +
                        "#如果不需要示例代码,注释下面一行\n" + 
                        SubDirCMakeTerm("example") +
                        SubDirCMakeTerm(project); 
        std::cout << content << std::endl;
        system(("echo \"" + content + "\" > "+ project + "/CMakeLists.txt").c_str());

        system(("echo \"" + empty_cmake_file_content + "\" > "+ project + "/tests/CMakeLists.txt").c_str());
        system(("echo \"" + empty_cmake_file_content + "\" > "+ project + "/example/CMakeLists.txt").c_str());
        system(("echo \"" + empty_cmake_file_content + "\" > "+ project + "/"  + project + "/CMakeLists.txt").c_str());
    }
    void CreatReadMe(const string project){
        system(("echo \"# 项目说明\" > "+ project + "/Readnme.md").c_str());
    }
    void CreatGit(const string project){
        system(("cd " + project + " && git init").c_str());
        system(("echo \"build/\" > " + project + "/.gitignore").c_str());
    }
    void NewBinary(const string &project_name){
        CreateDirectories(project_name);
        CreatMakeFile(project_name);
        CreatBuildScript(project_name);
        CreatCMakeFile(project_name);
        CreatReadMe(project_name);
        CreatGit(project_name);
        std::cout << "项目文件夹构建成功" << std::endl;
    }   // 新建二进制项目
    void NewLibrary(){
        std::cout << "lib" << std::endl;
    }  // 新建库项目, 大型项目应该使用库项目
    void AddClass(){
        std::cout << "class" << std::endl;
    }    // 添加类
    void AddTest(){
        std::cout << "test" << std::endl;
    }     // 添加测试
}