SECTIONS { 
	. = 1M; 
	.text : {
	    *(.multiboot_header)
        . = ALIGN(8); 
        *(.text) 
	}
	. = ALIGN(16); 
	.data           : { *(.data*) }
	. = ALIGN(16); 
	.bss            : 
	{ 
        __bss_start = .; 
	    _bss_start = .; 
	    *(.bss) 
	    __bss_end = .;
	} 
	. = ALIGN(16); 
	_end = .; 
	. = ALIGN(512);
}