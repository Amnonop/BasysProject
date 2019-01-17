	out		$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0
	out		$zero, $zero, $zero, $zero, 4	# : set IORegister[4] = 0
	in		$t2, $zero, $zero, $zero, 2		# : set $t2 = IORegister[2] - BUTNC state
	add		$s0, $zero, $zero, $zero, 25		# :###UPDATE AFTER PAUSE!
	in		$s2, $zero, $zero, $zero, 0		# : set $s2 = IORegister[0]
	in		$t1, $zero, $zero, $zero, 1		# : set $t1 = IORegister[1]
	in		$t3, $zero, $zero, $zero, 3		# : set $t3 = IORegister[3] - BUTND state

stopper:
	in	$t1, $zero, $zero, $zero, 0				#	branch	$zero, $t2, $a0, 1, pause_1				# : break loop when $a0 != $t0 means IORegister[2] has changed means BTNC was pushed
	in	$a0, $zero, $zero, $zero, 2					# : set $a0 = IORegister[2]
	branch	$zero, $t2, $a0, 1, pause_1				# : break loop when $a0 != $t0 means IORegister[2] has changed means BTNC was pushed
	in	$v0, $zero, $zero, $zero, 3					# : set $a0 = IORegister[3]
	branch	$zero, $t3, $v0, 3, BTND_2				# : break loop when $a0 != $t0 means IORegister[3] has changed
	sub $t1, $t1, $s2, $zero, 0						# : time diff
	branch	$zero, $t1, $s0, 4, update_timer 		#
	branch $zero, $zero, $zero, $zero, stopper		#

update_timer:
	in	$s2, $zero, $zero, $zero, 0				# :(update) set $s0 = IORegister[0]
	in	$s1, $zero, $zero, $zero, 4				# : set $s1 = IORegister[4]
	add $a1, $s1, $zero, $zero, 0				#
	add $t2, $zero, $zero, $zero, 0x9			#
	add $a0, $zero, $zero, $zero, 0x50			#
	and $t1, $a1, $t2, $zero, 0x9				#
	branch	$zero, $t1, $t2, 1, up_sec			#
	and $t1, $a1, $a0, $zero, 0x50				#
	branch	$zero, $t1, $a0, 1, up_ten_sec		#
	sra $at, $a1, $zero, $zero, 8				#
	and $t1, $at, $t2, $zero, 0x9				#
	branch	$zero, $t1, $t2, 1, up_mins			#
	and $t1, $at, $a0, $zero, 0x50				#
	branch	$zero, $t1, $a0, 1, up_ten_mins		#
	in	$a0, $zero, $zero, $zero, 3				# : set $t3 = IORegister[3] - BUTND state
	branch $zero, $zero, $zero, $zero, stopper	#

up_sec:
	add $t2, $zero, $zero, $zero, 0x0		#
	and $t2, $t2, $t2, $zero, 0x0			# compare elasped time to other channels
	add $s1, $s1, $zero, $zero, 0x1			#
	out $s1, $zero, $zero, $zero, 4				# update SSD
	in	$t2, $zero, $zero, $zero, 2			# :
	branch	$zero, $zero, $zero, $zero, stopper	#

up_ten_sec:
	add $t2, $zero, $zero, $zero, 0x0		#
	and $a1, $s1, $s1, $zero, 0xFF0			#
	add $s1, $a1, $zero, $zero, 0x010		#
	out $s1, $zero, $zero, $zero, 4				#
	in	$t2, $zero, $zero, $zero, 2			# :
	branch	$zero, $zero, $zero, $zero, stopper #

up_mins:
	add $t2, $zero, $zero, $zero, 0x0			#
	and $a1, $s1, $s1, $zero, 0xF00				#
	add $s1, $a1, $zero, $zero, 0x100			#
	out $s1, $zero, $zero, $zero, 4				#
	in	$t2, $zero, $zero, $zero, 2			# :
	branch	$zero, $zero, $zero, $zero, stopper #

up_ten_mins:
	in $s1, $zero, $zero, $zero, 4				#
	add	$a1, $s1, $zero, $zero, 0				#
	add $t2, $zero, $zero, $zero, 5				#
	sra	$a1, $a1, $zero, $zero, 12				#
	and $at, $a1, $t2, $zero, 5					#
	branch $zero, $at, $t2, 0, reset_clock		#
	add $a1, $a1, $zero, $zero, 1				#
	sll $s1, $a1, $zero, $zero, 12				#
	out	$s1, $zero, $zero, $zero, 4				# : set IORegister[4] = 0
	in	$t2, $zero, $zero, $zero, 2			# :
	branch	$zero, $zero, $zero, $zero, stopper #

