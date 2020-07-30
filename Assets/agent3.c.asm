
# Assignment Statement 
	PUSH 0
	SAVE %direction

# WHILE 
:LBL_0008
	PUSH 1
	BRF @LBL_0009

# WHILE BLOCK
# BEGIN BLOCK

# Assignment Statement 
	PUSH 5
	SAVE %moves

# WHILE 
:LBL_0010
	LOAD %moves
	PUSH 0
	GT
	BRF @LBL_0011

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
	JMP @LBL_0010
:LBL_0011

# Assignment Statement 
	LOAD %direction
	PUSH 1
	ADD
	SAVE %direction

# END BLOCK
	JMP @LBL_0008
:LBL_0009
