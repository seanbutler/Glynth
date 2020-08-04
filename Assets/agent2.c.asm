
# Assignment Statement 
	PUSH 4
	SAVE %max_moves

# Assignment Statement 
	PUSH 1
	SAVE %spin

# Assignment Statement 
	PUSH 0
	SAVE %direction

# WHILE 
:LBL_0120
	PUSH 1
	BRF @LBL_0121

# WHILE BLOCK
# BEGIN BLOCK

# Assignment Statement 
	LOAD %max_moves
	SAVE %moves

# WHILE 
:LBL_0122
	LOAD %moves
	PUSH 0
	GT
	BRF @LBL_0123

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
	JMP @LBL_0122
:LBL_0123

# Assignment Statement 
	LOAD %direction
	LOAD %spin
	ADD
	SAVE %direction

# END BLOCK
	JMP @LBL_0120
:LBL_0121
