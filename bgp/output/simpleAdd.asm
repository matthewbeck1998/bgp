start:
	jal	main
	li	$v0, 10
	syscall
main:
	subiu	$sp, $sp, 16	# Allocate 16 bytes for the stack frame
	sw	$ra, 12($sp)	# Save the return address
	
	li	$t0, 1		# $t0 = 1					x = 1;
	sw	$t0, 8($sp)	# x = $t0					x = 1;
	li	$t1, 2		# $t1 = 2					y = 2;
	sw	$t1, 4($sp)	# y = $t1					y = 2;
	li	$t2, 3		# $t2 = 3					z = 3;
	sw	$t2, 0($sp)	# z = $t2					z = 3;
	lw	$t3, 8($sp)	# $t3 = x					z = x + z;
	lw	$t4, 0($sp)	# $t4 = z					z = x + z;
	add	$t5, $t3, $t4	# $t5 = $t3 + $t4				z = x + z;
	sw	$t5, 0($sp)	# z = $t5					z = x + z;
	li	$v0, 0		# $v0 = 0					return 0;
	
	lw	$ra, 12($sp)	# Restore the return address
	addiu	$sp, $sp, 16	# Deallocate 16 bytes for the stack frame
	jr	$ra		# Jump back to caller
