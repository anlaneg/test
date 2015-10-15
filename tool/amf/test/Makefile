include $(AMF_PROJECT_MK_ROOT)/rule.mk

MODULE_BEFORE=
MODULE_AFTER=end

before:
	@echo "do $@:$^"

end:
	@echo "do $@:$^"

SUB_MODULE=module1 module2 

TARGET_TYPE=bin
INCLUDE_PATH=-I./module1 -I./module2

include $(AMF_PROJECT_MK_ROOT)/basic.mk

