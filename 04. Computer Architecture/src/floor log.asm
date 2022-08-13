.data
	message: .asciiz "Enter x to calculate floor (log2(x)): "
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
	beq $v0, $zero, printWarning	#if $v0 == 0 then goto printWarning

	#calculate log
	addi $t0, $t0, 0	#$t0 = 0 (counter = 0)
	add $t3, $zero, $v0	#$t3 = 0 + $v0 (copy the value of $v0 to $t3)
	
	loop2:
		beq $t3, $zero, exitLoop2 #if $t3 == 0 then goto exitLoop
	
		srl $t3, $t3, 1		#$t3 = #t3 >> 1 ($t3 / 2^1)
		addi $t0, $t0, 1	#$t0 = $t0 + 1 (counter++)
	
		j loop2
	exitLoop2:	

	#print output 
	#print string
	la $a0, result
	addi $v0, $zero, 4
	syscall
	
	#print integer
	addi $t0, $t0, -1
	add $a0, $zero, $t0
	addi $v0, $zero, 1
	syscall
	
	Exit:
	#Exit 
	addi $v0, $zero, 10
	syscall
