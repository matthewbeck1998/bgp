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
subiu	$sp, $sp, 128
sw	$ra, 124($sp)
addiu	$t0, $sp, 12
li	$t1, 0
sw	$t1, 0($t0)
$l3:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
li	$t0, 3
blt	$t1, $t0, $l5
li	$s7, 0
j	$l6
$l5:	
li	$s7, 1
$l6:	
bne	$s7, $0, $l2
j	$l4
$l2:	
addiu	$t0, $sp, 8
li	$t1, 0
sw	$t1, 0($t0)
$l8:	
addiu	$t0, $sp, 8
lw	$t1, 0($t0)
li	$t0, 3
blt	$t1, $t0, $l10
li	$s7, 0
j	$l11
$l10:	
li	$s7, 1
$l11:	
bne	$s7, $0, $l7
j	$l9
$l7:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
mul	$t0, $t1, 3
addiu	$t1, $sp, 8
lw	$t2, 0($t1)
add	$t1, $t2, $t0
mul	$t0, $t1, 4
addu	$t1, $t0, 88
addiu	$t0, $sp, 12
addiu	$t2, $sp, 8
lw	$t3, 0($t0)
lw	$t0, 0($t2)
add	$t2, $t3, $t0
addu	$t0, $sp, $t1
sw	$t2, 0($t0)
addiu	$t0, $sp, 88
lw	$t1, 0($t0)
move	$a0, $t1
jal	printInt
addiu	$t0, $sp, 8
lw	$t1, 0($t0)
li	$t0, 1
add	$t2, $t1, $t0
addiu	$t0, $sp, 8
sw	$t2, 0($t0)
j	$l8
$l9:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
li	$t0, 1
add	$t2, $t1, $t0
addiu	$t0, $sp, 12
sw	$t2, 0($t0)
j	$l3
$l4:	
addiu	$t0, $sp, 12
li	$t1, 0
sw	$t1, 0($t0)
$l13:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
li	$t0, 3
blt	$t1, $t0, $l15
li	$s7, 0
j	$l16
$l15:	
li	$s7, 1
$l16:	
bne	$s7, $0, $l12
j	$l14
$l12:	
addiu	$t0, $sp, 8
li	$t1, 0
sw	$t1, 0($t0)
$l18:	
addiu	$t0, $sp, 8
lw	$t1, 0($t0)
li	$t0, 3
blt	$t1, $t0, $l20
li	$s7, 0
j	$l21
$l20:	
li	$s7, 1
$l21:	
bne	$s7, $0, $l17
j	$l19
$l17:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
mul	$t0, $t1, 3
addiu	$t1, $sp, 8
lw	$t2, 0($t1)
add	$t1, $t2, $t0
mul	$t0, $t1, 4
addu	$t1, $t0, 52
addiu	$t0, $sp, 12
lw	$t2, 0($t0)
mul	$t0, $t2, 3
addiu	$t2, $sp, 8
lw	$t3, 0($t2)
add	$t2, $t3, $t0
mul	$t0, $t2, 4
addu	$t2, $t0, 88
addu	$t0, $sp, $t2
addu	$t2, $sp, $t1
lw	$t1, 0($t0)
sw	$t1, 0($t2)
addiu	$t0, $sp, 52
lw	$t1, 0($t0)
move	$a0, $t1
jal	printInt
addiu	$t0, $sp, 8
lw	$t1, 0($t0)
li	$t0, 1
add	$t2, $t1, $t0
addiu	$t0, $sp, 8
sw	$t2, 0($t0)
j	$l18
$l19:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
li	$t0, 1
add	$t2, $t1, $t0
addiu	$t0, $sp, 12
sw	$t2, 0($t0)
j	$l13
$l14:	
addiu	$t0, $sp, 12
li	$t1, 0
sw	$t1, 0($t0)
$l23:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
li	$t0, 3
blt	$t1, $t0, $l25
li	$s7, 0
j	$l26
$l25:	
li	$s7, 1
$l26:	
bne	$s7, $0, $l22
j	$l24
$l22:	
addiu	$t0, $sp, 8
li	$t1, 0
sw	$t1, 0($t0)
$l28:	
addiu	$t0, $sp, 8
lw	$t1, 0($t0)
li	$t0, 3
blt	$t1, $t0, $l30
li	$s7, 0
j	$l31
$l30:	
li	$s7, 1
$l31:	
bne	$s7, $0, $l27
j	$l29
$l27:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
mul	$t0, $t1, 3
addiu	$t1, $sp, 8
lw	$t2, 0($t1)
add	$t1, $t2, $t0
mul	$t0, $t1, 4
addu	$t1, $t0, 16
addu	$t0, $sp, $t1
li	$t1, 0
sw	$t1, 0($t0)
addiu	$t0, $sp, 4
li	$t1, 0
sw	$t1, 0($t0)
$l33:	
addiu	$t0, $sp, 4
lw	$t1, 0($t0)
li	$t0, 3
blt	$t1, $t0, $l35
li	$s7, 0
j	$l36
$l35:	
li	$s7, 1
$l36:	
bne	$s7, $0, $l32
j	$l34
$l32:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
mul	$t0, $t1, 3
addiu	$t1, $sp, 8
lw	$t2, 0($t1)
add	$t1, $t2, $t0
mul	$t0, $t1, 4
addu	$t1, $t0, 16
addiu	$t0, $sp, 12
lw	$t2, 0($t0)
mul	$t0, $t2, 3
addiu	$t2, $sp, 8
lw	$t3, 0($t2)
add	$t2, $t3, $t0
mul	$t0, $t2, 4
addu	$t2, $t0, 16
addiu	$t0, $sp, 12
lw	$t3, 0($t0)
mul	$t0, $t3, 3
addiu	$t3, $sp, 4
lw	$t4, 0($t3)
add	$t3, $t4, $t0
mul	$t0, $t3, 4
addu	$t3, $t0, 88
addiu	$t0, $sp, 4
lw	$t4, 0($t0)
mul	$t0, $t4, 3
addiu	$t4, $sp, 8
lw	$t5, 0($t4)
add	$t4, $t5, $t0
mul	$t0, $t4, 4
addu	$t4, $t0, 52
addu	$t0, $sp, $t3
addu	$t3, $sp, $t4
lw	$t4, 0($t0)
lw	$t0, 0($t3)
mul	$t3, $t4, $t0
addu	$t0, $sp, $t2
lw	$t2, 0($t0)
add	$t0, $t2, $t3
addu	$t2, $sp, $t1
sw	$t0, 0($t2)
addiu	$t0, $sp, 4
lw	$t1, 0($t0)
li	$t0, 1
add	$t2, $t1, $t0
addiu	$t0, $sp, 4
sw	$t2, 0($t0)
j	$l33
$l34:	
addiu	$t0, $sp, 16
lw	$t1, 0($t0)
move	$a0, $t1
jal	printInt
addiu	$t0, $sp, 8
lw	$t1, 0($t0)
li	$t0, 1
add	$t2, $t1, $t0
addiu	$t0, $sp, 8
sw	$t2, 0($t0)
j	$l28
$l29:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
li	$t0, 1
add	$t2, $t1, $t0
addiu	$t0, $sp, 12
sw	$t2, 0($t0)
j	$l23
$l24:	
li	$t0, 0
move	$v0, $t0
j	$l1
$l1:	
lw	$ra, 124($sp)
addiu	$sp, $sp, 128
jr	$ra
