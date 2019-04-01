/**
 * @file project.h
 * @author lzx (616281384@qq.com)
 * @brief 项目抽象类, 用于表示一个项目
 * @version 0.1
 * @date 2019-04-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <map>
#include <set>
#include <string>


namespace lzx::yamino {
   class Builer;
   // 表示一个项目
   class Project {
   public:
      // explicit Project(const std::string &project_name) : project_name_(project_name) {}
      Project(const std::string &project_name, const std::string &root_dir = ".") :  project_name_(project_name), root_dir_(root_dir){}
      virtual const std::set<std::string> &Dirs() const {
         if (!is_generator){
            Generate();
         }
         return directories_;
      }
      virtual const std::map<std::string, std::string> &Files() const {
         if (!is_generator){
            Generate();
         }
         return files_;
      }
      
   protected:
      virtual void Generate() const {}
      bool is_generator = false;
      // 只作为存储最终创建文件信息的部分存在,
      mutable std::set<std::string> directories_;     
      mutable std::map<std::string, std::string> files_;

      
      bool doc_ = true;
      bool test_ = true;
      bool example_ = true;
      bool binary_;
      const std::string root_dir_;
      const std::string project_name_;
   };

   /**
    * @brief 表示一个库项目
    * 
    */
   class LibraryProject : public Project {
      friend class Builder;
   public:
      LibraryProject(const std::string &project_name, const std::string &root_dir = ".") : Project{project_name, root_dir} {}
      // const std::set<std::string> &Dirs()  override;
      // const std::map<std::string, std::string> &Files()  override;
   
   private:
      void Generate() const override;
   };

   /**
    * @brief 表示一个二进制项目
    * 
    */
   class BinaryProject : public Project {
      friend class Builder;
   public:
      BinaryProject(const std::string &project_name, const std::string &root_dir = ".") : Project{project_name, root_dir} {}
      // const std::set<std::string> &Dirs()  override;
      // const std::map<std::string, std::string> &Files()  override;
   private:
      void Generate() const override ;
   };
}