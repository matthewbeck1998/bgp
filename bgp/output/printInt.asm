start:	
jal	main
li	$v0, 10
syscall	
printInt:	
subiu	$sp, $sp, 8
sw	$ra, 4($sp)
addiu	$t0, $sp, 0
sw	$a0, 0($t0)
$l0:	
lw	$ra, 4($sp)
addiu	$sp, $sp, 8
jr	$ra
main:	
subiu	$sp, $sp, 8
sw	$ra, 4($sp)
addiu	$t0, $sp, 0
li	$t1, 1
sw	$t1, 0($t0)
jal	printInt
li	$t0, 0
move	$v0, $t0
j	$l1
$l1:	
lw	$ra, 4($sp)
addiu	$sp, $sp, 8
jr	$ra
