	.file	"destructor.cpp"
# GNU C++11 (Ubuntu 5.4.0-6ubuntu1~16.04.12) version 5.4.0 20160609 (x86_64-linux-gnu)
#	compiled by GNU C version 5.4.0 20160609, GMP version 6.1.0, MPFR version 3.1.4, MPC version 1.0.3
# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed:  -imultiarch x86_64-linux-gnu -D_GNU_SOURCE
# destructor.cpp -mtune=generic -march=x86-64 -std=c++11 -fverbose-asm
# -fstack-protector-strong -Wformat -Wformat-security
# options enabled:  -faggressive-loop-optimizations
# -fasynchronous-unwind-tables -fauto-inc-dec -fchkp-check-incomplete-type
# -fchkp-check-read -fchkp-check-write -fchkp-instrument-calls
# -fchkp-narrow-bounds -fchkp-optimize -fchkp-store-bounds
# -fchkp-use-static-bounds -fchkp-use-static-const-bounds
# -fchkp-use-wrappers -fcommon -fdelete-null-pointer-checks
# -fdwarf2-cfi-asm -fearly-inlining -feliminate-unused-debug-types
# -fexceptions -ffunction-cse -fgcse-lm -fgnu-runtime -fgnu-unique -fident
# -finline-atomics -fira-hoist-pressure -fira-share-save-slots
# -fira-share-spill-slots -fivopts -fkeep-static-consts
# -fleading-underscore -flifetime-dse -flto-odr-type-merging -fmath-errno
# -fmerge-debug-strings -fpeephole -fprefetch-loop-arrays
# -freg-struct-return -fsched-critical-path-heuristic
# -fsched-dep-count-heuristic -fsched-group-heuristic -fsched-interblock
# -fsched-last-insn-heuristic -fsched-rank-heuristic -fsched-spec
# -fsched-spec-insn-heuristic -fsched-stalled-insns-dep -fschedule-fusion
# -fsemantic-interposition -fshow-column -fsigned-zeros
# -fsplit-ivs-in-unroller -fstack-protector-strong -fstdarg-opt
# -fstrict-volatile-bitfields -fsync-libcalls -ftrapping-math
# -ftree-coalesce-vars -ftree-cselim -ftree-forwprop -ftree-loop-if-convert
# -ftree-loop-im -ftree-loop-ivcanon -ftree-loop-optimize
# -ftree-parallelize-loops= -ftree-phiprop -ftree-reassoc -ftree-scev-cprop
# -funit-at-a-time -funwind-tables -fverbose-asm -fzero-initialized-in-bss
# -m128bit-long-double -m64 -m80387 -malign-stringops
# -mavx256-split-unaligned-load -mavx256-split-unaligned-store
# -mfancy-math-387 -mfp-ret-in-387 -mfxsr -mglibc -mieee-fp
# -mlong-double-80 -mmmx -mno-sse4 -mpush-args -mred-zone -msse -msse2
# -mtls-direct-seg-refs -mvzeroupper

	.section	.rodata
	.type	_ZStL19piecewise_construct, @object
	.size	_ZStL19piecewise_construct, 1
_ZStL19piecewise_construct:
	.zero	1
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
.LC0:
	.string	"Call constructor, addr = "
.LC1:
	.string	"value a = "
	.text
	.align 2
	.globl	_ZN5ClassC2Ev
	.type	_ZN5ClassC2Ev, @function
