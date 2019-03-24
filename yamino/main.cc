#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

#include "cmd.h"

using namespace yamino;

int main(int argc, char **argv){
    if ( argc < 3){
        cout << "请指定参数" << endl;
    }

    const string type = argv[1];        // 命令类型 new , add
    
    const string project  = argv[2];    // 项目名称
    
    string arg = "-bin"; 
    if (argc == 4){
        arg = argv[3];         // 配合上一个参数的参数, -bin -lib -test -class
    }
    


    if (type == "new"){
        // 新建项目
        if (arg  == "-lib"){
            NewLibrary();
        }else if(arg == "-bin" || arg == "-b"){
            NewBinary(project);
        }
    }
    // else if (type == "add"){
    //     // 添加成员
    //     if (arg == "-cls" || arg == "-c"){
    //         AddClass();
    //     }else if (arg == "-test" || arg == "-ut"){
    //         AddTest();
    //     }
    // }

}