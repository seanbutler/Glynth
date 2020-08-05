
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
:LBL_0180
	PUSH 1
	BRF @LBL_0181

# WHILE BLOCK
# BEGIN BLOCK

# Assignment Statement 
	LOAD %max_moves
	SAVE %moves

# WHILE 
:LBL_0182
	LOAD %moves
	PUSH 0
	GT
	BRF @LBL_0183

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
	JMP @LBL_0182
:LBL_0183

# Assignment Statement 
	LOAD %direction
	LOAD %spin
	ADD
	SAVE %direction

# END BLOCK
	JMP @LBL_0180
:LBL_0181
