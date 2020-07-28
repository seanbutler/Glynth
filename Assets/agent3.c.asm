
# Assignment Statement 
	PUSH 0
	SAVE %direction

# WHILE 
:LBL_0016
	PUSH 1
	BRF @LBL_0017

# WHILE BLOCK
# BEGIN BLOCK

# Assignment Statement 
	PUSH 5
	SAVE %moves

# WHILE 
:LBL_0018
	LOAD %moves
	PUSH 0
	GT
	BRF @LBL_0019

# WHILE BLOCK
# BEGIN BLOCK

# Assignment Statement 
	LOAD %moves
	PUSH 1
	SUB
	SAVE %moves

# MOVE FUNC (builtin)
	LOAD %direction
	MOVE 

# END BLOCK
	JMP @LBL_0018
:LBL_0019

# Assignment Statement 
	LOAD %direction
	PUSH 1
	ADD
	SAVE %direction

# END BLOCK
	JMP @LBL_0016
:LBL_0017
