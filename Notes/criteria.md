
## Best Classic Era (late70s-early80s) Arcade Games Ranked

Taken from [this](https://www.ranker.com/crowdranked-list/the-best-classic-arcade-games)
 site is a lost of the most popular arcade games from the classic era.
 - Galaga
 - Donkey Kong
 - Pac Man
 - Space Invaders (1 and 4 are synonymous)
 - Ms. Pac Man (3 and 5 are synonymous)
 - Dig Dug
 - Gauntlet
 - Asteroids
 - Mario Bros (not an arcade game, also covered elsewhere)
 - 1942
 - Defender
 - Street Fighter II
 - Centipede
 - Street Fighter 
 - Double Dragon (see 12 & 14)
 - Joust
 - Mortal Combat (see 12, 14 & 15)
 - etc
 - etc
 - PONG
 - SPY HUNTER
  
Ignore the strolling beat em up fighting games like Street Fighter and etc. Also 
ignore Mario Bros as really a console game. Both are well covered in other literature as well.

## Universal Patterns

These games __all__ have the following patterns in common.
 - Player Can Move
 - Flat 2D Space (asteroids?!)
 - __Either__ Player Reaches Goal To Win __OR__ Player Defeats (all) Enemies to Win
 - Enemies Hurt Player on Collision
 - More Enemies Than Players
 
## Common Patterns
 - Some Environment Blocks are visible and impassible, if so then only small fraction of space
 - Player has 3 Health
 - Enemies have 1 Health
 - Players Shoot Hurtful Projectiles
 - Enemies Shoot Hurtful Projectiles
 - Waves of Enemies
 - Stationary Player Respawn (Start) Point
 
## Uncommon Patterns
 - Some Environment Can be destroyed
   - if so then much more common
 - Player collects Items for Powers
   - Suppressed abilities, collectables unlock them
 - Enemies Grow or Space Shrinks either directly or indirectly (more on this later)    
 - Enemies Reach Goal To Win (Player Lose)

# Criteria for Quality Arcade Games

## Requirements / Must
 These can be coded into the wider system as they are necessary.
 - Complete (win or lose) a Level in over 30 seconds
     - lets say @16fps 16*60*0.5 = about 500 moves
 - Must Complete (win or lose) a Level in under 5 minutes
     - lets say @16fps 16*60*5 = about 5000 moves
 - Cannot win just by staying still and waiting
    - Or moving to safe place and waiting

## Goals / Should
 These can be set as evolutionary goals via fitness functions
 - Should Complete (win or lose) a Level in under 3 minutes
     - lets say @16fps 16 x 60 x 3 = about 3000 moves
     - lets say @16fps 16 x 60 x 5 = about 5000 moves
 - Player completes a Level a fraction (say, 1/2 ) of the time
    - Could be, given 3 hearts, lose 1 heart per level on average
 - Should Move over range of Locations
    - Simple Statistical Measure
 - Likely cover the same ground more than once
    - Simple Statistical Measure
 - Should interact (get close too) enemies to succeed

 - Enemy May sometimes Defeat Player by collision
 - Enemy Move towards and Away from the Player
 - Enemy Have Repetitive Behaviours which can be observed
 - Enemy Should interact (get close too) player at some point to succeed
 
 - Enemy Rewards the Player on its Death

## More Advanced Patterns

### Environment Generation Strategies

 - Use Randomised depth first search to carve out a maze
 - Randomly place few long walls
 - Randomly place single blocks

#### Player Characteristics

**Required Characteristics**

- Can perceive (nearly) the whole visible level, radius will do. Doesnt need to interrogate (say via ray casts). This is not a simulation the player sees the arena like a seagull or a drone. So can tell direction and distance to specific interesting elements like the goal once Goal has been onscreen Goal.
- Is movable

**Optional Characteristics**

- Reaches a Goal coords to win
- Has scalar health. WHen health reaches zero loses
- Has scalar points. Reaches a Score to win
- When low health finds and collects health
- Avoids Damage

#### Enemy

**Given/Unavoidable Characteristics**

- Has start/anchor point
    Set Anchor()

- Has limits/range/flaws to its perception
        
- Has limits/range to its movement
    If Distance From Anchor > Range

**Derived**

- Interacts with the Player at least once on a playthrough
- Hurts or Hinders the Player
- Rewards the Player on its Death
- Has predictable Repetitive Behaviour
- Vulnerable to Damage

#### Goal

Once entity has been in range of me they always know where I am.

#### Door-Key Challenge

**Door**

- Blocking and Changes to Passable
- Requires External Message
    - collection of pickups
    - killing of enemies
    - visit location
    - etc

**Key**

#### Arena


