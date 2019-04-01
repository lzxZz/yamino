#include "builder.h"
#include "project.h"
#include <iostream>
#include <string.h>


using std::string;
using std::cerr;
using std::endl;

namespace lzx::yamino{
   

   void LinuxMaker::Generate(const Project *project){
      for (auto dir : project->Dirs()){
         string cmd = "mkdir -p " + dir;
         if (system(cmd.c_str()) != 0){
            cerr << "生成文件夹" + dir + "失败" << endl;
            cerr << "\t" << strerror(errno) << endl;
         }
      }
      for (auto iter : project->Files()){
         string cmd = "echo \'" + iter.second + "\' >" + iter.first;
         if (system(cmd.c_str()) != 0){
            cerr << "生成文件" + iter.first + "失败" << endl;
            cerr << "\t" << strerror(errno) << endl;
         }
      }
   }

   void WindowsMaker::Generate(const Project *project){
      
   }

   void Builder::ReSet(){
      project_ = nullptr;
   }
   Project *Builder::GetProject(){
      return project_; 
   }
   void BinaryBuilder::BuildTest(){}
   void BinaryBuilder::BuildProject(){}
   void BinaryBuilder::BuildExample(){}
   void BinaryBuilder::BuildScript(){}

   void LibraryBuilder::BuildTest(){}
   void LibraryBuilder::BuildProject(){}
   void LibraryBuilder::BuildExample(){}
   void LibraryBuilder::BuildScript(){}
}
