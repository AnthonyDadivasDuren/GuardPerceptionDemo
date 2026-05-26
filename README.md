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
The investigation point is slightly predicted in the direction the player was moving, so the guard searches a bit further instead of only walking to the exact last visible position.

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
```

The Selector checks the branches from left to right.

The priority is:

```text
Chase > Investigate > Patrol
```

This means the guard will chase first if the player is visible.  
If the player is not visible anymore but there is a last known location, the guard investigates.  
If neither of those are true, the guard goes back to patrolling.

---

## Blackboard Keys

The guard uses `BB_Guard`.

| Key | Type | Purpose |
|---|---|---|
| `TargetActor` | Object / Actor | Stores the player when the guard can currently see them. This is used by the chase branch. |
| `LastKnownLocation` | Vector | Stores where the player was last seen or where the guard thinks the player was moving. This is used by the investigate branch. |
| `PatrolLocation` | Vector | Stores the current patrol destination. This is used by the patrol branch. |

---

## AI Perception

The guard uses one AI Perception sense for the G version:

```text
Sight
```

The Sight sense is set up on `BP_GuardAIController`.

When the guard sees the player, the AI Controller sets:

```text
TargetActor = Player
```

This makes the Behaviour Tree switch to the chase branch.

When the guard loses sight of the player, the AI Controller clears:

```text
TargetActor
```

The guard then stops chasing. Since `LastKnownLocation` is still set by the Behaviour Tree service, the Behaviour Tree switches to the investigate branch instead.

I chose Sight because it fits the stealth facility idea well. It also makes the AI state changes easy to show in the video.

---

## Last Known Location

At first I only updated `LastKnownLocation` when the player was first detected, but that made the guard sometimes investigate the wrong place.

To fix this, I added a Behaviour Tree service called:

```text
BTService_UpdateLastKnownLocation
```

This service runs while the guard is chasing. It keeps updating `LastKnownLocation` based on the player position and movement direction.

The guard does not only investigate the exact position where the player was last visible. It investigates a bit further in the direction the player was moving. This makes the guard feel less like it instantly gives up when the player hides behind a wall.

The basic idea is:

```text
LastKnownLocation = PlayerLocation + PlayerVelocityDirection * InvestigationOffset
```

If the player is not moving much, it just uses the player's current location instead.

---

## Custom C++ Behaviour Tree Tasks

Some of the Behaviour Tree nodes are custom C++ tasks.

### `BTTask_SetNextPatrolPoint`

This task gets the next patrol point from the guard's patrol point array and writes the location to the Blackboard key:

```text
PatrolLocation
```

The normal Unreal `Move To` node then moves the guard to that location.

### `BTTask_ClearBlackBoardKey`

This task clears a selected Blackboard key.

In this project it is used to clear:

```text
LastKnownLocation
```

after the guard has finished investigating. This allows the AI to leave the investigate branch and return to patrol.

### `BTTask_SetGuardState`

This task changes the guard's current state.

The states are:

```text
Patrol
Chase
Investigate
```

It also changes the guard's movement speed and triggers the visual color feedback.

---

## Visual Feedback

There is also an optional debug mode where the guard changes color depending on its current state. altough without animations.

| State | Meaning | Color |
|---|---|---|
| Patrol | The guard is following patrol points | Blue |
| Chase | The guard has seen the player and is chasing | Red |
| Investigate | The guard lost sight and is checking the last known location | Yellow |

This is mostly used for debugging and to make the behaviour easier to see.
---

## Guard Animations

The guard uses retargeted animations for the main AI states.

- Patrol uses a walk animation.
- Chase uses a sprint animation.
- Investigate uses walking while moving to the last known location.
- When the guard reaches the investigation point and stops, it plays a look-around animation.

---

## Movement Speeds

The guard also changes movement speed depending on state.

- Patrol is slower.
- Chase is faster.
- Investigate is in between.

This makes the AI behaviour easier to read and makes the guard feel less static.

---

## Caught / Restart Logic

The guard has a catch trigger.

If the guard reaches the player while chasing, the player is caught and the level restarts. This gives the demo a simple fail condition and makes it feel more like a small stealth game.

---

## Git LFS

Git LFS is enabled for Unreal Engine assets such as:

```text
.uasset
.fbx
.mp4
```

## Video Demonstration

The submitted video should show:

- The NavMesh in the level
- The player-controlled character
- The guard patrolling between patrol points
- The guard detecting the player with Sight
- The guard switching to chase
- The player breaking line of sight
- The guard investigating the predicted last known location
- The guard returning to patrol
