	.file	"test.c"
	.text
	.type	add, @function
add:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
	leal	(%edx,%eax), %eax
	popl	%ebp
	ret
	.size	add, .-add
	.type	add_as, @function
add_as:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
#APP
# 12 "test.c" 1
	movl %eax ,%eax;addl %edx, %eax;
# 0 "" 2
#NO_APP
	popl	%ebp
	ret
	.size	add_as, .-add_as
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$16, %esp
	movl	$3, 4(%esp)
	movl	$2, (%esp)
	call	add
	movl	$.LC0, %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	printf
	movl	$3, 4(%esp)
	movl	$2, (%esp)
	call	add_as
	movl	$.LC0, %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	printf
	movl	$0, %eax
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.4.4-14ubuntu5) 4.4.5"
	.section	.note.GNU-stack,"",@progbits
