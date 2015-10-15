
#定义当前debug是否开启(true为开启)
ENABLE_AMF_DEBUG=false

define amf_debug_log_inner
	@echo "amf_debug_log :$(1)"
endef

#amf日志输出
#$(1)
#@echo "ENABLE_AMF_DEBUG=$(ENABLE_AMF_DEBUG)"
define amf_debug_log
	$(if $(subst false,,$(strip $(ENABLE_AMF_DEBUG))),$(call amf_debug_log_inner , $(1)),)
endef

#amf命令执行
define amf_command_execute
	$(if $(subst false,,$(strip $(ENABLE_AMF_DEBUG))),$(call amf_debug_log,$(1)),)
	$(1)
endef


