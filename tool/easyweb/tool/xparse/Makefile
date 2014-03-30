include $(AMF_PROJECT_MK_ROOT)/rule.mk

TARGET_TYPE=bin
TARGET_NAME=xparse

SUB_MODULE=debug parse plugin syntax

#ld 选项
LD_FLAGS+=-lxml

#c_complier flags
C_COMPLIER_FLAGS+= -I./debug/ -I./syntax/ -I./plugin/

include $(AMF_PROJECT_MK_ROOT)/basic.mk

