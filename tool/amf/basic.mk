
#获得SRCS_OBJECT文件
SRCS_OBJECT=$(SRCS:%.c=$(OUT_DIR)/%.o)

#获得CPLUS_SRCS_OBJECT文件
CPLUS_SRCS_OBJECT=$(addprefix $(OUT_DIR)/,$(addsuffix .oo,$(basename $(CPLUS_SRCS))))

#获得.d文件
DEPEND_FILE=$(addsuffix .d,$(basename $(SRCS_OBJECT))) $(addsuffix .d,$(basename $(CPLUS_SRCS_OBJECT)))

#获得子模块生成的文件
SUB_MODULE_OBJECT=$(wildcard $(OUT_DIR)/_*.o)

#检查是否有MODULE_BEFORE
ifeq ($(strip $(MODULE_BEFORE)),)
__module_before__:
	@echo "do $@:$^"

else
__module_before__: $(MODULE_BEFORE)
	@echo "do $@:$^"

endif

#在__module_before__之后我们再开始匹配编译文件
#这样,可以保证__module_before__之前完成某此特殊操作


#检查是否有MODULE_AFTER
ifeq ($(strip $(MODULE_AFTER)),)
__module_after__:
	@echo "do $@:$^"

else
__module_after__: $(MODULE_AFTER)
	@echo "do $@:$^"

endif


__all__:__mk_out_dir__ __mk_submod__ __mk_target__
	@echo "do $@:$^"


#生成输出目录
__mk_out_dir__:
	@echo "mkdir $(OUT_DIR)"

#构建子模块
__mk_submod__:
	@for i in $(SUB_MODULE);do $(MAKE) -C $$i all || exit 1 ; done;

#清理生成
clean:
	@echo "-rm -rf $(OUT_DIR)"

#c文件生成.o文件
$(OUT_DIR)/%.o:%.c
	@echo "$@:$^"

#c++文件生成.oo文件
$(OUT_DIR)/%.oo:%.cpp
	@echo "$@:$^"

$(OUT_DIR)/%.oo:%.cc
	@echo "$@:$^"

$(OUT_DIR)/%.oo:%.C
	@echo "$@:$^"

#生成当前目录要求的目标
ifeq ($(strip $(TARGET_TYPE)),bin)
__mk_target__: $(SRCS_OBJECT) $(CPLUS_SRCS_OBJECT) $(SUB_MODULE_OBJECT)
	@echo "bin=$@:$^"
endif

ifeq ($(strip $(TARGET_TYPE)),lib)
__mk_target__: $(SRCS_OBJECT) $(CPLUS_SRCS_OBJECT) $(SUB_MODULE_OBJECT)
(
	@echo "lib=$@:$^"
endif

ifeq ($(strip $(TARGET_TYPE)),dynlib)
__mk_target__: $(SRCS_OBJECT) $(CPLUS_SRCS_OBJECT) $(SUB_MODULE_OBJECT)

	@echo "dnylib=$@:$^"
endif

ifeq ($(strip $(TARGET_TYPE)),obj)
__mk_target__: $(SRCS_OBJECT) $(CPLUS_SRCS_OBJECT) $(SUB_MODULE_OBJECT)

	@echo "obj=$@:$^"
endif

#用于amf框架测试
debug_amf:
	@echo "SRCS=$(SRCS)"
	@echo "CPLUS_SRCS=$(CPLUS_SRCS)"
	@echo "OUT_DIR=$(OUT_DIR)"
	@echo "SRCS_OBJECT=$(SRCS_OBJECT)"
	@echo "CPLUS_SRCS_OBJECT=$(CPLUS_SRCS_OBJECT)"
	@echo "DEPEND_FILE=$(DEPEND_FILE)"
	@echo "SUB_MODULE=$(SUB_MODULE)"
	@echo "TARGET_TYPE=$(TARGET_TYPE)"
	@echo "SUB_MODULE_OBJECT=$(SUB_MODULE_OBJECT)"


#尝试着包含.d文件
-include $(DEPEND_FILE)
