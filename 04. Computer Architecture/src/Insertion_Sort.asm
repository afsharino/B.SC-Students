.data
	n:	.word 7
	array:	.word 12, 11, -1, -5, 6, 85, -110
	result:	 .asciiz "Result after sorting: "
	separator: .asciiz ", "
.text
	la $t0, n
	lw $s0, 0($t0)	#$s0 = memory[0 + $t0]
	
	la $t1, array
	
	addi $t2, $zero, 1  #$t2 = 0 + 1 (counter = 1)
	
	outerLoop:
		beq $t2, $s0, outerExit #if $t2 == $s0 then goto outerExit
		
		sll $t7, $t2, 2		#$t7 = #t2 << 2 ($t2 * 2^2 = 4*i)
		add $t7, $t7,$t1	#$t7 = $t7 + $t1 (4*i + $t1)
		lw $t3, 0($t7)		#$t3 = array[i]
		addi $t4, $zero, 0	#t4 = 0
		add $t4, $t4, $t3	#$t4 = array[i]

		addi $t5, $t2, -1	#$t5 = $t2 - 1 (counter2 = i - 1)
		
		innerLoop:
			slti $t6, $t5, 0		#if $t5 < 0 then $t6 = 1 else $t6 = 0
			bne $t6, $zero, innerExit	#if $t6 != 0 then goto innerExit
			
			sll $t7, $t5, 2			#$t7 = $t5 << 2 ($t5 * 2^2 = 4*j)
			add $t7, $t7,$t1		#$t7 = $t7 + $t1 (4*j + $t1)
			lw $t3, 0($t7)			#$t3 = array[j]
			
			slt $t6, $t3, $t4 		#if array[j] < $t4
			bne $t6, $zero, innerExit	#if $t6 != 0 then goto innerExit
			
			beq $t3, $t4, innerExit		#if array[j] == $t4
			
			sw $t3, 4($t7)			#array[j+1] = $t3
			
			addi $t5, $t5, -1		#$t5 = $t5 - 1 
			
			j innerLoop
		innerExit:
		sll $t7, $t5, 2				#$t0 = $t0 + 1 (counter++)
		slt $t0, $t7, $zero			#if $t7 < 0 then $t0 = 1 else $t0 = 0
		bne $t0, $zero, makejPositive		#if $t0 != 0 then goto makejPositive
		add $t7, $t7,$t1			#$t7 = $t7 + $t1
		sw $t4, 4($t7)				#array[j+1] = $t4
		j continue
		makejPositive:				 
		addi $t7, $t7, 4			#$t7 = $t7 + 4
		add $t7, $t7,$t1			#$t7 = $t7 + $t1
		sw $t4, 0($t7)				#array[j+1] = $t4
		continue:
		
		addi $t2, $t2,1		#$t2 = $t2 + 1 (counter1++)
		j outerLoop
	outerExit:

	addi $t2, $zero, 0  #$t2 = 0  (counter = 0)
	#print string
	la $a0, result
	addi $v0, $zero, 4
	syscall
	printLoop:
		beq $t2, $s0, printExit #if $t2 == $s0 then goto printExit
		
		sll $t7, $t2, 2		#$t7 = #t2 << 2 ($t2 * 2^2 = 4*i)
		add $t7, $t7,$t1	#$t7 = $t7 + $t1 (4*i + $t1)
		lw $t3, 0($t7)		#$t3 = array[i]
		
		#print integer
		add $a0, $zero, $t3
		addi $v0, $zero, 1
		syscall
		
		#print string
		la $a0, separator
		addi $v0, $zero, 4
		syscall
			
		addi $t2, $t2,1		#$t2 = $t2 + 1 (counter1++)
		j printLoop
	printExit:
	
	#Exit 
	addi $v0, $zero, 10
	syscall
	

