@ Used the CPUlator to run and debug your code: https://cpulator.01xz.net/?sys=arm-de1soc&d_audio=48000
@ Note, that the CPUlator simulates a DE1-SoC device, and here you should use the HEX displays to show the numbers
@ See the Tutorials on LED, Button, and HEX displays in the F28HS course (Weeks 8 and 9)

@ This ARM Assembler code should implement a matching function, for use in MasterMind program, as
@ described in the CW3 specification. It should produce as output 2 numbers, the first for the
@ exact matches (peg of right colour and in right position) and approximate matches (peg of right
@ color but not in right position). Make sure to count each peg just once!
	
@ Example (first sequence is secret, second sequence is guess):
@ 1 2 1
@ 3 1 3 ==> 0 1
@ Display the result as two digits on the two rightmost HEX displays, from left to right
@

@ -----------------------------------------------------------------------------

.text
.global         main
main: 
	LDR  R2, =secret	@ pointer to secret sequence
	LDR  R3, =guess		@ pointer to guess sequence

	@ you probably need to initialise more values here

	@ ... COMPLETE THE CODING BY ADDING YOUR CODE HERE, you may want to use sub-routines to structure your code

exit:	@MOV	 R0, R4		@ load result to output register
	MOV 	 R7, #1		@ load system call code
	SWI 	 0		@ return this value
	
@ =============================================================================

.data

@ constants about the basic setup of the game: length of sequence and number of colors	
.equ LEN, 3
.equ COL, 3
.equ NAN1, 8
.equ NAN2, 9

@ constants needed to interface with external devices	
.equ BUTTONBASE, 0xFF200050
.equ HEXBASE,	 0xFF200020
.equ BUTTON_NO,  1	

@ you probably want to define a table here, encoding the display of digits on the HEX display	
.align 1	
digits:
	.byte  0b0111111	@ 0
@	... COMPLETE THIS TABLE  ...	          	

@ INPUT DATA for the matching function
.align 4
secret: .word 1 
	.word 2 
	.word 1 

.align 4
guess:	.word 3 
	.word 1 
	.word 3 

@ Not strictly necessary, but can be used to test the result	
@ Expect Answer: 0 1
.align 4
expect: .byte 0
	.byte 1

.align 4
secret1: .word 1 
	.word 2 
	.word 3 

.align 4
guess1:	.word 1 
	.word 1 
	.word 2 

@ Not strictly necessary, but can be used to test the result	
@ Expect Answer: 1 1
.align 4
expect1: .byte 1
	.byte 1

.align 4
secret2: .word 2 
	.word 3
	.word 2 

.align 4
guess2:	.word 3 
	.word 3 
	.word 1 

@ Not strictly necessary, but can be used to test the result	
@ Expect Answer: 1 0
.align 4
expect2: .byte 1
	.byte 0

