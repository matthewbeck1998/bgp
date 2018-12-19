start:	
jal	main
li	$v0, 10
syscall	
printInt:	
subiu	$sp, $sp, 8
sw	$ra, 4($sp)
addiu	$t0, $sp, 0
sw	$a0, 0($t0)
addiu	$t0, $sp, 0
lw	$t1, 0($t0)
move	$a0, $t1
li	$v0, 1
syscall	
$l0:	
lw	$ra, 4($sp)
addiu	$sp, $sp, 8
jr	$ra
main:	
subiu	$sp, $sp, 32
sw	$ra, 28($sp)
addiu	$t0, $sp, 24
li	$t1, 0
sw	$t1, 0($t0)
$l3:	
addiu	$t0, $sp, 24
lw	$t1, 0($t0)
li	$t0, 5
blt	$t1, $t0, $l5
li	$s7, 0
j	$l6
$l5:	
li	$s7, 1
$l6:	
bne	$s7, $0, $l2
j	$l4
$l2:	
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
j	$l3
$l4:	
addiu	$t0, $sp, 24
li	$t1, 0
sw	$t1, 0($t0)
$l8:	
addiu	$t0, $sp, 24
lw	$t1, 0($t0)
li	$t0, 5
blt	$t1, $t0, $l10
li	$s7, 0
j	$l11
$l10:	
li	$s7, 1
$l11:	
bne	$s7, $0, $l7
j	$l9
$l7:	
addiu	$t0, $sp, 24
lw	$t1, 0($t0)
mul	$t0, $t1, 4
addiu	$t1, $t0, 4
addu	$t0, $sp, $t1
lw	$t1, 0($t0)
move	$a0, $t1
jal	printInt
addiu	$t0, $sp, 24
lw	$t1, 0($t0)
li	$t0, 1
add	$t2, $t1, $t0
addiu	$t0, $sp, 24
sw	$t2, 0($t0)
j	$l8
$l9:	
$l1:	
lw	$ra, 28($sp)
addiu	$sp, $sp, 32
jr	$ra
