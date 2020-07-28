# Evolution of game entity code over in c-like Language

## Language Style

### Types

**Minimise Types**

**Remove Variable Declarations**

**Within an Entity All Local Variables are Always In Scope**

**Reduce Cartesian Vectors to Cardinal Directions**

**All Parameters are Range Safe and Wrap by means of Modulus**

## External Parameters Set Special Status
 - player ( i am visible to all via player keyword )
 - hurtful ( i am visible to player via hurt keyword, i subtract from the players health on collision)
 - healing ( i am visible to player via hurt keyword, i add to the players health on collision)
 - goal ( singleton, i am visible to player via goal keyword, i end the game on collision with player)
  
 ## Reserved Words & Special Variables

  - x, y
  - distance_to
  - direction_to
  
  - position = 
  - push position
  - pop position
  
  
  