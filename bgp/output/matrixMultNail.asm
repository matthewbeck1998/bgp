start:	
jal	main
li	$v0, 10
syscall	
main:	
subiu	$sp, $sp, 128
sw	$ra, 124($sp)
addiu	$t0, $sp, 12
li	$t1, 0
sw	$t1, 0($t0)
$l2:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
li	$t0, 3
blt	$t1, $t0, $l4
li	$s7, 0
j	$l5
$l4:	
li	$s7, 1
$l5:	
bne	$s7, $0, $l1
j	$l3
$l1:	
addiu	$t0, $sp, 8
li	$t1, 0
sw	$t1, 0($t0)
$l7:	
addiu	$t0, $sp, 8
lw	$t1, 0($t0)
li	$t0, 3
blt	$t1, $t0, $l9
li	$s7, 0
j	$l10
$l9:	
li	$s7, 1
$l10:	
bne	$s7, $0, $l6
j	$l8
$l6:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
mul	$t0, $t1, 3
addiu	$t1, $sp, 8
lw	$t2, 0($t1)
add	$t1, $t2, $t0
addiu	$t0, $sp, 12
addiu	$t2, $sp, 8
lw	$t3, 0($t0)
lw	$t0, 0($t2)
add	$t2, $t3, $t0
addu	$t0, $sp, $t1
sw	$t2, 0($t0)
addiu	$t0, $sp, 8
lw	$t1, 0($t0)
li	$t0, 1
add	$t2, $t1, $t0
addiu	$t0, $sp, 8
sw	$t2, 0($t0)
j	$l7
$l8:	
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
$l12:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
li	$t0, 3
blt	$t1, $t0, $l14
li	$s7, 0
j	$l15
$l14:	
li	$s7, 1
$l15:	
bne	$s7, $0, $l11
j	$l13
$l11:	
addiu	$t0, $sp, 8
li	$t1, 0
sw	$t1, 0($t0)
$l17:	
addiu	$t0, $sp, 8
lw	$t1, 0($t0)
li	$t0, 3
blt	$t1, $t0, $l19
li	$s7, 0
j	$l20
$l19:	
li	$s7, 1
$l20:	
bne	$s7, $0, $l16
j	$l18
$l16:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
mul	$t0, $t1, 3
addiu	$t1, $sp, 8
lw	$t2, 0($t1)
add	$t1, $t2, $t0
addiu	$t0, $sp, 12
lw	$t2, 0($t0)
mul	$t0, $t2, 3
addiu	$t2, $sp, 8
lw	$t3, 0($t2)
add	$t2, $t3, $t0
addu	$t0, $sp, $t2
addu	$t2, $sp, $t1
lw	$t1, 0($t0)
sw	$t1, 0($t2)
addiu	$t0, $sp, 8
lw	$t1, 0($t0)
li	$t0, 1
add	$t2, $t1, $t0
addiu	$t0, $sp, 8
sw	$t2, 0($t0)
j	$l17
$l18:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
li	$t0, 1
add	$t2, $t1, $t0
addiu	$t0, $sp, 12
sw	$t2, 0($t0)
j	$l12
$l13:	
addiu	$t0, $sp, 12
li	$t1, 0
sw	$t1, 0($t0)
$l22:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
li	$t0, 3
blt	$t1, $t0, $l24
li	$s7, 0
j	$l25
$l24:	
li	$s7, 1
$l25:	
bne	$s7, $0, $l21
j	$l23
$l21:	
addiu	$t0, $sp, 8
li	$t1, 0
sw	$t1, 0($t0)
$l27:	
addiu	$t0, $sp, 8
lw	$t1, 0($t0)
li	$t0, 3
blt	$t1, $t0, $l29
li	$s7, 0
j	$l30
$l29:	
li	$s7, 1
$l30:	
bne	$s7, $0, $l26
j	$l28
$l26:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
mul	$t0, $t1, 3
addiu	$t1, $sp, 8
lw	$t2, 0($t1)
add	$t1, $t2, $t0
addu	$t0, $sp, $t1
li	$t1, 0
sw	$t1, 0($t0)
addiu	$t0, $sp, 4
li	$t1, 0
sw	$t1, 0($t0)
$l32:	
addiu	$t0, $sp, 4
lw	$t1, 0($t0)
li	$t0, 3
blt	$t1, $t0, $l34
li	$s7, 0
j	$l35
$l34:	
li	$s7, 1
$l35:	
bne	$s7, $0, $l31
j	$l33
$l31:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
mul	$t0, $t1, 3
addiu	$t1, $sp, 8
lw	$t2, 0($t1)
add	$t1, $t2, $t0
addiu	$t0, $sp, 12
lw	$t2, 0($t0)
mul	$t0, $t2, 3
addiu	$t2, $sp, 8
lw	$t3, 0($t2)
add	$t2, $t3, $t0
addiu	$t0, $sp, 12
lw	$t3, 0($t0)
mul	$t0, $t3, 3
addiu	$t3, $sp, 4
lw	$t4, 0($t3)
add	$t3, $t4, $t0
addiu	$t0, $sp, 4
lw	$t4, 0($t0)
mul	$t0, $t4, 3
addiu	$t4, $sp, 8
lw	$t5, 0($t4)
add	$t4, $t5, $t0
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
j	$l32
$l33:	
addiu	$t0, $sp, 8
lw	$t1, 0($t0)
li	$t0, 1
add	$t2, $t1, $t0
addiu	$t0, $sp, 8
sw	$t2, 0($t0)
j	$l27
$l28:	
addiu	$t0, $sp, 12
lw	$t1, 0($t0)
li	$t0, 1
add	$t2, $t1, $t0
addiu	$t0, $sp, 12
sw	$t2, 0($t0)
j	$l22
$l23:	
li	$t0, 0
move	$v0, $t0
j	$l0
$l0:	
lw	$ra, 124($sp)
addiu	$sp, $sp, 128
jr	$ra
