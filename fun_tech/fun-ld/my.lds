ENTRY(_start)
SECTIONS
{
	. = 0x10000;
	.text : { *(.text) }
	. = 0x8000000;
	.data : { *(.data) }
	.bss : { *(.bss) }
	.plt : { *(.plt) }

	.SF_HOOK : {
            sf_hook_start_point = . ;
            *(.SF_HOOK)
            sf_hook_end_point = . ;
  }
}
