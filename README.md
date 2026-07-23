# FarmGame

A small OpenGL game engine built from scratch in C++, with the long-term goal of powering a farming game.

## About

FarmGame is a personal hobby project I'm using to learn engine and graphics programming. The original goal — and still the goal — was to build a farming game, but most of the work so far has gone into the underlying engine rather than gameplay itself. Game-specific content (crops, tools, farming mechanics, etc.) will be pushed incrementally as the engine stabilizes.

This is a learning project, not a finished product, so expect things to be rough around the edges and to change shape often.

## Status

Early / active development. Core engine systems are in place; gameplay hasn't started yet.

## Engine features so far

- **ECS** — `Entity` / `EntityManager` with components: `Transform`, `Camera`, `Mesh`, `Material`, `Script`
- **Batched, GPU-instanced renderer** — draw calls are grouped by shader/mesh/material and issued via `glDrawElementsInstanced` using per-instance VBOs; batches automatically split once they hit their instance cap
- **Render queues** (`Opaque`, `Skybox`, `Transparent`, `UI`) to control draw order and GL state per pass
- **Material system** — per-material render queue and texture binding on top of the shader system
- **Scene / SceneManager** for loading and switching between scenes
- Shader and texture abstractions, with a texture cache (`TextureStorage`)
- `Window`, `Input`, and `Time` wrappers around GLFW
- Basic asset loading (shader source files, textures via `stb_image`)

## Tech stack

- C++20
- OpenGL 3.3 (core profile)
- [GLFW](https://www.glfw.org/) — windowing & input
- [glad](https://glad.dav1d.de/) — OpenGL function loading
- [GLM](https://github.com/g-truc/glm) — math
- [stb_image](https://github.com/nothings/stb) — texture loading
- Visual Studio, Windows only for now

## Project structure

```
FarmGame/
├── Dependencies/        # Vendored third-party libs (GLFW, glad, glm)
├── FarmGame/
│   ├── assets/          # Shaders and other runtime assets
│   └── src/
│       ├── Core/        # Application, Window, Input, Time
│       ├── ECS/         # Entities, components, entity manager
│       ├── Graphics/    # Renderer, batching, meshes, shaders, textures
│       ├── Scene/       # Scene & SceneManager
│       ├── Assets/      # Asset manager
│       └── main.cpp
└── FarmGame.slnx
```

## Building

Currently targets Windows with Visual Studio. Dependencies are vendored, so no package manager is required.

1. Clone the repo:
   ```
   git clone https://github.com/null68/FarmGame.git
   ```
2. Open `FarmGame.slnx` in Visual Studio.
3. Build & run (x64 or x86).

## Roadmap

- [ ] Implement a proper ECS architecture (separate component storage, etc.)
- [ ] Move gameplay code into a dedicated `Game/` layer, loaded through `SceneManager`
- [ ] Start implementing actual farming mechanics (crops, tools, inventory, etc.)
- [ ] Expand the asset pipeline (models, more texture formats)

## License

No license yet — currently just a personal learning project.