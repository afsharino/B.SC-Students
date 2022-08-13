.data
	message: .asciiz "Enter x to calculate log2(x): "
	result:	 .asciiz "Result: "
	warning: .asciiz "Please enter natural number!!!!!"
	newLine: .asciiz "\n"
.text
	loop1:
		#print string
		la $a0, message
		addi $v0, $zero, 4
		syscall

		readInteger:
		#read integer
		addi $v0, $zero, 5
		syscall
	
		#check wether the number is natural number or not.
		slt $t5, $v0, $zero		#if $v0 < 0 then $t5 = 1 else $t5 = 0
		beq $t5, $zero, exitLoop1	#if $t5 == 0 then goto exitLoop1
		
		printWarning:
		#print string
		la $a0, warning
		addi $v0, $zero, 4
		syscall

		#print string
		la $a0, newLine
		addi $v0, $zero, 4
		syscall
		
		j loop1
	exitLoop1:
	beq $v0, $zero, printWarning

	#calculate log
	addi $t0, $t0, 0	#$t0 = 0 (counter = 0)
	add $t3, $zero, $v0	#$t3 = 0 + $v0 (copy the value of $v0 to $t3)
	
	loop:
		beq $t3, $zero, exitLoop #if $t3 == 0 then goto exitLoop
	
		srl $t3, $t3, 1		#$t3 = #t3 >> 1 ($t3 / 2^1)
		addi $t0, $t0, 1	#$t0 = $t0 + 1 (counter++)
	
		j loop
	exitLoop:	
	
	#check whether the number is EVEN or ODD
	addi $t1, $zero, 2	#$t1 = 0 + 2($t1 = 2)
	div $v0, $t1		# $v0/$t1
	mfhi $t2		#$t2 = remainder
	
	beq $t2, $zero, even	#if $t2 == 0 then goto even
	addi $t4,$zero, 1	#$t4 = 0 + 1 ($t4 = 1)
	beq $v0,$t4, even	#if $v0 == $t4($v0 == 1) then goto even
	
	#print output for odd numbers
	#print string
	la $a0, result
	addi $v0, $zero, 4
	syscall
	
	#print integer
	add $a0, $zero, $t0
	addi $v0, $zero, 1
	syscall
	j Exit
	
	even:
	#print output for even numbers and the number "1"
	#print string
	la $a0, result
	addi $v0, $zero, 4
	syscall
	
	#print integer
	addi $t0, $t0, -1
	add $a0, $zero, $t0
	addi $v0, $zero, 1
	syscall
	
	readyTOExit:
	
	Exit:
	#Exit 
	addi $v0, $zero, 10
	syscall