reset_clock:
	out $zero, $zero, $zero, $zero, 4				#
	in	$s1, $zero, $zero, $zero, 4					#
	in	$a0, $zero, $zero, $zero, 2		# : set $a0 = IORegister[2]
	in	$at, $zero, $zero, $zero, 2		# : (update) set $t2 = IORegister[2]
	in	$t2, $zero, $zero, $zero, 2		# : (update) set $t2 = IORegister[2]
	branch	$zero, $zero, $zero, $zero, stopper		#

pause_1:																									# enter PAUSE mode
	in			$t2, 		$zero, 	$zero, 	$zero, 	2								# update current counter of BTNC
	branch	$zero,	$zero,	$zero,	0,			pause_mode			# enter PAUSE mode
	#in	$at, $zero, $zero, $zero, 2		# : (update) set $at = IORegister[2]
	#add	$gp, $zero, $zero, $zero, 1		# :
	#out	$gp, $zero, $zero, $zero, 1		# : set IORegister[1] = 1 means LD0 is on
	#add $gp, $zero, $zero, $zero, 160	# : set $a2 = 160 = 32*5  (5 sec) #stalling for time delay between in $t2 and in	$a0
	#in	$a1, $zero, $zero, $zero, 0		# : set $a1 = IORegister[0]
	#sub	$s0, $a1, $t1, $zero, 0			# : $s0 = $a1 - $t1 (time difference)
			#in	$v0, $zero, $zero, $zero, 3		# : set $a1 = IORegister[3] -> BTND
			#branch	$zero, $t3, $v0, 1, BTND	# : if BTND changed
			#branch	$zero, $s0, $gp, 2, led_change		# : if $s0 > 160
	#branch	$zero, $at, $a0, 1, pause_2			# : break loop when $a0 != $at means IORegister[2]
	#branch $zero, $zero, $zero, $zero, pause_1	# :jump back to pause_1

pause_mode:
	in			$a0, 		$zero, 	$zero, 	$zero, 	2								# $a0 = IORegister[2]
	branch	$zero,	$t2, 		$a0, 		1, 			exit_pause			# if BTNC state changed, exit PAUSE mode
	branch	$zero,	$zero,	$zero,	0,			pause_mode			# continue PAUSE mode

exit_pause:
	in			$t2, 		$zero, 	$zero, 	$zero, 	2								# update current counter of BTNC
	branch	$zero,	$zero,	$zero,	0,			stopper					# enter PAUSE mode

BTND:
	in	$t3, $zero, $zero, $zero, 3		# : update $t3 to new BTND state
	in	$v0, $zero, $zero, $zero, 3		#
	in	$t3, $zero, $zero, $zero, 3		# : update $t3 to new BTND state
	in	$v0, $zero, $zero, $zero, 3		#
	out	$zero, $zero, $zero, $zero, 4	# : set IORegister[4] = 0 zero timer
	in	$s1, $zero, $zero, $zero, 4				# : set $s1 = IORegister[4]
	branch $zero, $zero, $zero, $zero, pause_1	# : jump back to pause_1

BTND_2:
	in	$t3, $zero, $zero, $zero, 3		# : set $t3 = IORegister[3] - BUTND state update $t3 to new BTND state
	in	$t3, $zero, $zero, $zero, 3		# : set $t3 = IORegister[3] - BUTND state update $t3 to new BTND state
	add	$v0, $t3, $zero, $zero, 0		#
	branch $zero, $zero, $zero, $zero, reset_clock	# :

led_change:
	in	$t1, $zero, $zero, $zero, 1			# : set $t1 = IORegister[1]
	add $t1, $zero, $zero, $zero, 1			# : set $t1++ to change LED 0
	and $t1, $t1, $t1, $zero, 1			    # : set $t1 = ($t1) & ($t1) & (0b...00001) mask all leds except for LD 0
	out	$t1, $zero, $zero, $zero, 1			# : change LED register
	branch $zero, $zero, $zero, $zero, pause_1	# : jump back to pause_1

halt:
	sub $zero, $zero, $zero, $zero, 0		#
	halt $zero, $zero, $zero, $zero, 0		# : halt
	sub $zero, $zero, $zero, $zero, 0		#

pause_2:
	in	$at, $zero, $zero, $zero, 2		# : (update) set $t2 = IORegister[2]
	in	$s2, $zero, $zero, $zero, 0		# :
	out	$zero, $zero, $zero, $zero, 1	# : (stall for delay) set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	in	$a0, $zero, $zero, $zero, 2		# : set $a0 = IORegister[2]
	in	$at, $zero, $zero, $zero, 2		# : (update) set $t2 = IORegister[2]
	in	$t2, $zero, $zero, $zero, 2		# : (update) set $t2 = IORegister[2]
	branch $zero, $zero, $zero, $zero, stopper	# : jump back to running stopper shouls update $t2 in stopper
