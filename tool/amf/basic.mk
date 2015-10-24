
#设置模块格式
SUB_MODULE_PREFIX=sub_obj.
C_USER_COMPLIER_FLAG=$(COMPLIER_FLAGS) $(C_COMPLIER_FLAGS) $(INCLUDE_PATH)
CPP_USER_COMPLIER_FLAG=$(COMPLIER_FLAGS) $(CPLUS_COMPLIER_FLAGS) $(INCLUDE_PATH)

#获得SRCS_OBJECT文件(注意，这里有一个顺序关系，debug.o必须位于最前)
SRCS_OBJECT=$(DEBUG_SRCS:%.debug=$(OUT_DIR)/%_debug.o) $(SRCS:%.c=$(OUT_DIR)/%.o) 

#获得CPLUS_SRCS_OBJECT文件
CPLUS_SRCS_OBJECT=$(addprefix $(OUT_DIR)/,$(addsuffix .oo,$(basename $(CPLUS_SRCS))))

#获得debug文件
#debug.h类同步生成,无必要列出
#DEBUG_SRC_GEN=$(DEBUG_SRCS:%.debug=%_debug.c) $(DEBUG_SRCS:%.debug=%_debug.h) 
DEBUG_SRC_GEN=$(DEBUG_SRCS:%.debug=$(OUT_DIR)/%_debug.c) #$(DEBUG_SRCS:%.debug=%_debug.h) 

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

#在__module_before__之后我们再开始匹配编译文件
#这样,可以实现__module_before__之前完成某此特殊操作

#检查是否有MODULE_BEFORE
ifeq ($(strip $(MODULE_BEFORE)),)
__module_before__:
else
__module_before__: $(MODULE_BEFORE)
endif

#检查是否有MODULE_AFTER
ifeq ($(strip $(MODULE_AFTER)),)
__module_after__:
else
__module_after__: $(MODULE_AFTER)
endif


__all__: __mk_out_dir__  __mk_submod__  __mk_target__

#生成输出目录
$(OUT_DIR) :
	$(call amf_command_execute,@mkdir $(OUT_DIR))

__mk_out_dir__:$(OUT_DIR)


#构建子模块
__mk_submod__:
	@for i in $(SUB_MODULE);do $(MAKE) -C $$i all || exit 1 ; done;

__cl_submod__:
	@for i in $(SUB_MODULE);do $(MAKE) -C $$i clean || exit 1 ; done;


#清理生成
ifeq ($(strip $(CLEAN_AFTER)),)
__module_clean_after__:
else
__module_clean_after__: $(CLEAN_AFTER)
endif

__clean__: __cl_submod__ __cl_target__ __module_clean_after__

__cl_target__:
	$(call amf_command_execute,  @rm -rf $(OUT_DIR))
	$(call amf_command_execute,  @rm -rf $(TARGET_NAME))


$(DEBUG_SRC_GEN):$(OUT_DIR)/%_debug.c:%.debug
	$(call amf_command_execute ,$(DEBUG_COMPLIER) $< $(OUT_DIR))

$(OUT_DIR)/%_debug.o:$(OUT_DIR)/%_debug.c
	$(call amf_command_execute ,$(CC) $(C_USER_COMPLIER_FLAG) -c -o $@ $<)
	
#c文件生成.o文件
$(OUT_DIR)/%.o:%.c
	$(call amf_command_execute ,$(CC) $(C_USER_COMPLIER_FLAG) -fPIC -c -o $@ $<)

#c++文件生成.oo文件
$(OUT_DIR)/%.oo:%.cpp
	$(call amf_command_execute ,$(CC) $(CPP_USER_COMPLIER_FLAG) -c -o $@ $<)

$(OUT_DIR)/%.oo:%.cc
	$(call amf_command_execute,$(CC) $(CPP_USER_COMPLIER_FLAG) -c -o $@ $<)

$(OUT_DIR)/%.oo:%.C
	$(call amf_command_execute,$(CC) $(CPP_USER_COMPLIER_FLAG) -c -o $@ $<)

#生成当前目录要求的目标
ifeq ($(strip $(TARGET_TYPE)),bin)
__mk_target__: $(SRCS_OBJECT) $(CPLUS_SRCS_OBJECT) $(SUB_MODULE_OBJECT)
	$(call amf_command_execute,$(CC) $(C_USER_COMPLIER_FLAG) -o $(TARGET_NAME) $^ $(DEPEND_LIBS))
endif

ifeq ($(strip $(TARGET_TYPE)),lib)
__mk_target__: $(SRCS_OBJECT) $(CPLUS_SRCS_OBJECT) $(SUB_MODULE_OBJECT)
	$(call amf_command_execute,$(AR) rc $(TARGET_NAME) $^)
endif

ifeq ($(strip $(TARGET_TYPE)),dynlib)
__mk_target__: $(SRCS_OBJECT) $(CPLUS_SRCS_OBJECT) $(SUB_MODULE_OBJECT)
	$(CC) $(C_USER_COMPLIER_FLAG) -fPIC -shared -Wl,-soname,$(shell basename $(TARGET_NAME)) -o $(TARGET_NAME) $^
endif

ifeq ($(strip $(TARGET_TYPE)),obj)
__mk_target__: $(SRCS_OBJECT) $(CPLUS_SRCS_OBJECT)  $(SUB_MODULE_OBJECT) 
	$(call amf_command_execute,$(CC) $(C_USER_COMPLIER_FLAG) -fPIC -nostdlib -r -o ../$(OUT_DIR)/$(SUB_MODULE_PREFIX)$(shell basename $(CURDIR)).o $^)
endif

ifeq ($(strip $(TARGET_TYPE)),)
__mk_target__:

endif

#用于amf框架测试
.PHONY: debug_amf
debug_amf:
	$(call display,  "SRCS=$(SRCS)")
	$(call display,  "CPLUS_SRCS=$(CPLUS_SRCS)")
	$(call display,  "OUT_DIR=$(OUT_DIR)")
	$(call display,  "SRCS_OBJECT=$(SRCS_OBJECT)")
	$(call display,  "CPLUS_SRCS_OBJECT=$(CPLUS_SRCS_OBJECT)")
	$(call display,  "DEPEND_FILE=$(DEPEND_FILE)")
	$(call display,  "SUB_MODULE=$(SUB_MODULE)")
	$(call display,  "TARGET_TYPE=$(TARGET_TYPE)")
	$(call display,  "SUB_MODULE_OBJECT=$(SUB_MODULE_OBJECT)")
	$(call display,  "SVN_SRC_VERSION=$(SVN_SRC_VERSION)")
	$(call display,  "GIT_SRC_VERSION=$(GIT_SRC_VERSION)")
	$(call display,  "TARGET_NAME=$(TARGET_NAME)")
	$(call display,  "C_USER_COMPLIER_FLAG=$(C_USER_COMPLIER_FLAG)")
	$(call display,  "CPP_USER_COMPLIER_FLAG=$(CPP_USER_COMPLIER_FLAG)")
	$(call display,  "DEPEND_LIBS=$(DEPEND_LIBS)")
	$(call display,  "DEPEND_FILE=$(DEPEND_FILE)")
	

#尝试着包含.d文件
-include $(DEPEND_FILE)

