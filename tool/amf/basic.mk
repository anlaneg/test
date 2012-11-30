#保证all为第一个目录
#此目标移至rule.mk中
#all: __module_before__ __all__ __module_after__
#	@echo "do $@:$^"

__all__:
	@echo "do $@:$^"


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
