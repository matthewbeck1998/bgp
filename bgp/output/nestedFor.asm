start:	
jal	main
li	$v0, 10
syscall	
main:	
subiu	$sp, $sp, 16
sw	$ra, 12($sp)
addiu	$t0, $sp, 0
li	$t1, 0
sw	$t1, 0($t0)
addiu	$t0, $sp, 8
li	$t1, 0
sw	$t1, 0($t0)
$l1:	
addiu	$t0, $sp, 8
lw	$t1, 0($t0)
li	$t0, 3
blt	$t1, $t0, $l3
li	$s7, 0
j	$l4
$l3:	
li	$s7, 1
$l4:	
bne	$s7, $0, $l0
j	$l2
$l0:	
addiu	$t0, $sp, 4
li	$t1, 0
sw	$t1, 0($t0)
$l6:	
addiu	$t0, $sp, 4
lw	$t1, 0($t0)
li	$t0, 3
blt	$t1, $t0, $l8
li	$s7, 0
j	$l9
$l8:	
li	$s7, 1
$l9:	
bne	$s7, $0, $l5
j	$l7
$l5:	
addiu	$t0, $sp, 0
lw	$t1, 0($t0)
li	$t0, 1
add	$t2, $t1, $t0
addiu	$t0, $sp, 0
sw	$t2, 0($t0)
addiu	$t0, $sp, 8
lw	$t1, 0($t0)
li	$t0, 1
add	$t2, $t1, $t0
addiu	$t0, $sp, 8
sw	$t2, 0($t0)
j	$l6
$l7:	
addiu	$t0, $sp, 8
lw	$t1, 0($t0)
li	$t0, 1
add	$t2, $t1, $t0
addiu	$t0, $sp, 8
sw	$t2, 0($t0)
j	$l1
$l2:	
lw	$ra, 12($sp)
addiu	$sp, $sp, 16
jr	$ra
