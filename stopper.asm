	add 	$sp, $zero, $zero, $zero, 512		# 0: set $sp = 512
	#lw 	$a0, $zero, $zero, $zero, 0x100		## 1: get n from address 256
	#lw		$a1, $zero, $zero, $zero, 0x101		## 2: get k from address 257
	in		$t0,  $zero, $zero, $zero, 0		# 1: set $t0 = IORegister[0]
	jal 	$zero, $zero, $zero, $zero, binom	# 3: calc $v0 = binom(n, k)
	sw 	$v0, $zero, $zero, $zero, 0x102		# 4: store binom(n, k) in 258
	halt $zero, $zero, $zero, $zero, 0		# 5: halt

binom:	
	sub	$sp, $sp, $zero, $zero, 4		# 6: adjust stack for 4 items
	sw	$s0, $sp, $zero, $zero, 3		# 7: save $s0
	sw	$s1, $sp, $zero, $zero, 2		# 8: save $s1
	sw	$s2, $sp, $zero, $zero, 1		# 9: save $s2
	sw	$ra, $sp, $zero, $zero, 0		# a: save return address
	
	add	$s2, $zero, $zero, $zero, 513		# b: table to store calculation values C[n + 1][k + 1] starts at this address
	
	add	$s0, $zero, $zero, $zero, 0		# c: i = 0
loop_i:
	branch	$zero, $s0, $a0, 2, return		# d: break loop when i > n
	add	$s1, $zero, $zero, $zero, 0		# e: j = 0
	add	$t0, $zero, $s0, $zero, 0		# f: $t0 = i
	branch	$zero, $s0, $a1, 3, loop_j		# 10: if i is min(i, k) j loop runs up to i
	add	$t0, $zero, $a1, $zero, 0		# 11: k is min(i, k) and j loop runs up to k

	
loop_j:
	branch 	$zero, $s1, $t0, 2, end_j		# 12: break loop when j > min(i, k)
	
	branch	$zero, $s1, $zero, 0, base		# 13: j == 0 is base case
	branch	$zero, $s1, $s0, 0, base		# 14: j == i is base case
	
	sub	$t1, $s0, $zero, $zero, 1		# 15: $t1 = i - 1
	sub	$t2, $s1, $zero, $zero, 1		# 16: $t2 = j - 1
	add	$t3, $a1, $zero, $zero, 1		# 17: $t3 = k + 1
	
	mac	$t2, $t1, $t3, $t2, 0			# 18: $t2 = (i-1) * (k+1) + (j-1)
	mac	$t1, $t1, $t3, $s1, 0			# 19: $t1 = (i-1) * (k+1) + j
	
	add	$t2, $s2, $t2, $zero, 0			# 1a: $t2 = &C[i-1][j-1]
	lw	$t2, $t2, $zero, $zero, 0		# 1b: $t2 = C[i-1][j-1]
	
	add	$t1, $s2, $t1, $zero, 0			# 1c: $t1 = &C[i-1][j]
	lw	$t1, $t1, $zero, $zero, 0		# 1d: $t1 = C[i-1][j]
	
	add	$t1, $t1, $t2, $zero, 0			# 1e: $t1 = C[i-1][j-1] + C[i-1][j]
	branch	$zero, $zero, $zero, 0, set_mem 	# 1f: set dynamic memory
	 
base:
	add	$t1, $zero, $zero, $zero, 1		# 20: $t1 = 1
	
set_mem:	
	add	$t3, $a1, $zero, $zero, 1		# 21: $t3 = k + 1
	mac	$t2, $s0, $t3, $s1, 0			# 22: $t2 = i * (k+1) + j
	add	$t2, $s2, $t2, $zero, 0			# 23: $t2 = &C[i][j]
	sw	$t1, $t2, $zero, $zero, 0		# 24: C[i][j] = C[i-1][j-1] + C[i-1][j]
	
	add	$s1, $s1, $zero, $zero, 1		# 25: j++
	branch	$zero, $zero, $zero, 0, loop_j		# 26: continue j loop

end_j:
	add	$s0, $s0, $zero, $zero, 1		# 27: i++
	branch	$zero, $zero, $zero, 0, loop_i		# 28: continue i loop

return:
	add	$t0, $a1, $zero, $zero, 1		# 29: $t0 = k + 1
	mac	$t1, $a0, $t0, $a1, 0			# 2a: $t1 = n * (k+1) + k
	add	$t1, $s2, $t1, $zero, 0			# 2b: $t1 = &C[n][k]
	lw	$v0, $t1, $zero, $zero, 0		# 2c: $v0 = C[n][k]
	
	lw	$ra, $sp, $zero, $zero, 0		# 2d: restore return address
	lw	$s2, $sp, $zero, $zero, 1		# 2e: restore $s2
	lw	$s1, $sp, $zero, $zero, 2		# 2f: restore $s1
	lw	$s0, $sp, $zero, $zero, 3		# 30: restore $s0
	add	$sp, $sp, $zero, $zero, 4		# 31: pop 4 items from stack
	jr	$ra, $zero, $zero, $zero, 0		# 32: and return
	
	.word	256 5
	.word	257 2
	
