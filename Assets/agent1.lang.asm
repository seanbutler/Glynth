
# Assignment Statement 
	PUSH 128
	SAVE %max

# Assignment Statement 
	PUSH 0
	SAVE %min

# Assignment Statement 
	PUSH 1
	SAVE %pos

# WHILE 
:LBL_0000
	LOAD %pos
	LOAD %max
	LT
	BRF @LBL_0001

# WHILE BLOCK
# BEGIN BLOCK

# OUTPUT EXPRESSION
	LOAD %pos
	OUTPUT 

# Assignment Statement 
	LOAD %pos
	PUSH 2
	MUL
	SAVE %pos

# END BLOCK
	JMP @LBL_0000
:LBL_0001

# WHILE 
:LBL_0002
	LOAD %pos
	LOAD %min
	GT
	BRF @LBL_0003

# WHILE BLOCK
# BEGIN BLOCK

# OUTPUT EXPRESSION
	LOAD %pos
	OUTPUT 

# Assignment Statement 
	LOAD %pos
	PUSH 1
	SUB
	SAVE %pos

# END BLOCK
	JMP @LBL_0002
:LBL_0003
