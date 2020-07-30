
# Assignment Statement 
	PUSH 2
	PUSH 1
	ADD
	SAVE %direction

# WHILE 
:LBL_0000
	PUSH 1
	BRF @LBL_0001

# WHILE BLOCK
# BEGIN BLOCK

# Assignment Statement 
	PUSH 8
	SAVE %moves

# WHILE 
:LBL_0002
	LOAD %moves
	PUSH 0
	GT
	BRF @LBL_0003

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
	JMP @LBL_0002
:LBL_0003

# Assignment Statement 
	LOAD %direction
	PUSH 1
	ADD
	SAVE %direction

# END BLOCK
	JMP @LBL_0000
:LBL_0001
