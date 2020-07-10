
# DECLARE health
	NOP

# DECLARE lives
	NOP

# Assignment Statement 
	PUSH 5
	SAVE lives

# DECLARE state
	NOP

# Assignment Statement 
	PUSH 0
	SAVE state

# IF EXPRESSION 
	LOAD state
	PUSH 0
	EQU
	BRT past_the_ifblock

# IF BLOCK
# BEGIN BLOCK

# Assignment Statement 
	PUSH 100
	SAVE health

# Assignment Statement 
	PUSH 1
	SAVE state

# END BLOCK
past_the_ifblock:
