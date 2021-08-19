# Raylib Template Project

```sh
# Getting the Project ready
git clone https://github.com/MrDiver/RaylibTemplateProject
cd RaylibTemplateProject
mkdir build
cmake ..
make
```
## Running the Project
```sh
# Running the project
./dist/rlProgram
```

## Resource folder
The resource folder `dist/res` can automatically be accessed with a relative path like `"res/shaders/base.vs"` from the Program.
```cpp
// Basic Example
Shader s = LoadShader("res/shaders/base.vs","res/shaders/lighting.fs");
```

## Options

You can supply an option to the cmake script if you don't want Raygui to be downloaded and added.

```sh
cmake .. -DUSE_RAYGUI=OFF
```