# Brainstorm

## Current direction
Corrode is first a god-sim sandbox built arount generated terrain and changing ecology? The user shapes env. conditions and does not directly control creatures? Observing effects over time.

## Core loop
 1. Generate a terrain map from a seed. (Reproducable)
 2. Establish env. conditions (rainfall, temp, soil)
 3. Simulate water vegitation, *eventually* creatures.
 4. Let the player change conditions or terrain.
 5. Show resulting changes through map, overlays.

 ```
 player choices -> env -> resources -> creature behavior -> changed env
 ```

 ## Terrain data
 Map will be a grid of cells? Cells will init have data:
  - elevation
  - moisture / water amount
  - temp
  - soil comp / fertility
  - vegitation level
  - biome class

  some values are likely consistent throughout a simulation (elevation?); others change (moisture?, fertility, vegiation, water?)

## Climate and weater
Rainfall should be a dynamic process.
Candidate inputs:
 - precip freq
 - precip intensity
 - base temp
 - wind?
 - evaporation rate?

## Terrain generation architecture
Abstract base class as interface. Generators implement this.

```cpp
class TerrainGenerator {
public:
    virtual ~TerrainGenerator() = default;
    virtual const char* name() const = 0;
    virtual void generate(Terrain& terrain, uint32_t seed) = 0;
};
```

Implementations:
 - flat terrain
 - noise based elevation
 - island elevation
 - water / flow pass
 - soil pass
 - biome pass

Deterministic for any given seed.

## Initial alpha reqs?
 - Generate and render map
 - Color the map from elevation and moisture
 - Simulate rainfall, evaporation, vegetation growth
 - Allow user to paint? rainfall / fertility
 - Add pause, speed controls, seed selection, debug overlays

## Creature implement reqs
Start with a herbivor probably. Seeks water and vegetation. consumes food, wanders, reproduces under good conditions, dies when it can't get what it needs.

Only after getting this move on to more complicated things, ie genetics, predators, more species, humans, whatever.

## Theme
Core mechanics are an ecological? god-sim. Post industrial reclamation setting is interesting as a later theme, maybe make an optional like "gamemode" with damaged soil, contamination (radiation, chemicals, etc), abandoned structures, nature reclaiming the land.

## Defered for later
 - More detail with soil mechanics
 - erosion and river formation (at least realistic river formation, could have a simple pass in the generation loop)
 - seasons
 - genetics / evolution
 - combat / predators
 - multiple species
 - post-industrial stuff
