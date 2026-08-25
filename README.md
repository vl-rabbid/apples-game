## Apples Game
An educational game written in C++ using SFML

### Build
This project uses CMake and automatically downloads SFML during configuration. 
To build, open the project in your IDE or run:
```bash
cmake --preset debug
cmake --build --preset debug
```

### Linux Dependencies
Linux users need to install the required SFML development dependencies for their distribution before building the project.
See the official SFML documentation for the dependency list and installation instructions:
[SFML 2.6 Linux dependencies](https://www.sfml-dev.org/tutorials/2.6/start-linux.php)

For Fedora:
```bash
sudo dnf install libX11-devel libXcursor-devel libXrandr-devel libXi-devel libXinerama-devel mesa-libGL-devel libudev-devel openal-soft-devel libvorbis-devel flac-devel
```
