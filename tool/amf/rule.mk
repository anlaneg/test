#保证all为第一个目录
all: __module_before__ __all__ __module_after__
	@echo "do $@:$^"

