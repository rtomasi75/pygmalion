# Pygmalion
Pygmalion primarily is a chess-engine. The layout of the source-code is however designed to also support other chess-like boardgames. Tic Tac Toe being the toy example in the repo to demonstrate this.

## Current version

Pygmalion is still in a very early developement state. An official release is not available yet, however you can try the latest source-code by following the instructions below. Some of the currently implemented features are:
- Winboard/XBoard version 2 support
- Principal Variation Search
- Transposition Table
- Aspiration Windows
- Recursive Nullmove Pruning
- History Heuristics
- Killermove Heuristics
- Futility Pruning

Pondering, multi-core support and Late Move Reductions are currently not implemented. The evaluation function is not yet finished: it considers attacks, mobility, control, kingsafety and pawn-structure. The weights for the different terms still need to be tuned.

## Using Pygmalion

Pygmalion isn't a stand-alone chess-program with an own GUI. It is designed to integrate with most of the available GUIs for chess, notably [Winboard](http://www.open-aurec.com/wbforum/viewtopic.php?t=51528)/[XBoard](https://www.gnu.org/software/xboard/), [Arena](http://www.playwitharena.de/) and [Cute Chess](https://github.com/cutechess/cutechess/releases).

Upon start-up, Pygmalion will attempt to create .data files in its working-directory if they aren't present. If the files aren't present, it will nevertheless function properly,  but may take a tiny bit longer to start. That is because the lookup-tables contained in those files will have to be created on the fly. If you do not want it to create these files, just do not grant it write permission to its working-directory.

## Building Pygmalion
To build Pygmalion, you will need CMake (min. version 3.16) combined with a C++17 capable toolchain. The source-code is designed for maximum portability and does not rely on any third-party libraries. Please note that the source-code heavily relies on templates and compile-time evaluation - building can take some time.

### Building on Linux

To build Pygmalion on Linux you need to first install the packages that are required for building (cmake, make, a C++17 capable compiler). The recommended compiler is clang 10.0.0.

There is a known issue when building with g++ 10.2.1 that causes the build to fail with an internal compiler error. If you want to use g++, it is recommended to use g++ 9.3.0.

You can use the following commands to build Pygmalion:
```
mkdir pygmalion_build
cd pygmalion_build
cmake [PYGMALION_SOURCE] -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-march=native" -DOPTIMIZE_LINK_TIME=ON
make
```
where `[PYGMALION_SOURCE]` specifies the folder in which you have previously cloned this repository.

To run the executable that has been built type
```
./pygmalion-chess-frontend/pygmalion-chess-engine
```


### Building with Microsoft Visual Studio

You should always use the latest version of Visual Studio when building Pygmalion. You can either use [TortoiseGit](https://tortoisegit.org/), or clone the repository directly using Visual Studio. Choose the "x64-Clang-Release" CMake configuration for building.
