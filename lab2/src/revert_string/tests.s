	.file	"tests.c"
	.section	.rodata
.LC0:
	.string	""
.LC1:
	.string	"tests.c"
.LC2:
	.string	"CU_PASS(\"ok\")"
	.text
	.globl	testRevertString
	.type	testRevertString, @function
testRevertString:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	addq	$-128, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$1819043144, -48(%rbp)
	movw	$111, -44(%rbp)
	movabsq	$8583974613681337427, %rax
	movq	%rax, -32(%rbp)
	movabsq	$7161128522263065705, %rax
	movq	%rax, -24(%rbp)
	movw	$29541, -16(%rbp)
	movb	$0, -14(%rbp)
	movl	$6513249, -128(%rbp)
	movl	$1684234849, -64(%rbp)
	movb	$0, -60(%rbp)
	movl	$3355185, -112(%rbp)
	movl	$6513249, -96(%rbp)
	movl	$6517602, -80(%rbp)
	movl	$0, %r9d
	movl	$.LC0, %r8d
	movl	$.LC1, %ecx
	movl	$.LC2, %edx
	movl	$39, %esi
	movl	$1, %edi
	call	CU_assertImplementation
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L2
	call	__stack_chk_fail
.L2:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	testRevertString, .-testRevertString
	.globl	testRevertString2
	.type	testRevertString2, @function
testRevertString2:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$3355185, -48(%rbp)
	movl	$6513249, -32(%rbp)
	movl	$6517602, -16(%rbp)
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L4
	call	__stack_chk_fail
.L4:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	testRevertString2, .-testRevertString2
	.globl	testRevertString3
	.type	testRevertString3, @function
testRevertString3:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$3355185, -48(%rbp)
	movl	$6513249, -32(%rbp)
	movl	$6517602, -16(%rbp)
	leaq	-32(%rbp), %rdx
	leaq	-48(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Swap
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L6
	call	__stack_chk_fail
.L6:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	testRevertString3, .-testRevertString3
	.section	.rodata
.LC3:
	.string	"Suite"
.LC4:
	.string	"test of RevertString function"
	.align 8
.LC5:
	.string	"test of RevertString2 function"
	.text
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	$0, -8(%rbp)
	call	CU_initialize_registry
	testl	%eax, %eax
	je	.L8
	call	CU_get_error
	jmp	.L9
.L8:
	movl	$0, %edx
	movl	$0, %esi
	movl	$.LC3, %edi
	call	CU_add_suite
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L10
	call	CU_cleanup_registry
	call	CU_get_error
	jmp	.L9
.L10:
	movq	-8(%rbp), %rax
	movl	$testRevertString, %edx
	movl	$.LC4, %esi
	movq	%rax, %rdi
	call	CU_add_test
	testq	%rax, %rax
	jne	.L11
	call	CU_cleanup_registry
	call	CU_get_error
	jmp	.L9
.L11:
	movq	-8(%rbp), %rax
	movl	$testRevertString2, %edx
	movl	$.LC5, %esi
	movq	%rax, %rdi
	call	CU_add_test
	testq	%rax, %rax
	jne	.L12
	call	CU_cleanup_registry
	call	CU_get_error
	jmp	.L9
.L12:
	movl	$2, %edi
	call	CU_basic_set_mode
	call	CU_basic_run_tests
	call	CU_cleanup_registry
	call	CU_get_error
.L9:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
