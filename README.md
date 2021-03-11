# C++ FightingGame by Roundbeargames

Indie game developer from South Korea
<br>
https://youtube.com/roundbeargames

<br>

# Getting Started (Windows)

1. Download ZIP or clone repository

2. Open FightingGameProject.sln (using Visual Studio 2019 Community)

    https://visualstudio.microsoft.com/downloads

<br>

# Getting Started (Linux - Ubuntu or Unbuntu based)

1. Download ZIP or clone repository

2. Install compiler, build tools, and libraries

```
sudo apt install g++ build-essential libglu1-mesa-dev libpng-dev
```

3. Navigate to main.cpp and compile

```
g++ -o CPPFightingGame main.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
```
```
./CPPFightingGame
```

<br>

# Getting Started (CMake)

1. Download ZIP or clone repository

2. Install CMake, compiler, build tools, and libraries

```
sudo apt install cmake g++ build-essential libglu1-mesa-dev libpng-dev

```

3. Navigate to CMakeLists.txt and compile

```
cmake .
```

```
make
```

```
./CPPFightingGame
```

<br>

# Tutorial Videos

https://youtube.com/playlist?list=PLWYGofN_jX5Apmb8pJUD8NN3KskHW2lcy

<br>

# OLC-3

This project uses olcPixelGameEngine by OneLoneCoder
https://github.com/OneLoneCoder/olcPixelGameEngine
Copyright 2018, 2019, 2020 OneLoneCoder.com
