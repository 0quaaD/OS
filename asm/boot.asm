
	%include "asm/multiboot.asm"
	section .bss
	align 16
stack_bottom:
	resb 16384


stack_top:
	extern maink
	section .text
	global _start
_start:
	mov esp, stack_top
	call maink
	cli
	.hang:
	hlt
	jmp .hang
	
