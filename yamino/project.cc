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

}

   void BinaryProject::Generate() const{
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
                                   "#include \"" + project_name_ + "/" + project_name_ + "/lib.cc\"\n"
                                   "using namespace " + project_name_ + ";\n\n"
                                   "TEST(LibTest, Add) {\n"
                                   "\tEXPECT_EQ(4, Add(2,2));\n"
                                   "}";
         files_.emplace(make_pair(lib_test_path, lib_test_content));
      }
         
   }

   void LibraryProject::Generate() const{
      
   }
}