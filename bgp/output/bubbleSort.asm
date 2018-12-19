start:	
jal	main
li	$v0, 10
syscall	
main:	
subiu	$sp, $sp, 120
sw	$ra, 116($sp)
addiu	$t0, $sp, 12
li	$t1, 0
sw	$t1, 0($t0)
$l2:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
li	$t0, 25
blt	$t1, $t0, $l4
li	$s7, 0
j	$l5
$l4:	
li	$s7, 1
$l5:	
bne	$s7, $0, $l1
j	$l3
$l1:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
mul	$t0, $t1, 4
addiu	$t1, $t0, 16
addiu	$t0, $sp, 12
lw	$t2, 0($t0)
li	$t0, 24
sub	$t3, $t0, $t2
addu	$t0, $sp, $t1
sw	$t3, 0($t0)
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
li	$t0, 1
add	$t2, $t1, $t0
addiu	$t0, $sp, 12
sw	$t2, 0($t0)
j	$l2
$l3:	
addiu	$t0, $sp, 12
li	$t1, 0
sw	$t1, 0($t0)
$l7:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
li	$t0, 24
blt	$t1, $t0, $l9
li	$s7, 0
j	$l10
$l9:	
li	$s7, 1
$l10:	
bne	$s7, $0, $l6
j	$l8
$l6:	
addiu	$t0, $sp, 8
li	$t1, 0
sw	$t1, 0($t0)
$l12:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
li	$t0, 24
sub	$t2, $t0, $t1
li	$t0, 1
sub	$t1, $t2, $t0
addiu	$t0, $sp, 8
lw	$t2, 0($t0)
blt	$t2, $l14
li	$s7, 0
j	$l15
$l14:	
li	$s7, 1
$l15:	
bne	$s7, $0, $l11
j	$l13
$l11:	
addiu	$t0, $sp, 8
lw	$t2, 0($t0)
mul	$t0, $t2, 4
addiu	$t2, $t0, 16
addiu	$t0, $sp, 8
lw	$t3, 0($t0)
li	$t0, 1
add	$t4, $t3, $t0
mul	$t0, $t4, 4
addiu	$t3, $t0, 16
addu	$t0, $sp, $t2
addu	$t2, $sp, $t3
lw	$t3, 0($t0)
lw	$t0, 0($t2)
bgt	$t3, $t0, $l16
li	$s7, 0
j	$l17
$l16:	
li	$s7, 1
$l17:	
bne	$s7, $0, $l18
j	$l19
$l18:	
addiu	$t0, $sp, 8
lw	$t2, 0($t0)
mul	$t0, $t2, 4
addiu	$t2, $t0, 16
addu	$t0, $sp, $t2
addiu	$t2, $sp, 4
lw	$t3, 0($t0)
sw	$t3, 0($t2)
addiu	$t0, $sp, 8
lw	$t2, 0($t0)
mul	$t0, $t2, 4
addiu	$t2, $t0, 16
addiu	$t0, $sp, 8
lw	$t3, 0($t0)
li	$t0, 1
add	$t4, $t3, $t0
mul	$t0, $t4, 4
addiu	$t3, $t0, 16
addu	$t0, $sp, $t3
addu	$t3, $sp, $t2
lw	$t2, 0($t0)
sw	$t2, 0($t3)
addiu	$t0, $sp, 8
lw	$t2, 0($t0)
li	$t0, 1
add	$t3, $t2, $t0
mul	$t0, $t3, 4
addiu	$t2, $t0, 16
addiu	$t0, $sp, 4
addu	$t3, $sp, $t2
lw	$t2, 0($t0)
sw	$t2, 0($t3)
$l19:	
addiu	$t0, $sp, 8
lw	$t2, 0($t0)
li	$t0, 1
add	$t3, $t2, $t0
addiu	$t0, $sp, 8
sw	$t3, 0($t0)
j	$l12
$l13:	
addiu	$t0, $sp, 12
lw	$t2, 0($t0)
li	$t0, 1
add	$t3, $t2, $t0
addiu	$t0, $sp, 12
sw	$t3, 0($t0)
j	$l7
$l8:	
li	$t0, 0
move	$v0, $t0
j	$l0
$l0:	
lw	$ra, 116($sp)
addiu	$sp, $sp, 120
jr	$ra
