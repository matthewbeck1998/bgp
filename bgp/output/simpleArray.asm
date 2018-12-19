start:	
jal	main
li	$v0, 10
syscall	
main:	
subiu	$sp, $sp, 32
sw	$ra, 28($sp)
addiu	$t0, $sp, 24
li	$t1, 0
sw	$t1, 0($t0)
$l2:	
addiu	$t0, $sp, 24
lw	$t1, 0($t0)
li	$t0, 5
blt	$t1, $t0, $l4
li	$s7, 0
j	$l5
$l4:	
li	$s7, 1
$l5:	
bne	$s7, $0, $l1
j	$l3
$l1:	
addiu	$t0, $sp, 24
lw	$t1, 0($t0)
mul	$t0, $t1, 4
addiu	$t1, $t0, 4
addiu	$t0, $sp, 24
addu	$t2, $sp, $t1
lw	$t1, 0($t0)
sw	$t1, 0($t2)
addiu	$t0, $sp, 24
lw	$t1, 0($t0)
li	$t0, 1
add	$t2, $t1, $t0
addiu	$t0, $sp, 24
sw	$t2, 0($t0)
j	$l2
$l3:	
$l0:	
lw	$ra, 28($sp)
addiu	$sp, $sp, 32
jr	$ra
