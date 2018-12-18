jal	main
li	$v0, 10
syscall	
main:	
subiu	$sp, $sp, 16
sw	$ra, 12($sp)
addiu	$t0, $sp, 8
li	$t1, 1
sw	$t1, 0($t0)
addiu	$t0, $sp, 4
li	$t1, 2
sw	$t1, 0($t0)
addiu	$t0, $sp, 0
li	$t1, 3
sw	$t1, 0($t0)
addiu	$t0, $sp, 8
addiu	$t1, $sp, 0
lw	$t2, 0($t0)
lw	$t0, 0($t1)
add	$t1, $t2, $t0
li	$t0, 3
add	$t2, $t1, $t0
li	$t0, 3
li	$t1, 5
mul	$t3, $t0, $t1
addiu	$t0, $sp, 0
lw	$t1, 0($t0)
div	$t3, $t1
mflo	$t0
sub	$t1, $t2, $t0
addiu	$t0, $sp, 0
sw	$t1, 0($t0)
li	$t0, 0
move	$v0, $t0
lw	$ra, 12($sp)
addiu	$sp, $sp, 16
jr	$ra
