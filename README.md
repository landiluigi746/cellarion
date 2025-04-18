# cellarion

![Language](https://skillicons.dev/icons?i=cpp)

![License](https://img.shields.io/badge/License-MIT-brightgreen.svg)

cellarion is a cellular automata showcase written in C++ with raylib and OpenMP. It provides a simple
interface for users to create and run cellular automata on a 2D grid of cells.

## Index

- [Implemented automata](#implemented-automata)
- [Usage](#usage)
  - [Compiling](#compiling)
  - [Running](#running)
- [Screenshots](#screenshots)

## Implemented automata

Currently, cellarion supports the following automata:

- Conway's Game of Life
- Brian's Brain
- Rule 110 (adapted to 2D)

More automata will be added soon.

## Usage

### Compiling

To compile cellarion, you need to have a C++17 compiler and CMake installed. Then, run the following commands:

```bash
git clone https://github.com/landiluigi746/cellarion.git
cd cellarion
mkdir build
cmake -S . -B build # -DCMAKE_BUILD_TYPE=Release for release build, by default it's Debug
cmake --build build
```

### Running

After compiling, you can run cellarion by running the following command:

```bash
./bin/BUILD_TYPE/cellarion # replace BUILD_TYPE with the build type you used
```

### Screenshots

<div style="display: flex; justify-content: space-between; margin: 20px 0;">
  <div style="flex: 1;">
    <img src="res/screenshots/GameOfLife.png" alt="Game Of Life" style="width: 100%; height: auto; border-radius: 8px;">
    <p style="text-align: center; margin-top: 8px;">Game Of Life</p>
  </div>
  <div style="flex: 1;">
    <img src="res/screenshots/BrianBrain.png" alt="Brian's Brain" style="width: 100%; height: auto; border-radius: 8px;">
    <p style="text-align: center; margin-top: 8px;">Brian's Brain</p>
  </div>
  <div style="flex: 1;">
    <img src="res/screenshots/Rule110.png" alt="Rule 110" style="width: 100%; height: auto; border-radius: 8px;">
    <p style="text-align: center; margin-top: 8px;">Rule 110</p>
  </div>
</div>