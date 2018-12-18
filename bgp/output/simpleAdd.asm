func	main, 16
addiu	$t0, $sp, FS
subiu	$t1, $t0, getOffset(x)
li	$t0, 1
sw	$t0, 0($t1)
addiu	$t0, $sp, FS
subiu	$t1, $t0, getOffset(y)
li	$t0, 2
sw	$t0, 0($t1)
addiu	$t0, $sp, FS
subiu	$t1, $t0, getOffset(z)
li	$t0, 3
sw	$t0, 0($t1)
addiu	$t0, $sp, FS
subiu	$t1, $t0, getOffset(x)
addiu	$t0, $sp, FS
subiu	$t2, $t0, getOffset(z)
lw	$t0, 0($t1)
lw	$t1, 0($t2)
add	$t2, $t0, $t1
addiu	$t0, $sp, FS
subiu	$t1, $t0, getOffset(z)
sw	$t2, 0($t1)
li	$t0, 0
ret	$t18
