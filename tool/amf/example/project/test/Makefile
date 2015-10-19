include $(AMF_PROJECT_MK_ROOT)/rule.mk

TARGET_TYPE=bin

INCLUDE_PATH+=-I$(AMF_PROJECT_ROOT)/project/lib/libdyn/ -I$(AMF_PROJECT_ROOT)/project/lib/libstatic/ -I$(AMF_PROJECT_ROOT)/project/test/module1/ -I$(AMF_PROJECT_ROOT)/project/test/module2/ -I$(AMF_PROJECT_ROOT)/../../libdebug -L$(AMF_PROJECT_ROOT)/project/lib/libstatic/ -L$(AMF_PROJECT_ROOT)/project/lib/libdyn/ -L$(AMF_PROJECT_ROOT)/../../libdebug

TARGET_NAME=test

COMPLIER_FLAGS += -DPROJECT_TEST    

SUB_MODULE= module1 module2

DEPEND_LIBS=-lsta -ldyn -ldebug

include $(AMF_PROJECT_MK_ROOT)/basic.mk

