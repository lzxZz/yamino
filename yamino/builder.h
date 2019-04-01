/**
 * @file builder.h
 * @author lzx (616281384@qq.com)
 * @brief 项目生成器的抽象
 * @version 0.1
 * @date 2019-04-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

namespace lzx::yamino {
   class Project;
   /**
    * @brief 生成器基类
    * 
    */
   class Builder {
   public:
      Builder(Project *project) : project_(project) {}
      virtual void BuildTest() {}
      virtual void BuildProject() {}
      virtual void BuildExample() {}
      virtual void BuildScript() {}
      virtual Project *GetProject();
      virtual void ReSet();
   private:
      Project *project_;
   };
   /**
    * @brief 库项目生成器
    * 
    */
   class LibraryBuilder : public Builder {
   public:
      LibraryBuilder(Project *project) : Builder{project} {}
      void BuildTest() override;
      void BuildProject() override;
      void BuildExample() override;
      void BuildScript() override;
   };

   class BinaryBuilder : public Builder {
      public:
      BinaryBuilder(Project *project) : Builder{project} {}
      void BuildTest() override;
      void BuildProject() override;
      void BuildExample() override;
      void BuildScript() override;
   };

   /**
    * @brief 将项目对象实例化到磁盘上
    * 
    */
   class Maker {
   public:
      // virtual Maker *GetInstance() = 0;
      virtual void Generate(const Project *project) = 0;
   };


   /**
    * @brief 将项目实例化到linux磁盘上
    * 
    */
   class LinuxMaker : public Maker {
   public:
      // Maker *GetInstance() override;
      void Generate(const Project *project) override;
   };

   /**
    * @brief 将项目实例化到windows磁盘上
    * 
    */
   class WindowsMaker : public Maker {
   public:
      // Maker *GetInstance() override;
      void Generate(const Project *project) override;
   };
   
}