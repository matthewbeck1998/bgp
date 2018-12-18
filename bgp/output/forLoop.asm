start:	
jal	main
li	$v0, 10
syscall	
main:	
subiu	$sp, $sp, 8
sw	$ra, 4($sp)
addiu	$t0, $sp, 0
li	$t1, 5
sw	$t1, 0($t0)
addiu	$t0, $sp, 0
lw	$t1, 0($t0)
li	$t0, 1
sub	$t2, $t1, $t0
addiu	$t0, $sp, 0
sw	$t2, 0($t0)
$l1:	
addiu	$t0, $sp, 0
lw	$t1, 0($t0)
li	$t0, 0
bgt	$t1, $t0, $l3
li	$t0, 0
j	$l4
$l3:	
li	$t1, 1
$l4:	
bne	$t0, 0, $l0
j	$l2
$l0:	
addiu	$t0, $sp, 0
lw	$t2, 0($t0)
li	$t0, 1
sub	$t3, $t2, $t0
addiu	$t0, $sp, 0
sw	$t3, 0($t0)
j	$l1
$l2:	
li	$t0, 0
move	$v0, $t0
lw	$ra, 4($sp)
addiu	$sp, $sp, 8
jr	$ra
