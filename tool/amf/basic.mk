
#设置模块格式
SUB_MODULE_PREFIX=sub_obj.

#获得SRCS_OBJECT文件(注意，这里有一个顺序关系，debug.o必须位于最前)
SRCS_OBJECT=$(DEBUG_SRCS:%.debug=$(OUT_DIR)/%_debug.o) $(SRCS:%.c=$(OUT_DIR)/%.o) 

#获得CPLUS_SRCS_OBJECT文件
CPLUS_SRCS_OBJECT=$(addprefix $(OUT_DIR)/,$(addsuffix .oo,$(basename $(CPLUS_SRCS))))

#获得debug文件
DEBUG_SRC_GEN=$(DEBUG_SRCS:%.debug=%_debug.c) $(DEBUG_SRCS:%.debug=%_debug.h) 

#获得.d文件
DEPEND_FILE=$(addsuffix .d,$(basename $(SRCS_OBJECT))) $(addsuffix .d,$(basename $(CPLUS_SRCS_OBJECT)))


#获得子模块生成的文件
ifeq ($(strip $(SUB_MODULE)),)
SUB_MODULE_OBJECT:=
else
SUB_MODULE_OBJECT:=$(SUB_MODULE:%=$(OUT_DIR)/$(SUB_MODULE_PREFIX)%.o) 

$(SUB_MODULE_OBJECT):__mk_submod__
endif

#获取svn文件版本
SVN_SRC_VERSION=$(shell if `svn info 2>/dev/null 1>/dev/null`; then svn info 2>/dev/null | head -n 5 | tail -n 1 | cut -d ' ' -f 2 ; else echo "NOT_SVN"; fi;)

#获取git文件版本
GIT_SRC_VERSION=$(shell if `git log 2>/dev/null 1>/dev/null` ; then  git log |  head -n 1 | cut -d ' ' -f 2 ; else echo "NOT_GIT"; fi;)
#检查是否有MODULE_BEFORE
ifeq ($(strip $(MODULE_BEFORE)),)
__module_before__:
	$(call amf_debug_log,  "do $@:$^")

else
__module_before__: $(MODULE_BEFORE)
	$(call amf_debug_log,  "do $@:$^")
endif

#在__module_before__之后我们再开始匹配编译文件
#这样,可以保证__module_before__之前完成某此特殊操作


#检查是否有MODULE_AFTER
ifeq ($(strip $(MODULE_AFTER)),)
__module_after__:
	$(call amf_debug_log,  "do $@:$^")

else
__module_after__: $(MODULE_AFTER)
	$(call amf_debug_log,  "do $@:$^")
endif


__all__:__mk_out_dir__ __mk_submod__ __mk_target__
	$(call amf_debug_log,  "do $@:$^")


#生成输出目录
__mk_out_dir__:
	$(call amf_debug_log,  "mkdir $(OUT_DIR)")
	$(call amf_command_execute,-mkdir $(OUT_DIR))

#构建子模块
__mk_submod__:
	@for i in $(SUB_MODULE);do $(MAKE) -C $$i all || exit 1 ; done;

#清理生成
clean:
	$(call amf_debug_log,  "-rm -rf $(OUT_DIR)")
	$(call amf_command_execute,  -rm -rf $(OUT_DIR))

#c文件生成.o文件
$(OUT_DIR)/%.o:%.c
	$(call amf_debug_log,  "$@:$^")
	$(call amf_command_execute ,$(CC) -c $(C_COMPLIER_FLAGS) -o $@ $^)

#c++文件生成.oo文件
$(OUT_DIR)/%.oo:%.cpp
	$(call amf_debug_log,  "$@:$^")
	$(call amf_command_execute ,$(CC) -c $(CPLUS_COMPLIER_FLAGS) -o $@ $^)

$(OUT_DIR)/%.oo:%.cc
	$(call amf_debug_log,  "$@:$^")
	$(call amf_command_execute,$(CC) -c $(CPLUS_COMPLIER_FLAGS) -o $@ $^)

$(OUT_DIR)/%.oo:%.C
	$(call amf_debug_log,  "$@:$^")
	$(call amf_command_execute,$(CC) -c $(CPLUS_COMPLIER_FLAGS) -o $@ $^)

#生成当前目录要求的目标
ifeq ($(strip $(TARGET_TYPE)),bin)
__mk_target__: $(SRCS_OBJECT) $(CPLUS_SRCS_OBJECT) $(SUB_MODULE_OBJECT)
	$(call amf_debug_log,  "bin=$@:$^")
	$(call amf_command_execute,$(CC) $(C_COMPLIER_FLAGS) -o $@ $^)
endif

ifeq ($(strip $(TARGET_TYPE)),lib)
__mk_target__: $(SRCS_OBJECT) $(CPLUS_SRCS_OBJECT) $(SUB_MODULE_OBJECT)
	$(call amf_debug_log,  "lib=$@:$^")
	$(call amf_command_execute,$(CC) $(C_COMPLIER_FLAGS) -o $@ $^)
endif

ifeq ($(strip $(TARGET_TYPE)),dynlib)
__mk_target__: $(SRCS_OBJECT) $(CPLUS_SRCS_OBJECT) $(SUB_MODULE_OBJECT)

	$(call amf_debug_log,  "dnylib=$@:$^")
	$(call amf_command_execute,$(CC) $(C_COMPLIER_FLAGS) -o $@ $^)
endif

ifeq ($(strip $(TARGET_TYPE)),obj)
__mk_target__: $(SRCS_OBJECT) $(CPLUS_SRCS_OBJECT)  $(SUB_MODULE_OBJECT) 
	$(__target_complier__) -nostdlib -r -o $(TOP_MODULE)/$(OUT_DIR)/$(SUB_MODULE_PREFIX)$(TARGET_NAME).o $^ $(AMF_INCLUDE_PATH)
endif

	$(call amf_debug_log,  "obj=$@:$^")
	$(call amf_command_execute,$(CC) $(C_COMPLIER_FLAGS) -o $@ $^)
endif

#用于amf框架测试
debug_amf:
	$(call amf_debug_log,  "SRCS=$(SRCS)")
	$(call amf_debug_log,  "CPLUS_SRCS=$(CPLUS_SRCS)")
	$(call amf_debug_log,  "OUT_DIR=$(OUT_DIR)")
	$(call amf_debug_log,  "SRCS_OBJECT=$(SRCS_OBJECT)")
	$(call amf_debug_log,  "CPLUS_SRCS_OBJECT=$(CPLUS_SRCS_OBJECT)")
	$(call amf_debug_log,  "DEPEND_FILE=$(DEPEND_FILE)")
	$(call amf_debug_log,  "SUB_MODULE=$(SUB_MODULE)")
	$(call amf_debug_log,  "TARGET_TYPE=$(TARGET_TYPE)")
	$(call amf_debug_log,  "SUB_MODULE_OBJECT=$(SUB_MODULE_OBJECT)")
	$(call amf_debug_log,  "SVN_SRC_VERSION=$(SVN_SRC_VERSION)")
	$(call amf_debug_log,  "GIT_SRC_VERSION=$(GIT_SRC_VERSION)")

#尝试着包含.d文件
-include $(DEPEND_FILE)
