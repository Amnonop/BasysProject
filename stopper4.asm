	out		$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0
	out		$zero, $zero, $zero, $zero, 4	# : set IORegister[4] = 0

	add		$s0, $zero, $zero, $zero, 32		# :###UPDATE AFTER PAUSE!
	in		$s2, $zero, $zero, $zero, 0		# : set $s2 = IORegister[0]
	in		$t1, $zero, $zero, $zero, 2		# : set $t1 = IORegister[1]
	in		$t2, $zero, $zero, $zero, 3		# : set $t2 = IORegister[2] - BUTNC state
	in		$t3, $zero, $zero, $zero, 4		# : set $t3 = IORegister[3] - BUTND state
	jal 	$zero, $zero, $zero, $zero, stopper	# : 
	halt	$zero, $zero, $zero, $zero, 0		# : halt


stopper:
	in	$a0, $zero, $zero, $zero, 2					# : set $a0 = IORegister[2]
	branch	$zero, $t2, $a0, 1, pause_1				# : break loop when $a0 != $t0 means IORegister[2] has changed means BTNC was pushed
	in	$a0, $zero, $zero, $zero, 3					# : set $a0 = IORegister[3]
	branch	$zero, $t3, $a0, 1, BTND_2				# : break loop when $a0 != $t0 means IORegister[3] has changed
	in	$t1, $zero, $zero, $zero, 0					#	 
	sub $t1, $t1, $s2, $zero, 0						# : time diff
	branch	$zero, $t1, $s0, 4, update_timer 		#
	branch $zero, $zero, $zero, $zero, stopper		#
	


update_timer:
	
	in	$s2, $zero, $zero, $zero, 0				# :(update) set $s0 = IORegister[0]
	add $t2, $zero, $zero, $zero, 0		#
	add $t3, $zero, $zero, $zero, 0		#
	in  $a1, $zero, $zero, $zero, 4				# : set $a1 = IORegister[4]
	add $t2, $zero, $zero, $zero, 0x9		#
	add $t3, $zero, $zero, $zero, 0x50		#
	and $t1, $a1, $t2, $zero, 0x9			#
	branch	$zero, $t1, $t2, 1, up_sec			#
	and $t1, $a1, $t3, $zero, 0x50			#
	branch	$zero, $t1, $t3, 1, up_ten_sec		#
	
	sra $at, $a1, $zero, $zero, 8			#
	and $t1, $at, $t2, $zero, 0x9				#
	branch	$zero, $t1, $t2, 1, up_mins			#
	and $t1, $at, $t3, $zero, 0x50			#
	branch	$zero, $t1, $t3, 1, up_ten_mins		#

up_sec:
	add $t2, $zero, $zero, $zero, 0x0		#
	add $t3, $zero, $zero, $zero, 0x0		#
	and $t2, $t2, $t2, $zero, 0x0			# compare elasped time to other channels
	add $a1, $zero, $zero, $zero, 0x1		#
	out $a1, $zero, $zero, $zero, 4				# update SSD
	branch	$zero, $zero, $zero, $zero, stopper	#

up_ten_sec:
	add $t2, $zero, $zero, $zero, 0x0		#
	add $t3, $zero, $zero, $zero, 0x0		#
	and $a1, $a1, $a1, $zero, 0xFFF0			#
	add $a1, $zero, $zero, $zero, 0x10		#
	out $a1, $zero, $zero, $zero, 4				#
	branch	$zero, $zero, $zero, $zero, stopper #

up_mins:
	add $t2, $zero, $zero, $zero, 0x0		#
	add $t3, $zero, $zero, $zero, 0x0		#
	and $a1, $a1, $a1, $zero, 0xFF00			#
	add $a1, $zero, $zero, $zero, 0x100		#
	out $a1, $zero, $zero, $zero, 4				#
	branch	$zero, $zero, $zero, $zero, stopper #

up_ten_mins:
	add $t2, $zero, $zero, $zero, 0x0		#
	add $t3, $zero, $zero, $zero, 0x0		#
	and $a1, $a1, $a1, $zero, 0xF000			#
	add $a1, $zero, $zero, $zero, 0x1000		#
	out $a1, $zero, $zero, $zero, 4				#
	branch	$zero, $zero, $zero, $zero, stopper #
	##add: if 59:59 -> 00
pause_1:
	in	$t2, $zero, $zero, $zero, 2		# : (update) set $t2 = IORegister[2] 
	out	$t1, $zero, $zero, $zero, 1	# : set IORegister[1] = 1 means LD0 is on
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec) #stalling for time delay between in $t2 and in	$a0
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	add $s1, $zero, $zero, $zero, 160	# : set $s1 = 160 = 32*5  (5 sec)
	in	$at, $zero, $zero, $zero, 1		# : set $at = IORegister[0]
	sub	$s0, $at, $t0, $zero, 0			# : $s0 = $at - $t0 (time difference) 
	in	$a1, $zero, $zero, $zero, 3		# : set $a1 = IORegister[3] -> BTND
	branch	$zero, $t3, $a1, 1, BTND	# : if BTND changed
	branch	$zero, $s0, $s1, 2, led_change		# : if $s0 > 160 
	in	$a0, $zero, $zero, $zero, 2		# : set $a0 = IORegister[2] -> BTNC
	branch	$zero, $t2, $a0, 1, pause_2		# : break loop when $a0 != $t2 means IORegister[2] has changed means BTNC was pushed for the second time
	branch $zero, $zero, $zero, $zero, pause_1	# :jump back to pause_1

pause_2:
	in	$t2, $zero, $zero, $zero, 2		# : (update) set $t2 = IORegister[2]
	out	$zero, $zero, $zero, $zero, 1	# : (stall for delay) set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	out	$zero, $zero, $zero, $zero, 1	# : set IORegister[1] = 0 means turn of LEDs
	in	$a0, $zero, $zero, $zero, 2		# : set $a0 = IORegister[2]
	branch	$zero, $t2, $a0, 1, pause_2		# : break loop when $a0 != $t2 means IORegister[2] has changed means BTNC was pushed for the second time
	branch $zero, $zero, $zero, $zero, stopper	# : jump back to running stopper shouls update $t2 in stopper

BTND:
	add $t3, $a1, $zero, $zero, $zero, 0 # : update $t3 to new BTND state
	out	$zero, $zero, $zero, $zero, 4	# : set IORegister[4] = 0 zero timer
	branch $zero, $zero, $zero, $zero, pause_1	# : jump back to pause_1

BTND_2:
	add $t3, $a1, $zero, $zero, $zero, 0 # : update $t3 to new BTND state
	out	$zero, $zero, $zero, $zero, 4	# : set IORegister[4] = 0 zero timer
	branch $zero, $zero, $zero, $zero, stopper	# : jump back to stopper

led_change:
	in	$t1, $zero, $zero, $zero, 1			# : set $t1 = IORegister[1]
	add $t1, $zero, $zero, $zero, 1			# : set $t1++ to change LED 0
	and $t1, $t1, $t1, $zero, 1			    # : set $t1 = ($t1) & ($t1) & (0b...00001) mask all leds except for LD 0
	out	$t1, $zero, $zero, $zero, 1			# : change LED register
	branch $zero, $zero, $zero, $zero, pause_1	# : jump back to pause_1