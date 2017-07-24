#######################################################################
#Copyright 2017 M. Davis D. Navarro A. Mata

#Permission is hereby granted, free of charge, to any person obtaining a 
#copy of this software and associated documentation files (the "Software"), 
#to deal in the Software without restriction, including without limitation 
#the rights to use, copy, modify, merge, publish, distribute, sublicense, 
#and/or sell copies of the Software, and to permit persons to whom the 
#Software is furnished to do so, subject to the following conditions:

#The above copyright notice and this permission notice shall be included 
#in all copies or substantial portions of the Software.

#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
#OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
#MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
#IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
#CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
#TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
#SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#######################################################################
# Mips calculator simulation
.data
den: .asciiz "\nEnter a integer: "
dop: .asciiz "\nEnter the operator: "
A:   .word 1 #First
B:   .word 1 #Second number

#Operators
#1 = +
#2 = -
#3 = and
#4 = or
#5 = not
#6 = nand
#7 = nor
#8 = xor
#9 = xnor

.text
li $t1, 1
li $t2, 2
li $t3, 3
li $t4, 4
li $t5, 5
li $t6, 6
li $t7, 7
li $t8, 8
li $t9, 9



calc:	li $v0, 4  	#Syscall enter first number print              
        la $a0, den           
        syscall
        
        li $v0, 5           
        syscall
        add $s0, $v0, $0
        
        li $v0, 4       #Syscall enter second number print         
        la $a0, den           
        syscall
        
        li $v0, 5 
        syscall
        add $s1, $v0, $0
        
        li $v0, 4       #Syscall enter operator print         
        la $a0, dop           
        syscall
        
        li $v0, 5 
        syscall
        add $s2, $v0, $0

options:beq $t1, $s2, sum 
	beq $t2, $s2, less 
	beq $t3, $s2, andB 
	beq $t4, $s2, orB 
	beq $t5, $s2, notB 
	beq $t6, $s2, nandB
	beq $t7, $s2, norB
	beq $t8, $s2, xorB 
	beq $t9, $s2, xnorB
	j calc

sum: 	add $v1, $s0, $s1
	j print
	

less: 	sub $v1, $s0, $s1
	j print


#prod: 	mult $v0, $s0, $s1 # in the implemented architecture   


#div: 	div $v0, $s0, $s1 # in the implemented architecture 

andB: 	and $v1, $s0, $s1
	j print

orB: 	or $v1, $s0, $s1
	j print

notB: 	not $v1, $s0
	j print

nandB: 	and $t0, $s0, $s1
	not $v1, $t0
	j print
	
norB:	nor $v1, $s0, $s1
	j print
	
xorB:	xor $v1, $s0, $s1
	j print

xnorB: 	xor $t0, $s0, $s1
	not $v1, $t0
	j print

print:	li $v0, 1               
        add $a0, $v1, $0          
        syscall
	j calc
