
# DECLARE posx

# Assignment Statement 
	PUSH 10
	SAVE %posx

# DECLARE posy

# Assignment Statement 
	PUSH 20
	SAVE %posy

# WHILE 
:LAB_0000
	LOAD %posy
	PUSH 30
	LT
	BRF @LAB_0001

# WHILE BLOCK
# BEGIN BLOCK

# Assignment Statement 
	LOAD %posy
	PUSH 1
	ADD
	SAVE %posy

# END BLOCK
	JMP @LAB_0000
:LAB_0001
