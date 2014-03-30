
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

else
__module_before__: $(MODULE_BEFORE)

endif

#在__module_before__之后我们再开始匹配编译文件
#这样,可以保证__module_before__之前完成某此特殊操作


#检查是否有MODULE_AFTER
ifeq ($(strip $(MODULE_AFTER)),)
__module_after__:

else
__module_after__: $(MODULE_AFTER)

endif


__all__:__mk_out_dir__ __mk_submod__ __mk_target__


#生成输出目录
__mk_out_dir__:
	@-mkdir -p $(OUT_DIR)

#构建子模块
__mk_submod__:
	@for i in $(SUB_MODULE);do $(MAKE) -C $$i all || exit 1 ; done;

#清理生成
clean:
	@for i in $(SUB_MODULE);do $(MAKE) -C $$i clean || exit 1 ; done;
	-rm -rf $(OUT_DIR) $(DEBUG_SRC_GEN)

#debug文件生成.c文件
#注意：此句为了防止$(DEBUG_SRC_GEN)被make删除
.SECONDARY:$(DEBUG_SRC_GEN)

%_debug.h %_debug.c:%.debug
	$(DEBUG_COMPLIER_PATH)/$(DEBUG_COMPLIER)  $^ .  $(DEBUG_COMPLIER_PATH)

#c文件生成.o文件
$(OUT_DIR)/%.o:%.c
	$(CC) $(C_COMPLIER_FLAGS) $(AMF_INCLUDE_PATH) -MD -c -o $@ $< 
#c++文件生成.oo文件
$(OUT_DIR)/%.oo:%.cpp
	$(CPLUSPLUS) $(CPLUS_COMPLIER_FLAGS) $(AMF_INCLUDE_PATH) -c -o $@ $^ 

$(OUT_DIR)/%.oo:%.cc
	$(CPLUSPLUS) $(CPLUS_COMPLIER_FLAGS) $(AMF_INCLUDE_PATH) -c -o $@ $^ 
$(OUT_DIR)/%.oo:%.C
	$(CPLUSPLUS) $(CPLUS_COMPLIER_FLAGS) $(AMF_INCLUDE_PATH) -c -o $@ $^ 

#检查应使用的编译器
ifeq ($(strip $(CPLUS_SRCS_OBJECT)),)
__target_complier__=$(CC)
else
__target_complier__=$(CPLUSPLUS)
endif

#生成当前目录要求的目标
ifeq ($(strip $(TARGET_TYPE)),bin)
__mk_target__: $(SRCS_OBJECT) $(CPLUS_SRCS_OBJECT) $(SUB_MODULE_OBJECT)
	$(__target_complier__) $(C_COMPLIER_FLAGS) -o $(OUT_DIR)/$(TARGET_NAME) $^ $(LD_FLAGS) $(AMF_INCLUDE_PATH)
	cp $(OUT_DIR)/$(TARGET_NAME) $(AMF_PROJECT_ROOT)/bin
endif

ifeq ($(strip $(TARGET_TYPE)),lib)
__mk_target__: $(SRCS_OBJECT) $(CPLUS_SRCS_OBJECT)  $(SUB_MODULE_OBJECT)
	ar -r $(OUT_DIR)/$(TARGET_NAME).a  $^
	cp -rf $(OUT_DIR)/$(TARGET_NAME).a $(AMF_PROJECT_ROOT)/lib
endif

ifeq ($(strip $(TARGET_TYPE)),dynlib)
__mk_target__: $(SRCS_OBJECT) $(CPLUS_SRCS_OBJECT)  $(SUB_MODULE_OBJECT) 
	$(__target_complier__) -fPIC -shared -o $(OUT_DIR)/$(TARGET_NAME).so $^ $(AMF_INCLUDE_PATH)
	cp -rf $(OUT_DIR)/$(TARGET_NAME).so $(AMF_PROJECT_ROOT)/lib
endif

ifeq ($(strip $(TARGET_TYPE)),obj)
__mk_target__: $(SRCS_OBJECT) $(CPLUS_SRCS_OBJECT)  $(SUB_MODULE_OBJECT) 
	$(__target_complier__) -nostdlib -r -o $(TOP_MODULE)/$(OUT_DIR)/$(SUB_MODULE_PREFIX)$(TARGET_NAME).o $^ $(AMF_INCLUDE_PATH)
endif

ifeq ($(strip $(TARGET_TYPE)),)
__mk_target__:
endif

#用于amf框架测试
debug_amf:
	@echo "CC=$(CC)"
	@echo "CPLUSPLUS=$(CPLUSPLUS)"
	@echo "DEBUG_COMPLIER=$(DEBUG_COMPLIER)"
	@echo "SRCS=$(SRCS)"
	@echo "CPLUS_SRCS=$(CPLUS_SRCS)"
	@echo "DEBUG_SRCS=$(DEBUG_SRCS)"
	@echo "OUT_DIR=$(OUT_DIR)"
	@echo "SRCS_OBJECT=$(SRCS_OBJECT)"
	@echo "CPLUS_SRCS_OBJECT=$(CPLUS_SRCS_OBJECT)"
	@echo "DEBUG_OBJECT=$(DEBUG_SRCS:%.debug=$(OUT_DIR)/%_debug.o)"
	@echo "DEPEND_FILE=$(DEPEND_FILE)"
	@echo "SUB_MODULE=$(SUB_MODULE)"
	@echo "TARGET_TYPE=$(TARGET_TYPE)"
	@echo "SUB_MODULE_OBJECT= $(SUB_MODULE_OBJECT)"
	@echo "SVN_SRC_VERSION=$(SVN_SRC_VERSION)"
	@echo "GIT_SRC_VERSION=$(GIT_SRC_VERSION)"
	@echo "C_COMPLIER_FLAGS=$(C_COMPLIER_FLAGS)"
	@echo "DEBUG_SRC_GEN=$(DEBUG_SRC_GEN)"
	@echo "AMF_INCLUDE_PATH=$(AMF_INCLUDE_PATH)"


#尝试着包含.d文件
-include $(DEPEND_FILE)
