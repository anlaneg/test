
define(`M4_USER',`int user_name_`$1'(void)')
define(`M4_USER_PASSWD',)
ifdef(`M4_USER_PASSWD',`define(`M4_USER_NAME',`M4_USER($1)')',"nothing to do!")
M4_USER_NAME(`along')

