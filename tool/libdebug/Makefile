include $(AMF_PROJECT_MK_ROOT)/rule.mk
SRCS=libdebug.c
TARGET_TYPE=lib
TARGET_NAME=libdebug.a

MODULE_AFTER=test_debug
CLEAN_AFTER=test_clean

test_debug:
	$(MAKE) -C ./example/ 
test_clean:
	$(MAKE) -C ./example clean

include $(AMF_PROJECT_MK_ROOT)/basic.mk

