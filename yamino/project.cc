#include "project.h"

using std::string;
using std::set;
using std::map;
using std::make_pair;

namespace lzx::yamino{
namespace{

string test_main_content = R"(#include <gtest/gtest.h>

int main(int argc, char **argv){
   ::testing::InitGoogleTest(&argc,argv);
   return RUN_ALL_TESTS();
}
)";

string build_script_content = R"(#!/bin/bash

mkdir build
cd build
pwd
cmake ..
make
)";

}

   void BinaryProject::Generate() const{
      
   }

   void LibraryProject::Generate() const{
      // 生成单个的doc目录
      if (doc_){
         string doc = root_dir_ + "/" + project_name_ + "/doc";
         directories_.emplace(doc);
      }

      // 生成下列文件树
      // test/
      //    CMakeLists.txt
      //    -main.cc
      //    -[project]/
      //       -project.cc
      if (test_){
         string test = root_dir_ + "/" + project_name_ + "/test";
         string test_project = root_dir_ + "/" + project_name_ + "/test/" + project_name_ ;
         
         directories_.emplace(test);
         directories_.emplace(test_project);

         string cmake_path = test + "/CMakeLists.txt";
         string cmake_content = "cmake_minimum_required(VERSION 3.0)\n\n"
                                 "link_libraries(\n"
                                 "\tgtest\n"
                                 "\tpthread\n"
                                 "\t" + project_name_  + "\n)\n\n";
         cmake_content += "aux_source_directory(. SRCS)\n\n" 
                          "aux_source_directory(" + project_name_ + " SRCS)\n\n"
                          "add_executable(test_main ${SRCS})";

         string test_main_path = test + "/main.cc";

         files_.emplace(make_pair(cmake_path, cmake_content));
         files_.emplace(make_pair(test_main_path, test_main_content));

         string lib_test_path = test_project + "/" + project_name_ + ".cc";
         string lib_test_content = "#include <gtest/gtest.h>\n"
                                   "#include \"" + project_name_ + "/" + project_name_ + "/lib.h\"\n"
                                   "using namespace " + project_name_ + ";\n\n"
                                   "TEST(LibTest, Add) {\n"
                                   "\tEXPECT_EQ(4, Add(2,2));\n"
                                   "}";
         files_.emplace(make_pair(lib_test_path, lib_test_content));
      }
         
      // 生成example文件夹, 和空白的CMake文件
      if (example_){
         string exmp_path = root_dir_ + "/" + project_name_ + "/example";
         string exmp_cmake_path = root_dir_ + "/" + project_name_ + "/example/CMakeLists.txt";
         string exmp_cmake_content = "cmake_minimum_required(VERSION 3.0)\n\n";

         directories_.emplace(exmp_path);
         files_.emplace(make_pair(exmp_cmake_path, exmp_cmake_content));
         
      }

      // 构建项目核心目录
      // [project]/
      //    -bin/
      //       -hello/
      //          -main.cc
      //       -CMakeLists.txt
      //    -[project]/
      //       -lib.cc              // 带有project命名空间中的Add函数和void Hello函数
      //       -CMakeLists.txt
      //    CMakeLists.txt
      
      string core_path = root_dir_ + "/" + project_name_ + "/" + project_name_;
      directories_.emplace(core_path);
      if (binary_){
         string bin_path = core_path + "/bin";
         directories_.emplace(bin_path);

         string hello_path = bin_path + "/hello";
         directories_.emplace(hello_path);

         string cmake_path = bin_path + "/CMakeLists.txt";
         string cmake_content =  "cmake_minimum_required(VERSION 3.0)\n\n"
                                 "link_libraries(" + project_name_ + ")\n\n"
                                 "aux_source_directory(hello HELLO_SRCS)\n\n"
                                 "add_executable(hello ${HELLO_SRCS})";
         files_.emplace(make_pair(cmake_path, cmake_content));

         string main_path = hello_path + "/main.cc";
         string main_content =   "#include \"" + project_name_ + "/" + project_name_ + "/lib.h\"\n\n"
                                 "int main(){\n"
                                 "\t" +project_name_ + "::Hello();\n"
                                 "\treturn 0;\n"
                                 "}";
         files_.emplace(make_pair(main_path, main_content));
      }

      string project_cmake_path = core_path + "/CMakeLists.txt";
      string project_cmake_content =   "cmake_minimum_required(VERSION 3.0)\n\n"
                                       
                                       "add_subdirectory(" + project_name_ + ")\n\n";
      if (binary_){
         project_cmake_content += "add_subdirectory(bin)\n\n";
      }
      files_.emplace(make_pair(project_cmake_path, project_cmake_content));

      string lib_path = core_path + "/" + project_name_;
      directories_.emplace(lib_path);

      string lib_cmake_path = lib_path + "/CMakeLists.txt";
      string lib_cmake_content = "cmake_minimum_required(VERSION 3.0)\n\n"
                                 "aux_source_directory(. SRCS)\n\n"
                                 "add_library(" + project_name_ +  " ${SRCS})";
      files_.emplace(make_pair(lib_cmake_path, lib_cmake_content));

      string lib_src_path = lib_path + "/lib.cc";
      string lib_src_content = "#include \"" + project_name_ + "/" + project_name_ + "/lib.h\"\n"
                               "#include <iostream>\n\n"
                               "namespace " + project_name_ + " {\n"
                               "\tvoid Hello(){\n"
                               "\t\tstd::cout << \"当你凝视深渊的时候, 深渊也在凝视着你!\" << std::endl;\n\n"
                               "\t}"
                               "\tint Add(int a, int b) {\n"
                               "\t\treturn a + b;\n"
                               "\t}\n\n"
                               "}";
      files_.emplace(make_pair(lib_src_path, lib_src_content));

      string lib_head_path = lib_path + "/lib.h";
      string lib_head_content =   "namespace " + project_name_ + "{\n"
                                 "\tvoid Hello();\n\n"
                                 "\tint Add(int a, int b);\n\n"
                                 "}";
      files_.emplace(make_pair(lib_head_path, lib_head_content));

      // 构建脚本目录
      // -script/
      //    -build.sh
      string script_path = root_dir_ + "/" + project_name_ + "/script";
      directories_.emplace(script_path);

      string build_path = script_path + "/build.sh";
      files_.emplace(make_pair(build_path, build_script_content));


      // 构建makefile
      string makefile_path = root_dir_ + "/" + project_name_ + "/Makefile";
      string makefile_content = ".PHONY : build clean test\n\n"
                                 "build:\n"
	                              "\t@./script/build.sh\n\n"
                                 "clean:\n"
                                 "\t@-rm -r build\n"
                                 "test:\n"
                                 "\t@make\n"
                                 "\t@./build/test/test_main";

      files_.emplace(make_pair(makefile_path, makefile_content));

      // 构建root CMake
      string cmake_path = root_dir_ + "/" + project_name_ + "/CMakeLists.txt";
      string cmake_content =  "cmake_minimum_required(VERSION 3.0)\n\n"
                              "project(" + project_name_ +" CXX)\n\n"
                              "add_compile_options(-Wall)\n\n"
                              "include_directories(${CMAKE_SOURCE_DIR})\n\n"
                              "add_subdirectory(" + project_name_ + ")\n\n";
      if (test_){
         cmake_content += "add_subdirectory(test)\n\n";
      }
      if (example_){
         cmake_content += "add_subdirectory(example)\n\n";
      }
      

      files_.emplace(make_pair(cmake_path, cmake_content));
   }

   
}