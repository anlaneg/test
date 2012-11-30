#保证all为第一个目录
all: __module_before__ __all__ __module_after__
	@echo "do $@:$^"

#获取当前文件夹下的所有c文件
SRCS=$(wildcard *.c)

#获取当前文件夹下所有c++文件
CPLUS_SRCS=$(wildcard *.cpp) $(wildcard *.C) $(wildcard *.cc)

#设置当前文件夹下需要参与编译的子module
SUB_MODULE=

#需要建立的输出目录
OUT_DIR=obj

#设置需要生成的类型
TARGET_TYPE=obj

#C 默认编译选项
C_COMPLIER_FLAGS="-Wall -Werror -g"

#C++ 默认编译选项
CPLUS_COMPLIER_FLAGS="-Wall -Werror -g"

#ld 选项
LD_FLAGS=""


