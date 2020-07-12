
; DECLARE health
	NOP

; DECLARE lives
	NOP

; Assignment Statement 
	PUSH 5
	SAVE lives

; DECLARE state
	NOP

; Assignment Statement 
	PUSH 0
	SAVE state

; IF EXPRESSION 
	LOAD health
	PUSH 0
	GT
	BRF JumpLabel0

; IF BLOCK
; BEGIN BLOCK

; WHILE 
JumpLabel1:
	BRF JumpLabel2
	JMP JumpLabel1
JumpLabel2:

; WHILE 
JumpLabel3:
	BRF JumpLabel4
	JMP JumpLabel3
JumpLabel4:

; END BLOCK
JumpLabel0:
