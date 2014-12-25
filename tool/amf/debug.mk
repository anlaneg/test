
#定义当前debug是否开启(true为开启)
ENABLE_AMF_DEBUG=false

#amf日志输出
#$(1)
#@echo "ENABLE_AMF_DEBUG=$(ENABLE_AMF_DEBUG)"
define amf_debug_log
	#$(if ifeq ($(strip $(ENABLE_AMF_DEBUG)),true),@echo $(1),)
endef

#amf命令执行
define amf_command_execute
	$(if ifeq ( $(strip $(ENABLE_AMF_DEBUG)), true),$(call amf_debug_log ,"$(1)"),$(1))
ifeq ($(strip $(ENABLE_AMF_DEBUG)),true)
	$(call amf_debug_log , "$(1)")
else
	$(1)
endif

endef


