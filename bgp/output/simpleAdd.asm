addiu	$t0, $sp, 8
li	$t1, 1
sw	$t1, 0($t1)
addiu	$t1, $sp, 4
li	$t2, 2
sw	$t2, 0($t2)
addiu	$t2, $sp, 0
li	$t3, 3
sw	$t3, 0($t3)
addiu	$t3, $sp, 8
addiu	$t4, $sp, 0
lw	$t5, 0($t3)
lw	$t3, 0($t4)
add	$t4, $t5, $t3
li	$t3, 3
add	$t5, $t4, $t3
li	$t3, 3
li	$t4, 5
mul	$t6, $t3, $t4
addiu	$t3, $sp, 0
lw	$t4, 0($t3)
div	$t6, $t4
mflo	$t3
sub	$t4, $t5, $t3
addiu	$t3, $sp, 0
sw	$t4, 0($t3)
