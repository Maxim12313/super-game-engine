# Game Engine

### Entity Component System
Cache friendly data management architecture promoting code reusibility.
Sparse set system focused design following [EnTT's](https://github.com/skypjack/entt) 
architecture

### Graphics Rendering
Building ontop of opengl to provide conveient interface for 3d and 2d rendering, camera class, and other utilities

### Multiplayer Networking
In Progress

### Extra
Work [Board](https://trello.com/b/ECVEo80Q)

## Sources
### ECS
[Archetype ECS](https://austinmorlan.com/posts/entity_component_system/)

[System Focused ECS](https://github.com/skypjack/entt)

[EnTT blog](https://skypjack.github.io/2019-04-12-entt-tips-and-tricks-part-1/)

### OpenGL
[Guide](https://learnopengl.com/)

### Networking
[Beej's guide](https://beej.us/guide/bgnet/pdf/bgnet_usl_c_1.pdf)



## Installation
Install necessary build tools and dependencies
```
brew install cmake  \
brew install glfw3  \
brew install glm    \
brew install llvm   \
```

## Clang-tidy
```
sudo ln -s "$(brew --prefix llvm)/bin/clang-format" "/usr/local/bin/clang-format"
sudo ln -s "$(brew --prefix llvm)/bin/clang-tidy" "/usr/local/bin/clang-tidy"
sudo ln -s "$(brew --prefix llvm)/bin/clang-apply-replacements" "/usr/local/bin/clang-apply-replacements"
```

## Setup
```
cmake -B build  \
make -C build   \
```

App binaries will be in `/build/bin`
