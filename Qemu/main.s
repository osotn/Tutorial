	.arch i8086,jumps
	.code16
	.att_syntax prefix
#NO_APP
	.text
	.global	print_char
	.type	print_char, @function
print_char:
	pushw	%bp
	movw	%sp,	%bp
	movb	4(%bp),	%al
	movb	%al,	%al
	xorb	%ah,	%ah
	orb	$14,	%ah
	movw	$7,	%bx
#APP
;# 4 "main.c" 1
	int $0x10
;# 0 "" 2
#NO_APP
	nop
	popw	%bp
	pushw	%ss
	popw	%ds
	ret
	.size	print_char, .-print_char
	.global	cls
	.type	cls, @function
cls:
	pushw	%bp
	movw	%sp,	%bp
#APP
;# 12 "main.c" 1
	mov $0x0003, %ax 
int $0x10         

;# 0 "" 2
#NO_APP
	nop
	popw	%bp
	pushw	%ss
	popw	%ds
	ret
	.size	cls, .-cls
	.section	.rodata
.LC0:
	.string	"Hello from C Bootloader!"
	.text
	.global	main_c
	.type	main_c, @function
main_c:
	pushw	%bp
	movw	%sp,	%bp
	subw	$2,	%sp
	movw	$.LC0,	-2(%bp)
	pushw	%ss
	popw	%ds
	call	cls
	jmp	.L4
.L5:
	movw	-2(%bp),	%bx
	leaw	1(%bx),	%ax
	movw	%ax,	-2(%bp)
	movb	%ss:(%bx),	%al
	pushw	%ax
	pushw	%ss
	popw	%ds
	call	print_char
	addw	$2,	%sp
.L4:
	movw	-2(%bp),	%bx
	movb	%ss:(%bx),	%al
	cmpb	$1,	%al
	testb	%al,	%al
	jne	.L5
	nop
	movw	%bp,	%sp
	popw	%bp
	pushw	%ss
	popw	%ds
	ret
	.size	main_c, .-main_c
	.ident	"GCC: (GNU) 6.3.0"
