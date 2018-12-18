jal	main
li	$v0, 10
syscall	
main:	
subiu	$sp, $sp, 8
sw	$ra, 4($sp)
addiu	$t0, $sp, 0
li	$t1, 3
sw	$t1, 0($t0)
addiu	$t0, $sp, 0
lw	$t1, 0($t0)
li	$t0, 3
beq	$t1, $t0, $l0
li	$t0, 0
j	$l1
$l0:	
li	$t1, 1
$l1:	
bne	$t0, 0, $l2
addiu	$t0, $sp, 0
li	$t2, 2
sw	$t2, 0($t0)
j	$l3
$l2:	
addiu	$t0, $sp, 0
li	$t2, 4
sw	$t2, 0($t0)
$l3:	
addiu	$t0, $sp, 0
li	$t2, 1
sw	$t2, 0($t0)
lw	$ra, 4($sp)
addiu	$sp, $sp, 8
jr	$ra
