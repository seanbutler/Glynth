
# Assignment Statement 
	PUSH 8
	SAVE %max_moves

# Assignment Statement 
	PUSH 2
	SAVE %spin

# Assignment Statement 
	PUSH 0
	SAVE %direction

# WHILE 
:LBL_0248
	PUSH 1
	BRF @LBL_0249

# WHILE BLOCK
# BEGIN BLOCK

# Assignment Statement 
	LOAD %max_moves
	SAVE %moves

# WHILE 
:LBL_0250
	LOAD %moves
	PUSH 0
	GT
	BRF @LBL_0251

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
	JMP @LBL_0250
:LBL_0251

# Assignment Statement 
	LOAD %direction
	LOAD %spin
	ADD
	SAVE %direction

# END BLOCK
	JMP @LBL_0248
:LBL_0249
