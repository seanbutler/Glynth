# High Level Criteria for Quality Game Entities

## Environment

#### Generation Strategies

 - Use Randomised depth first search to carve out a maze
 - Randomly place few long walls
 - Randomly place single blocks

#### Navigation

## Simple Arcade Games

#### All Agent Characteristics

- Cannot pass through walls
- Exists at coords in the world.

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





