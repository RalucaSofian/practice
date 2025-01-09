# Project Name: practice
## Project Description

The aim of the project is to create a basic game engine, and program a simple platformer game using it.


## Technologies Used

- C language
- GLFW
    - Window management
    - Capture of input events
    - Simple OpenGL rendering


## Project Folder Structure

Source files of the project are saved under the following folder structure:

```bash
.
├── bin/
├── inc/
│   ├── platform/
│   ├── systems/
│   ├── utils/
│   └── ...
├── src/
│   ├── platform/
│   ├── systems/
│   ├── utils/
│   ├── game_controller.c
│   ├── main.c
│   └── renderer.c
├── level_one.txt
├── makefile
└── README.md
```


## Running the Project

The commands for building and running the project are simple make commands:

```bash
# build the project binary
$: make all
# run the project
$: make run
```

After this, the game window will open, and the custom logger will print in the console as each module initializes:

```bash
[08-01-2025 16:06:42.496] [INFO] main.c                           ‣ EVT Sys Init
[08-01-2025 16:06:42.496] [INFO] main.c                           ‣ EVT Sys Init -- Done
[08-01-2025 16:06:42.496] [INFO] main.c                           ‣ Input Sys Init
...
```


## Game Controls

- **WASD**: control the movement of the Player
- **R**: reset the position of the Player to the starting one
- **ESC** or **Ctrl+Q**: close/quit the game window


## Functionalities

- Event System:
    - Subscribe-Dispatch Model
- Physics System:
    - Operating with 2D Vectors
    - Handling of multiple types of Forces: Gravity, Air Friction, Ground Friction
    - Handling of Collisions
- Player System:
    - Up to two Player Entities
    - Customizable Control Schemes: Arrow Keys or WASD
- Level System:
    - Customizable using a simple Text File
    - Different Types of Level Entities: Player, Floor, Platform
    - Customizable Positions on screen, Dimensions, and Colours for all Entity Types
- Logging System:
    - Four Logging Levels: Verbose, Info, Warning, Error

