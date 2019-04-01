
#include <cassert>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

#include "cmd.h"

#include "builder.h"
#include "project.h"
using namespace yamino;
using namespace lzx::yamino;

int main(int argc, char **argv){
    if ( argc < 3){
        cout << "请指定参数" << endl;
        // 输出帮助信息
        return -1;
    }
    
    bool is_library = true;
    bool set_dir = false;
    string root_dir = ".";
    bool is_fix = false;
    for (int i = 3; i < argc; i++){
        string arg = argv[i];       //将const char*转换为string,否则==运算回比较指针
        if (arg == "-bin"){
            is_library = false;
        }else if (arg == "-dir"){         // 设置项目创建的目录
            root_dir = argv[++i];
        }else if ( arg == "-fix"){
            is_fix = true;
        }
    }

    const string cmd_type = argv[1];
    const string project_name = argv[2];

    assert(cmd_type ==  "new"); // 暂时只支持创建项目

    Project *project = nullptr;
    Builder *builder = nullptr;
    if (is_library){
        project = new LibraryProject(project_name, root_dir);
        builder = new LibraryBuilder(project);
    }else{
        project = new BinaryProject(project_name, root_dir);
        builder = new BinaryBuilder(project);
    }
    builder->BuildExample();
    builder->BuildProject();
    builder->BuildScript();
    builder->BuildTest();
    
    
    
    Maker *maker = nullptr;
    
#ifdef __linux__
    cout << "linux" << endl;
    maker = new LinuxMaker();
#elif defined WIN32
    cout << "暂不支持windows平台" << endl;

    maker = new WindowsMaker();
#else
    cout << "未定义Maker" << endl;
    return -1;
#endif

    project = builder->GetProject();

    maker->Generate(project);
    
    
    


    

}