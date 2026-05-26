# Guard Perception Demo

This is my AI programming assignment made in Unreal Engine.  
The project is a small first-person stealth facility where a guard patrols the level, sees the player, chases them, investigates the last known location, and then returns to patrol.

The main focus of the project is using Unreal's AI systems:

- NavMesh
- Behaviour Tree
- Blackboard
- AI Perception
- Custom C++ Behaviour Tree tasks
- Blueprint logic for setup and visual feedback

The project is made as a hybrid project. The main AI flow is set up in the Behaviour Tree, but some of the custom nodes are made in C++ and then used inside the Behaviour Tree.

---

## G Requirements

The project currently has the G requirements implemented:

- The level has a NavMesh covering the walkable areas.
- There is a player-controlled character in the scene.
- The guard patrols the level using a Behaviour Tree.
- The guard uses AI Perception with Sight.
- The guard has different states before and after detecting the player.
- The guard returns to patrol after losing the player.
- Git LFS is set up for Unreal assets.
- The README explains the Behaviour Tree, Blackboard keys, and perception setup.

---

## Level Setup

The level is a small greybox stealth facility.

It contains:

- A player start
- Walls and cover
- A guard
- Patrol points
- NavMesh
- An exit trigger

The level is built so the player can walk into the guard's sight, hide behind cover, and show that the guard can lose sight and return to patrol.

---

## AI States

The guard currently has three main states:

### Patrol

This is the default state.

The guard moves between patrol points placed in the level.  
The patrol points are assigned on the guard actor in the level.

### Chase

This happens when the guard sees the player.

When Sight perception detects the player, the AI Controller sets the Blackboard key `TargetActor`.  
The Behaviour Tree then switches to the chase branch and the guard moves toward the player.

### Investigate

This happens when the guard loses sight of the player.

While chasing, a Behaviour Tree service updates `LastKnownLocation`.  
When the player leaves sight, `TargetActor` is cleared, but `LastKnownLocation` stays set.  
The guard then moves to that location, waits shortly, clears the key, and goes back to patrol.

---

## Behaviour Tree

The guard uses `BT_Guard`.

Current structure:

```text
Root
└── Selector
    ├── Chase Player
    │   ├── Blackboard Decorator: TargetActor Is Set
    │   ├── Service: Update Last Known Location
    │   ├── Set Guard State: Chase
    │   └── Move To: TargetActor
    │
    ├── Investigate Last Known Location
    │   ├── Blackboard Decorator: LastKnownLocation Is Set
    │   ├── Set Guard State: Investigate
    │   ├── Move To: LastKnownLocation
    │   ├── Wait
    │   └── Clear Blackboard Key: LastKnownLocation
    │
    └── Patrol
        ├── Set Guard State: Patrol
        ├── Set Next Patrol Point
        ├── Move To: PatrolLocation
        └── Wait
