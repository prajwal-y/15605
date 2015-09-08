/*
 * traceback_helper.S
 * Author: Prajwal Yadapadithaya (pyadapad)
 */

.global get_next_ret_addr
.global get_cur_ebp
.global get_next_ebp

get_next_ret_addr:
	pushl	%ebp		
	movl	%esp,%ebp	
	pushl	%edi
	pushl	%ebx
	pushl	%esi
	
  movl	8(%ebp),%ebx	/* get the argument */
	movl	4(%ebx),%eax	/* save the return address */

	popl	%esi
	popl	%ebx
	popl	%edi
	movl	%ebp,%esp
	popl	%ebp
	ret

get_cur_ebp:
	movl	%ebp,%eax
	ret

get_next_ebp:
	movl	4(%esp),%ebx
  movl	(%ebx),%eax
  ret
