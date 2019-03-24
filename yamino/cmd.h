/**
 * @file cmd.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-03-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */


#ifndef YAMINO_CMD_H_
#define YAMINO_CMD_H_

#include <string>

namespace yamino{
    /**
     * @brief  命令类别
     * 
     */
    enum class CommandType{
        kNew,   
        kAdd,
    };


    void NewBinary(const std::string &project_name);   // 新建二进制项目
    void NewLibrary();  // 新建库项目, 大型项目应该使用库项目
    void AddClass();    // 添加类
    void AddTest();     // 添加测试

}



#endif//YAMINO_CMD_H_