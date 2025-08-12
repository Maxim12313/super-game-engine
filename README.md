# Game Engine

## Entity Component System
Cache friendly data management architecture promoting code reusibility

## Graphics Rendering
Building ontop of opengl to provide conveient interface for 3d and 2d rendering, camera class, and other utilities

## Extra
Work [Board](https://trello.com/b/ECVEo80Q)

## Installation
Install necessary build tools and dependencies
```
brew install cmake  \
brew install glfw3  \
brew install glm    \
```

## Setup
```
cmake -B build  \
make -C build   \
```

App binaries will be in `/build/bin`
