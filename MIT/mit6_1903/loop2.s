	.file	"loop2.c"
	.text
	.globl	fact_while
	.type	fact_while, @function
fact_while:
.LFB0:
	.cfi_startproc
	movl	$1, %eax
	jmp	.L2
.L3:
	imulq	%rdi, %rax
	subq	$1, %rdi
.L2:
	cmpq	$1, %rdi
	jg	.L3
	ret
	.cfi_endproc
.LFE0:
	.size	fact_while, .-fact_while
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
