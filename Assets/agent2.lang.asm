
; DECLARE state
	NOP

; DECLARE health
	NOP

; Assignment Statement 
	PUSH 0
	SAVE state

; WHILE 
JumpLabel0:
	LOAD lives
	PUSH 0
	GT
	BRF JumpLabel1

; WHILE BLOCK
; BEGIN BLOCK

; IF EXPRESSION 
	LOAD state
	PUSH 0
	EQU
	BRF JumpLabel2

; IF BLOCK
; BEGIN BLOCK

; Assignment Statement 
	PUSH 100
	SAVE health

; Assignment Statement 
	PUSH 1
	SAVE state

; END BLOCK
JumpLabel2:

; WHILE 
JumpLabel3:
	LOAD hello
	LOAD world
	EQU
	BRF JumpLabel4

; WHILE BLOCK
; BEGIN BLOCK

; Assignment Statement 
	LOAD gee
	SAVE gosh

; END BLOCK
	JMP JumpLabel3
JumpLabel4:

; IF EXPRESSION 
	LOAD state
	PUSH 1
	EQU
	BRF JumpLabel5

; IF BLOCK
; BEGIN BLOCK

; Assignment Statement 
	LOAD coins
	PUSH 1
	ADD
	SAVE coins

; IF EXPRESSION 
	LOAD health
	PUSH 0
	EQU
	BRF JumpLabel6

; IF BLOCK
; BEGIN BLOCK

; Assignment Statement 
	PUSH 2
	SAVE state

; END BLOCK
JumpLabel6:

; END BLOCK
JumpLabel5:

; IF EXPRESSION 
	LOAD state
	PUSH 2
	EQU
	BRF JumpLabel7

; IF BLOCK
; BEGIN BLOCK

; IF EXPRESSION 
	LOAD health
	PUSH 0
	EQU
	BRF JumpLabel8

; IF BLOCK
; BEGIN BLOCK

; Assignment Statement 
	PUSH 2
	SAVE state

; END BLOCK
JumpLabel8:

; END BLOCK
JumpLabel7:

; END BLOCK
	JMP JumpLabel0
JumpLabel1:
