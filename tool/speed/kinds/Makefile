include $(AMF_PROJECT_MK_ROOT)/rule.mk

MODULE_BEFORE=
MODULE_AFTER=end

before:
	@echo "do $@:$^"

end:
	@echo "do $@:$^"

SUB_MODULE= lib modules frame kinds

TARGET_TYPE=bin

LD_FLAGS= -lpthread

C_COMPLIER_FLAGS+=-I. -I./lib/ -I./modules/

include $(AMF_PROJECT_MK_ROOT)/basic.mk

