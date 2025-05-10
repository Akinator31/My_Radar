# My Radar 🛩️

![image](https://github.com/user-attachments/assets/192c5953-e352-4d5d-b653-0e17e7951030)

## Overview

My Radar is a 2D air traffic simulation project built in C using CSFML. The program simulates aircraft traffic based on a script file and handles collision detection using a quadtree optimization system.

## Features

- Real-time 2D aircraft simulation with predefined trajectories
- Control towers with coverage zones
- Advanced collision detection using Separate Axis Theorem (SAT)
- Quadtree-based spatial partitioning for optimized collision detection
- Interactive visualization controls
- Custom script-based scenario definition

## Controls

- `L` : Toggle hitboxes and control areas visibility
- `S` : Toggle entity sprites visibility
- `K` : Toggle quadtree visualization
- `Q` : Quit program

## Installation

```bash
make
```

## Usage

```bash
./my_radar [OPTIONS] path_to_script
```

### Options
- `-h` : Display help menu and exit

### Script Format

The script file should contain entities defined as follows:

```
A [x1] [y1] [x2] [y2] [speed] [takeoff_time]    # Defines an aircraft
T [x] [y] [radius]                              # Defines a control tower
```

Where:
- `x1,y1` : Takeoff coordinates
- `x2,y2` : Landing coordinates
- `speed` : Aircraft velocity
- `takeoff_time` : Delay before takeoff
- `radius` : Control tower coverage radius

## Project Structure

```
.
├── assets/         # Graphics resources
├── include/        # Header files
│   ├── engine/
│   ├── entity/
│   ├── errors/
│   └── lib/
├── lib/           # Libraries
│   ├── my_lib/
│   ├── my_list/
│   ├── quadtree/
│   └── vector/
└── src/          # Source code
    ├── collisions/
    ├── engine/
    ├── entity/
    ├── errors/
    ├── event/
    └── utils/
```

## Technical Details

- **Language**: C
- **Graphics**: CSFML
- **Build System**: Make
- **Performance**: Quadtree optimization for collision detection
- **Architecture**: Entity-component system

## Features Highlights

- **Collision Detection**: Implements SAT algorithm for precise collision detection
- **Optimization**: Uses quadtree for efficient spatial partitioning
- **Control Towers**: Provides safe zones where collisions are ignored
- **Dynamic Simulation**: Handles multiple aircraft with different trajectories