_ZN5ClassC2Ev:
.LFB1384:
	.cfi_startproc
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$24, %rsp	#,
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)	# this, this
	movq	-24(%rbp), %rax	# this, tmp92
	movl	(%rax), %ebx	# this_2(D)->a, D.34634
	movl	$.LC0, %esi	#,
	movl	$_ZSt4cout, %edi	#,
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc	#
	movq	%rax, %rdx	#, D.34635
	movq	-24(%rbp), %rax	# this, tmp93
	movq	%rax, %rsi	# tmp93,
	movq	%rdx, %rdi	# D.34635,
	call	_ZNSolsEPKv	#
	movl	$.LC1, %esi	#,
	movq	%rax, %rdi	# D.34636,
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc	#
	movl	%ebx, %esi	# D.34634,
	movq	%rax, %rdi	# D.34635,
	call	_ZNSolsEi	#
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi	#,
	movq	%rax, %rdi	# D.34635,
	call	_ZNSolsEPFRSoS_E	#
	nop
	addq	$24, %rsp	#,
	popq	%rbx	#
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1384:
	.size	_ZN5ClassC2Ev, .-_ZN5ClassC2Ev
	.globl	_ZN5ClassC1Ev
	.set	_ZN5ClassC1Ev,_ZN5ClassC2Ev
	.section	.rodata
.LC2:
	.string	"Call destructor, addr = "
	.text
	.align 2
	.globl	_ZN5ClassD2Ev
	.type	_ZN5ClassD2Ev, @function
_ZN5ClassD2Ev:
.LFB1387:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA1387
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
	movl	$.LC2, %esi	#,
	movl	$_ZSt4cout, %edi	#,
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc	#
	movq	%rax, %rdx	#, D.34639
	movq	-8(%rbp), %rax	# this, tmp89
	movq	%rax, %rsi	# tmp89,
	movq	%rdx, %rdi	# D.34639,
	call	_ZNSolsEPKv	#
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi	#,
	movq	%rax, %rdi	# D.34640,
	call	_ZNSolsEPFRSoS_E	#
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1387:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA1387:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1387-.LLSDACSB1387
.LLSDACSB1387:
.LLSDACSE1387:
	.text
	.size	_ZN5ClassD2Ev, .-_ZN5ClassD2Ev
	.globl	_ZN5ClassD1Ev
	.set	_ZN5ClassD1Ev,_ZN5ClassD2Ev
	.globl	main
	.type	main, @function
main:
.LFB1389:
	.cfi_startproc
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%fs:40, %rax	#, tmp93
	movq	%rax, -8(%rbp)	# tmp93, D.34643
	xorl	%eax, %eax	# tmp93
	leaq	-16(%rbp), %rax	#, tmp89
	movq	%rax, %rdi	# tmp89,
	call	_ZN5ClassC1Ev	#
	leaq	-16(%rbp), %rax	#, tmp90
	movq	%rax, %rdi	# tmp90,
	call	_ZN5ClassD1Ev	#
	leaq	-16(%rbp), %rax	#, tmp91
	movq	%rax, %rdi	# tmp91,
	call	_ZN5ClassD1Ev	#
	movl	$0, %eax	#, D.34642
	movq	-8(%rbp), %rdx	# D.34643, tmp94
	xorq	%fs:40, %rdx	#, tmp94
	je	.L5	#,
	call	__stack_chk_fail	#
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1389:
	.size	main, .-main
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB1579:
	.cfi_startproc
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movl	%edi, -4(%rbp)	# __initialize_p, __initialize_p
	movl	%esi, -8(%rbp)	# __priority, __priority
	cmpl	$1, -4(%rbp)	#, __initialize_p
	jne	.L8	#,
	cmpl	$65535, -8(%rbp)	#, __priority
	jne	.L8	#,
	movl	$_ZStL8__ioinit, %edi	#,
	call	_ZNSt8ios_base4InitC1Ev	#
	movl	$__dso_handle, %edx	#,
	movl	$_ZStL8__ioinit, %esi	#,
	movl	$_ZNSt8ios_base4InitD1Ev, %edi	#,
	call	__cxa_atexit	#
.L8:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1579:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I__ZN5ClassC2Ev, @function
_GLOBAL__sub_I__ZN5ClassC2Ev:
.LFB1580:
	.cfi_startproc
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movl	$65535, %esi	#,
	movl	$1, %edi	#,
	call	_Z41__static_initialization_and_destruction_0ii	#
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1580:
	.size	_GLOBAL__sub_I__ZN5ClassC2Ev, .-_GLOBAL__sub_I__ZN5ClassC2Ev
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__ZN5ClassC2Ev
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.12) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
