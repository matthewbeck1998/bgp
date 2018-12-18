start:	
jal	main
li	$v0, 10
syscall	
main:	
subiu	$sp, $sp, 8
sw	$ra, 4($sp)
addiu	$t0, $sp, 0
li	$t1, 1
sw	$t1, 0($t0)
addiu	$t0, $sp, 0
lw	$t1, 0($t0)
li	$t0, 1
beq	$t1, $t0, $l1
li	$s7, 0
j	$l2
$l1:	
li	$s7, 1
$l2:	
bne	$s7, $0, $l3
addiu	$t0, $sp, 0
lw	$t1, 0($t0)
li	$t0, 2
beq	$t1, $t0, $l5
li	$s7, 0
j	$l6
$l5:	
li	$s7, 1
$l6:	
bne	$s7, $0, $l7
j	$l8
$l7:	
addiu	$t0, $sp, 0
li	$t1, 3
sw	$t1, 0($t0)
li	$t0, 0
move	$v0, $t0
j	$l0
$l8:	
j	$l4
$l3:	
addiu	$t0, $sp, 0
li	$t1, 2
sw	$t1, 0($t0)
li	$t0, 0
move	$v0, $t0
j	$l0
$l4:	
li	$t0, 0
move	$v0, $t0
j	$l0
$l0:	
lw	$ra, 4($sp)
addiu	$sp, $sp, 8
jr	$ra
