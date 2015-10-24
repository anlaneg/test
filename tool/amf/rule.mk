
#添加debug.mk
include $(AMF_PROJECT_MK_ROOT)/debug.mk

#保证all为第一个目录
all: __module_before__ __all__ __module_after__

clean:__clean__

#获取当前文件夹下的所有c文件
SRCS=$(wildcard *.c)

#获取当前文件夹下所有c++文件
CPLUS_SRCS=$(wildcard *.cpp) $(wildcard *.C) $(wildcard *.cc)

#获取当前文件夹下所有debug文件
DEBUG_SRCS=$(wildcard *.debug)

#设置当前文件夹下需要参与编译的子module
SUB_MODULE=

#设置顶层目录
TOP_MODULE=..

#需要建立的输出目录
OUT_DIR=obj

#设置需要生成的目标类型
TARGET_TYPE=obj

#设置需要生成的目标名称
TARGET_NAME=target

#设置编译器程序
CC=gcc
AR=ar
CPLUSPLUS=g++
DEBUG_COMPLIER=$(AMF_PROJECT_LIBDEBUG)/debugutil.sh

#C 默认编译选项
COMPLIER_FLAGS= -Wall -Werror -g -MD
C_COMPLIER_FLAGS= -Wshadow -Wpointer-arith

#C++ 默认编译选项
CPLUS_COMPLIER_FLAGS= 

#ld 选项
DEPEND_LIBS=

#设置head-file path,lib-path
INCLUDE_PATH=
