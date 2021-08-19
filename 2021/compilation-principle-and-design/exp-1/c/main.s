	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 11, 0	sdk_version 11, 0
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
LBB0_1:                                 ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB0_3 Depth 2
	cmpl	$100, -8(%rbp)
	jge	LBB0_8
## %bb.2:                               ##   in Loop: Header=BB0_1 Depth=1
	movl	$0, -12(%rbp)
LBB0_3:                                 ##   Parent Loop BB0_1 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	cmpl	$100, -12(%rbp)
	jge	LBB0_6
## %bb.4:                               ##   in Loop: Header=BB0_3 Depth=2
	movl	-8(%rbp), %eax
	addl	-12(%rbp), %eax
	movslq	-8(%rbp), %rcx
	imulq	$400, %rcx, %rcx        ## imm = 0x190
	leaq	_matrix_a(%rip), %rdx
	addq	%rcx, %rdx
	movslq	-12(%rbp), %rcx
	movl	%eax, (%rdx,%rcx,4)
	movl	-8(%rbp), %eax
	imull	-12(%rbp), %eax
	movslq	-12(%rbp), %rcx
	imulq	$400, %rcx, %rcx        ## imm = 0x190
	leaq	_matrix_b(%rip), %rdx
	addq	%rcx, %rdx
	movslq	-8(%rbp), %rcx
	movl	%eax, (%rdx,%rcx,4)
## %bb.5:                               ##   in Loop: Header=BB0_3 Depth=2
	movl	-12(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -12(%rbp)
	jmp	LBB0_3
LBB0_6:                                 ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_7
LBB0_7:                                 ##   in Loop: Header=BB0_1 Depth=1
	movl	-8(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -8(%rbp)
	jmp	LBB0_1
LBB0_8:
	movl	$0, -16(%rbp)
LBB0_9:                                 ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB0_11 Depth 2
                                        ##       Child Loop BB0_13 Depth 3
	cmpl	$100, -16(%rbp)
	jge	LBB0_20
## %bb.10:                              ##   in Loop: Header=BB0_9 Depth=1
	movl	$0, -20(%rbp)
LBB0_11:                                ##   Parent Loop BB0_9 Depth=1
                                        ## =>  This Loop Header: Depth=2
                                        ##       Child Loop BB0_13 Depth 3
	cmpl	$100, -20(%rbp)
	jge	LBB0_18
## %bb.12:                              ##   in Loop: Header=BB0_11 Depth=2
	movl	$0, -24(%rbp)
LBB0_13:                                ##   Parent Loop BB0_9 Depth=1
                                        ##     Parent Loop BB0_11 Depth=2
                                        ## =>    This Inner Loop Header: Depth=3
	cmpl	$100, -24(%rbp)
	jge	LBB0_16
## %bb.14:                              ##   in Loop: Header=BB0_13 Depth=3
	movslq	-16(%rbp), %rax
	imulq	$400, %rax, %rax        ## imm = 0x190
	leaq	_matrix_a(%rip), %rcx
	addq	%rax, %rcx
	movslq	-24(%rbp), %rax
	movl	(%rcx,%rax,4), %edx
	movslq	-24(%rbp), %rax
	imulq	$400, %rax, %rax        ## imm = 0x190
	leaq	_matrix_b(%rip), %rcx
	addq	%rax, %rcx
	movslq	-20(%rbp), %rax
	imull	(%rcx,%rax,4), %edx
	movslq	-16(%rbp), %rax
	imulq	$400, %rax, %rax        ## imm = 0x190
	leaq	_matrix_c(%rip), %rcx
	addq	%rax, %rcx
	movslq	-20(%rbp), %rax
	addl	(%rcx,%rax,4), %edx
	movl	%edx, (%rcx,%rax,4)
## %bb.15:                              ##   in Loop: Header=BB0_13 Depth=3
	movl	-24(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -24(%rbp)
	jmp	LBB0_13
LBB0_16:                                ##   in Loop: Header=BB0_11 Depth=2
	jmp	LBB0_17
LBB0_17:                                ##   in Loop: Header=BB0_11 Depth=2
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
	jmp	LBB0_11
LBB0_18:                                ##   in Loop: Header=BB0_9 Depth=1
	jmp	LBB0_19
LBB0_19:                                ##   in Loop: Header=BB0_9 Depth=1
	movl	-16(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -16(%rbp)
	jmp	LBB0_9
LBB0_20:
	xorl	%eax, %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_matrix_a               ## @matrix_a
.zerofill __DATA,__common,_matrix_a,40000,4
	.globl	_matrix_b               ## @matrix_b
.zerofill __DATA,__common,_matrix_b,40000,4
	.globl	_matrix_c               ## @matrix_c
.zerofill __DATA,__common,_matrix_c,40000,4
.subsections_via_symbols
