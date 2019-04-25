	.file	"test.c"
	.section	.rodata
.LC0:
	.string	"hello, world"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	leaq	.LC0(%rip), %rdi
	call	puts@PLT
	movl	$0, -4(%rbp)
	movl	-4(%rbp), %eax
	cmpl	$1, %eax
	je	.L3
	cmpl	$1, %eax
	jg	.L4
	testl	%eax, %eax
	je	.L5
	jmp	.L2
.L4:
	cmpl	$2, %eax
	je	.L6
	cmpl	$5, %eax
	je	.L7
	jmp	.L2
.L3:
	movl	$8, -4(%rbp)
.L6:
	movl	$3, -4(%rbp)
.L5:
	addl	$1, -4(%rbp)
.L7:
	addl	$1, -4(%rbp)
.L2:
	movl	-4(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
