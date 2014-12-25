
#添加debug.mk
include $(AMF_PROJECT_MK_ROOT)/debug.mk

#保证all为第一个目录
all: __module_before__ __all__ __module_after__
	$(call amf_debug_log, "do $@:$^")

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
TARGET_TYPE=

#设置编译器名称
CC=gcc

#设置需要生成的目标名称
TARGET_NAME=target

#设置编译器程序
CC=gcc
CPLUSPLUS=g++
DEBUG_COMPLIER=debugutil.sh

#C 默认编译选项
C_COMPLIER_FLAGS= -Wall -Werror -g -Wshadow -Wpointer-arith #-Wmissing-prototypes -Wstrict-prototypes 

#C++ 默认编译选项
CPLUS_COMPLIER_FLAGS=-Wall -Werror -g

#ld 选项
LD_FLAGS=-ldebug -lstr -L$(AMF_PROJECT_ROOT)/lib -finline-functions

#include 选项
AMF_INCLUDE_PATH=-I$(AMF_PROJECT_ROOT)/src/lib/libdebug \
-I$(AMF_PROJECT_ROOT)/src/lib/libmem \
-I$(AMF_PROJECT_ROOT)/src/lib/libstr \
-I$(AMF_PROJECT_ROOT)/src/lib/cjson-code \
-I$(AMF_PROJECT_ROOT)/src/lib/libxml

#设置debug complier path
DEBUG_COMPLIER_PATH=$(AMF_PROJECT_ROOT)/mk
