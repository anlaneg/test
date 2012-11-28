main: module_before all  module_after

module_before:
	eval $(MODULE_BEFORE)
	echo "test"
module_after:
	$(MODULE_AFTER)

ifeq 
all:
	echo "hello"

