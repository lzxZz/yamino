import os;

buildContent = '''#!/bin/bash

mkdir build
cd build
pwd
cmake ..
make'''

makefileContent = '''.PHONY : build clean

build:
	@./script/build.sh

clean:
	@-rm -r build
'''
gitIgnoreContent = '''.vscode/
build/
out/
'''

testMainContent= '''#include <gtest/gtest.h>

int main(int argc, char **argv){
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
'''

testBasicContent = '''#include <gtest/gtest.h>

TEST(ExampleTest, Add){
   EXPECT_EQ(2,2);
}


'''

def GetSubDirString(directory):
   return 'add_subdirectory(' + directory + ')'


def FileExist(file):
   return os.path.exists(file);