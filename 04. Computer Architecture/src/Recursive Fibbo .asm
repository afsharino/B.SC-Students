.data
  n: .word 9
  result:   .asciiz "Result: "

.text
  main:
 #read value of n from memory and store in $t0
    la $t0, n
    lw $t0, 0($t0)
    
 #move n($t0) to $a0 and call function
    add $a0, $t0, $zero
    jal recursiveFibbo
    
 #move $v0 to $s2
    add $s2, $v0, $zero
    
 #print the result
    jal print
    
 #store $v0($s2) in memory and exit
    la $t0, n
    sw $s2, 4($t0)
    j Exit
    
 recursiveFibbo:
 #store registers that will change in stack
    addi $sp, $sp, -12
    sw $s0, 8($sp)
    sw $a0, 4($sp)
    sw $ra, 0($sp)
  
 #check whether the number is less than 2 or not(0, 1)
    addi $t1, $zero, 2
    slt $t1, $a0, $t1  
    bne $t1, $zero, return
  
 #recursiveFibbo(n-1)
    addi $a0, $a0, -1
    jal recursiveFibbo
    
 #store return value in $s0 
    add $s0, $v0, $zero
    lw $a0,4($sp)
    
 #recursiveFibbo(n-2)
    addi $a0, $a0, -2
    jal recursiveFibbo
    
 #recursiveFibbo(n-1) + #recursiveFibbo(n-2) 
    add $v0, $v0, $s0
    
 #restore saved values from stack and jump to main programm
    lw $ra , 0 ( $sp )
    lw $s0 , 8 ( $sp )
    addi $sp, $sp, 12
    jr $ra

 #return 0 and 1
 return: 
   add $v0, $a0, $0
  
   lw $ra , 0 ( $sp )
   lw $s0 , 8 ( $sp )
   addi $sp, $sp, 12
   jr $ra
  
 #print output 
 print:
 #print string
   la $a0, result
   addi $v0, $zero, 4
   syscall
  
 #print integer
   add $a0, $zero, $s2
   addi $v0, $zero, 1
   syscall
  
   jr  $ra
  
 #Exit
 Exit: 
   addi $v0, $zero, 10
   syscall