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
printSpace:	
subiu	$sp, $sp, 8
sw	$ra, 4($sp)
li	$a0, 32
li	$v0, 11
syscall	
$l1:	
lw	$ra, 4($sp)
addiu	$sp, $sp, 8
jr	$ra
printNewline:	
subiu	$sp, $sp, 8
sw	$ra, 4($sp)
li	$a0, 10
li	$v0, 11
syscall	
$l2:	
lw	$ra, 4($sp)
addiu	$sp, $sp, 8
jr	$ra
main:	
subiu	$sp, $sp, 120
sw	$ra, 116($sp)
addiu	$t0, $sp, 12
li	$t1, 0
sw	$t1, 0($t0)
$l5:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
li	$t0, 25
blt	$t1, $t0, $l7
li	$s7, 0
j	$l8
$l7:	
li	$s7, 1
$l8:	
bne	$s7, $0, $l4
j	$l6
$l4:	
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
j	$l5
$l6:	
addiu	$t0, $sp, 12
li	$t1, 0
sw	$t1, 0($t0)
$l10:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
li	$t0, 25
blt	$t1, $t0, $l12
li	$s7, 0
j	$l13
$l12:	
li	$s7, 1
$l13:	
bne	$s7, $0, $l9
j	$l11
$l9:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
mul	$t0, $t1, 4
addiu	$t1, $t0, 16
addu	$t0, $sp, $t1
lw	$t1, 0($t0)
move	$a0, $t1
jal	printInt
jal	printSpace
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
li	$t0, 1
add	$t2, $t1, $t0
addiu	$t0, $sp, 12
sw	$t2, 0($t0)
j	$l10
$l11:	
jal	printNewline
jal	printNewline
addiu	$t0, $sp, 12
li	$t1, 0
sw	$t1, 0($t0)
$l15:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
li	$t0, 24
blt	$t1, $t0, $l17
li	$s7, 0
j	$l18
$l17:	
li	$s7, 1
$l18:	
bne	$s7, $0, $l14
j	$l16
$l14:	
addiu	$t0, $sp, 8
li	$t1, 0
sw	$t1, 0($t0)
$l20:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
li	$t0, 25
sub	$t2, $t0, $t1
li	$t0, 1
sub	$t1, $t2, $t0
addiu	$t0, $sp, 8
lw	$t2, 0($t0)
blt	$t2, $t1, $l22
li	$s7, 0
j	$l23
$l22:	
li	$s7, 1
$l23:	
bne	$s7, $0, $l19
j	$l21
$l19:	
addiu	$t0, $sp, 8
lw	$t1, 0($t0)
mul	$t0, $t1, 4
addiu	$t1, $t0, 16
addiu	$t0, $sp, 8
lw	$t2, 0($t0)
li	$t0, 1
add	$t3, $t2, $t0
mul	$t0, $t3, 4
addiu	$t2, $t0, 16
addu	$t0, $sp, $t1
addu	$t1, $sp, $t2
lw	$t2, 0($t0)
lw	$t0, 0($t1)
bgt	$t2, $t0, $l24
li	$s7, 0
j	$l25
$l24:	
li	$s7, 1
$l25:	
bne	$s7, $0, $l26
j	$l27
$l26:	
addiu	$t0, $sp, 8
lw	$t1, 0($t0)
mul	$t0, $t1, 4
addiu	$t1, $t0, 16
addu	$t0, $sp, $t1
addiu	$t1, $sp, 4
lw	$t2, 0($t0)
sw	$t2, 0($t1)
addiu	$t0, $sp, 8
lw	$t1, 0($t0)
mul	$t0, $t1, 4
addiu	$t1, $t0, 16
addiu	$t0, $sp, 8
lw	$t2, 0($t0)
li	$t0, 1
add	$t3, $t2, $t0
mul	$t0, $t3, 4
addiu	$t2, $t0, 16
addu	$t0, $sp, $t2
addu	$t2, $sp, $t1
lw	$t1, 0($t0)
sw	$t1, 0($t2)
addiu	$t0, $sp, 8
lw	$t1, 0($t0)
li	$t0, 1
add	$t2, $t1, $t0
mul	$t0, $t2, 4
addiu	$t1, $t0, 16
addiu	$t0, $sp, 4
addu	$t2, $sp, $t1
lw	$t1, 0($t0)
sw	$t1, 0($t2)
$l27:	
addiu	$t0, $sp, 8
lw	$t1, 0($t0)
li	$t0, 1
add	$t2, $t1, $t0
addiu	$t0, $sp, 8
sw	$t2, 0($t0)
j	$l20
$l21:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
li	$t0, 1
add	$t2, $t1, $t0
addiu	$t0, $sp, 12
sw	$t2, 0($t0)
j	$l15
$l16:	
addiu	$t0, $sp, 12
li	$t1, 0
sw	$t1, 0($t0)
$l29:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
li	$t0, 25
blt	$t1, $t0, $l31
li	$s7, 0
j	$l32
$l31:	
li	$s7, 1
$l32:	
bne	$s7, $0, $l28
j	$l30
$l28:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
mul	$t0, $t1, 4
addiu	$t1, $t0, 16
addu	$t0, $sp, $t1
lw	$t1, 0($t0)
move	$a0, $t1
jal	printInt
jal	printSpace
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
li	$t0, 1
add	$t2, $t1, $t0
addiu	$t0, $sp, 12
sw	$t2, 0($t0)
j	$l29
$l30:	
li	$t0, 0
move	$v0, $t0
j	$l3
$l3:	
lw	$ra, 116($sp)
addiu	$sp, $sp, 120
jr	$ra
