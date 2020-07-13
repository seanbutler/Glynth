
; DECLARE state
	NOP

; Assignment Statement 
	PUSH 0
	SAVE state

; DECLARE health
	NOP

; Assignment Statement 
	PUSH 0
	SAVE health

; WHILE 
JumpLabel0:
	LOAD health
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
	PUSH 1
	SAVE state

; END BLOCK
JumpLabel2:

; END BLOCK
	JMP JumpLabel0
JumpLabel1:
