include $(AMF_PROJECT_MK_ROOT)/rule.mk
SRCS=libdebug.c
TARGET_TYPE=lib
TARGET_NAME=libdebug.a

MODULE_AFTER=test_debug

test_debug:
	$(MAKE) -C ./example/ 
	$(MAKE) -C ./example clean

include $(AMF_PROJECT_MK_ROOT)/basic.mk

