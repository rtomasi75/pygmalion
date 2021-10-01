The version of Pygmalion in this folder was build for Marcel Vanthoor (http://talkchess.com/forum3/memberlist.php?mode=viewprofile&u=11930) who has been so kind to help me testing the current strength of the engine, with the goal of getting a rough estimate of it's ELO rating on the CCRL scale.

It is build to run against Debian GNU/Linux 11 (bullseye) on an Intel Skylake CPU. The source code used for this build is commit 2a31bc385264de0a5d4c01e2c6ab1f8e8d3299f7 (special version for elo testing) of the master branch. Transposition table size is hardcoded to 16MB.

The following CPU features are required for this version to run properly:
  X86
  X64
  MMX
  POPCNT
  BMI
  BMI2
  SSE
  SSE2
  SSE3
  SSSE3
  SSE41
  SSE42
  AVX
  AVX2
  
Build log:

user@liquidity:~/pygmalion$ uname -a
Linux liquidity 4.4.0-19041-Microsoft #1237-Microsoft Sat Sep 11 14:32:00 PST 2021 x86_64 GNU/Linux
user@liquidity:~/pygmalion$ cat /etc/*-release
PRETTY_NAME="Debian GNU/Linux 11 (bullseye)"
NAME="Debian GNU/Linux"
VERSION_ID="11"
VERSION="11 (bullseye)"
VERSION_CODENAME=bullseye
ID=debian
HOME_URL="https://www.debian.org/"
SUPPORT_URL="https://www.debian.org/support"
BUG_REPORT_URL="https://bugs.debian.org/"user@liquidity:~/pygmalion$ 
cmake /mnt/d/git/pygmalion -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_CXX_FLAGS="-march=skylake" -DBUILD_SHARED_LIBS=OFF -DCMAKE_EXE_LINKER_FLAGS="-static"
-- The C compiler identification is GNU 10.2.1
-- The CXX compiler identification is Clang 11.0.1
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- NOT building with compact slider magics
-- NOT building with indirect slider magics
-- trying to build with -flto
-- Performing Test COMPILER_SUPPORTS_FLTO
-- Performing Test COMPILER_SUPPORTS_FLTO - Failed
-- NOT building with -flto
-- Looking for pthread.h
-- Looking for pthread.h - found
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Failed
-- Looking for pthread_create in pthreads
-- Looking for pthread_create in pthreads - not found
-- Looking for pthread_create in pthread
-- Looking for pthread_create in pthread - found
-- Found Threads: TRUE
-- Configuring done
-- Generating done
-- Build files have been written to: /home/user/pygmalion
user@liquidity:~/pygmalion$ make -j10
Scanning dependencies of target pygmalion-intrinsics
[  1%] Building CXX object pygmalion-intrinsics/CMakeFiles/pygmalion-intrinsics.dir/src/command.cpp.o
[  3%] Building CXX object pygmalion-intrinsics/CMakeFiles/pygmalion-intrinsics.dir/src/command_debugCpu.cpp.o
[  3%] Building CXX object pygmalion-intrinsics/CMakeFiles/pygmalion-intrinsics.dir/src/command_debugCompiler.cpp.o
[  4%] Building CXX object pygmalion-intrinsics/CMakeFiles/pygmalion-intrinsics.dir/src/command_debugIntrinsics.cpp.o
[  5%] Building CXX object pygmalion-intrinsics/CMakeFiles/pygmalion-intrinsics.dir/src/command_help.cpp.o
[  6%] Building CXX object pygmalion-intrinsics/CMakeFiles/pygmalion-intrinsics.dir/src/command_quit.cpp.o
[  7%] Building CXX object pygmalion-intrinsics/CMakeFiles/pygmalion-intrinsics.dir/src/command_ver.cpp.o
[  8%] Building CXX object pygmalion-intrinsics/CMakeFiles/pygmalion-intrinsics.dir/src/compiler.cpp.o
[  9%] Building CXX object pygmalion-intrinsics/CMakeFiles/pygmalion-intrinsics.dir/src/engine.cpp.o
[ 10%] Building CXX object pygmalion-intrinsics/CMakeFiles/pygmalion-intrinsics.dir/src/cpu.cpp.o
[ 12%] Building CXX object pygmalion-intrinsics/CMakeFiles/pygmalion-intrinsics.dir/src/profiler.cpp.o
[ 13%] Linking CXX static library libpygmalion-intrinsics.a
[ 13%] Built target pygmalion-intrinsics
Scanning dependencies of target pygmalion-intrinsics-test
Scanning dependencies of target pygmalion-intrinsics-engine
Scanning dependencies of target pygmalion-state
[ 14%] Building CXX object pygmalion-intrinsics/CMakeFiles/pygmalion-intrinsics-engine.dir/test/engine.cpp.o
[ 15%] Building CXX object pygmalion-intrinsics/CMakeFiles/pygmalion-intrinsics-test.dir/test/unit.cpp.o
[ 16%] Building CXX object pygmalion-state/CMakeFiles/pygmalion-state.dir/src/pygmalion-state.cpp.o
[ 17%] Linking CXX executable pygmalion-intrinsics-engine
[ 18%] Linking CXX static library libpygmalion-state.a
[ 18%] Built target pygmalion-state
Scanning dependencies of target pygmalion-tictactoe-state
Scanning dependencies of target pygmalion-mechanics
Scanning dependencies of target pygmalion-chess-state
[ 19%] Building CXX object pygmalion-tictactoe-state/CMakeFiles/pygmalion-tictactoe-state.dir/src/pygmalion-tictactoe-state.cpp.o
[ 23%] Building CXX object pygmalion-chess-state/CMakeFiles/pygmalion-chess-state.dir/src/pygmalion-chess-state.cpp.o
[ 23%] Building CXX object pygmalion-chess-state/CMakeFiles/pygmalion-chess-state.dir/src/board.cpp.o
[ 23%] Building CXX object pygmalion-mechanics/CMakeFiles/pygmalion-mechanics.dir/src/pygmalion-mechanics.cpp.o
[ 23%] Built target pygmalion-intrinsics-engine
[ 24%] Linking CXX static library libpygmalion-mechanics.a
[ 25%] Linking CXX static library libpygmalion-tictactoe-state.a
[ 25%] Built target pygmalion-mechanics
Scanning dependencies of target pygmalion-dynamics
[ 25%] Built target pygmalion-tictactoe-state
Scanning dependencies of target pygmalion-tictactoe-mechanics
Scanning dependencies of target pygmalion-tictactoe-state-test
[ 26%] Building CXX object pygmalion-dynamics/CMakeFiles/pygmalion-dynamics.dir/src/pygmalion-dynamics.cpp.o
[ 27%] Building CXX object pygmalion-tictactoe-state/CMakeFiles/pygmalion-tictactoe-state-test.dir/test/main.cpp.o
[ 28%] Building CXX object pygmalion-tictactoe-mechanics/CMakeFiles/pygmalion-tictactoe-mechanics.dir/src/pygmalion-tictactoe-mechanics.cpp.o
[ 29%] Linking CXX static library libpygmalion-chess-state.a
[ 29%] Built target pygmalion-chess-state
Scanning dependencies of target pygmalion-chess-state-test
Scanning dependencies of target pygmalion-chess-mechanics
[ 30%] Building CXX object pygmalion-chess-state/CMakeFiles/pygmalion-chess-state-test.dir/test/main.cpp.o
[ 31%] Building CXX object pygmalion-chess-mechanics/CMakeFiles/pygmalion-chess-mechanics.dir/src/pygmalion-chess-mechanics.cpp.o
[ 32%] Linking CXX static library libpygmalion-dynamics.a
[ 34%] Linking CXX static library libpygmalion-tictactoe-mechanics.a
[ 34%] Built target pygmalion-dynamics
[ 34%] Built target pygmalion-tictactoe-mechanics
Scanning dependencies of target pygmalion-tictactoe-dynamics
Scanning dependencies of target pygmalion-tictactoe-mechanics-test
[ 35%] Building CXX object pygmalion-tictactoe-mechanics/CMakeFiles/pygmalion-tictactoe-mechanics-test.dir/test/main.cpp.o
[ 36%] Building CXX object pygmalion-tictactoe-dynamics/CMakeFiles/pygmalion-tictactoe-dynamics.dir/src/pygmalion-tictactoe-dynamics.cpp.o
[ 37%] Linking CXX executable pygmalion-tictactoe-state-test
[ 37%] Built target pygmalion-tictactoe-state-test
[ 38%] Linking CXX static library libpygmalion-chess-mechanics.a
[ 39%] Linking CXX static library libpygmalion-tictactoe-dynamics.a
[ 39%] Built target pygmalion-chess-mechanics
Scanning dependencies of target pygmalion-chess-dynamics
Scanning dependencies of target pygmalion-chess-mechanics-test
[ 40%] Building CXX object pygmalion-chess-mechanics/CMakeFiles/pygmalion-chess-mechanics-test.dir/test/main.cpp.o
[ 40%] Built target pygmalion-tictactoe-dynamics
Scanning dependencies of target pygmalion-tictactoe-dynamics-test
[ 41%] Building CXX object pygmalion-chess-dynamics/CMakeFiles/pygmalion-chess-dynamics.dir/src/command_debugAttacked.cpp.o
[ 45%] Building CXX object pygmalion-chess-dynamics/CMakeFiles/pygmalion-chess-dynamics.dir/src/command_debugKingArea.cpp.o
[ 46%] Building CXX object pygmalion-chess-dynamics/CMakeFiles/pygmalion-chess-dynamics.dir/src/command_debugMagics.cpp.o
[ 46%] Building CXX object pygmalion-chess-dynamics/CMakeFiles/pygmalion-chess-dynamics.dir/src/command_debugCheck.cpp.o
[ 46%] Building CXX object pygmalion-chess-dynamics/CMakeFiles/pygmalion-chess-dynamics.dir/src/command_debugMovegen.cpp.o
[ 47%] Building CXX object pygmalion-tictactoe-dynamics/CMakeFiles/pygmalion-tictactoe-dynamics-test.dir/test/main.cpp.o
[ 48%] Linking CXX executable pygmalion-chess-state-test
[ 49%] Linking CXX executable pygmalion-tictactoe-mechanics-test
[ 49%] Built target pygmalion-chess-state-test
[ 50%] Building CXX object pygmalion-chess-dynamics/CMakeFiles/pygmalion-chess-dynamics.dir/src/command_debugTargeted.cpp.o
[ 50%] Built target pygmalion-tictactoe-mechanics-test
[ 51%] Building CXX object pygmalion-chess-dynamics/CMakeFiles/pygmalion-chess-dynamics.dir/src/command_debugTropism.cpp.o
[ 52%] Linking CXX executable pygmalion-tictactoe-dynamics-test
[ 52%] Built target pygmalion-tictactoe-dynamics-test
[ 53%] Building CXX object pygmalion-chess-dynamics/CMakeFiles/pygmalion-chess-dynamics.dir/src/command_debugUntabled.cpp.o
[ 54%] Building CXX object pygmalion-chess-dynamics/CMakeFiles/pygmalion-chess-dynamics.dir/src/command_getFen.cpp.o
[ 56%] Building CXX object pygmalion-chess-dynamics/CMakeFiles/pygmalion-chess-dynamics.dir/src/command_perft.cpp.o
[ 57%] Building CXX object pygmalion-chess-dynamics/CMakeFiles/pygmalion-chess-dynamics.dir/src/command_setFen.cpp.o
[ 58%] Linking CXX executable pygmalion-chess-mechanics-test
[ 59%] Building CXX object pygmalion-chess-dynamics/CMakeFiles/pygmalion-chess-dynamics.dir/src/command_testMovegen.cpp.o
[ 60%] Building CXX object pygmalion-chess-dynamics/CMakeFiles/pygmalion-chess-dynamics.dir/src/generator.cpp.o
[ 61%] Building CXX object pygmalion-chess-dynamics/CMakeFiles/pygmalion-chess-dynamics.dir/src/pygmalion-chess-dynamics.cpp.o
[ 61%] Built target pygmalion-chess-mechanics-test
[ 62%] Linking CXX static library libpygmalion-chess-dynamics.a
[ 62%] Built target pygmalion-chess-dynamics
Scanning dependencies of target pygmalion-chess-dynamics-test
Scanning dependencies of target pygmalion-evaluation
[ 64%] Building CXX object pygmalion-evaluation/CMakeFiles/pygmalion-evaluation.dir/src/pygmalion-evaluation.cpp.o
[ 64%] Building CXX object pygmalion-chess-dynamics/CMakeFiles/pygmalion-chess-dynamics-test.dir/test/main.cpp.o
[ 65%] Linking CXX static library libpygmalion-evaluation.a
[ 65%] Built target pygmalion-evaluation
Scanning dependencies of target pygmalion-search
Scanning dependencies of target pygmalion-tictactoe-evaluation
Scanning dependencies of target pygmalion-chess-evaluation
[ 67%] Building CXX object pygmalion-search/CMakeFiles/pygmalion-search.dir/src/pygmalion-search.cpp.o
[ 68%] Building CXX object pygmalion-tictactoe-evaluation/CMakeFiles/pygmalion-tictactoe-evaluation.dir/src/evaluator.cpp.o
[ 69%] Building CXX object pygmalion-tictactoe-evaluation/CMakeFiles/pygmalion-tictactoe-evaluation.dir/src/pygmalion-tictactoe-evaluation.cpp.o
[ 70%] Building CXX object pygmalion-chess-evaluation/CMakeFiles/pygmalion-chess-evaluation.dir/src/command_debugControl.cpp.o
[ 74%] Building CXX object pygmalion-chess-evaluation/CMakeFiles/pygmalion-chess-evaluation.dir/src/command_debugSEE.cpp.o
[ 74%] Building CXX object pygmalion-chess-evaluation/CMakeFiles/pygmalion-chess-evaluation.dir/src/evaluator.cpp.o
[ 74%] Building CXX object pygmalion-chess-evaluation/CMakeFiles/pygmalion-chess-evaluation.dir/src/command_debugPawntable.cpp.o
[ 74%] Building CXX object pygmalion-chess-evaluation/CMakeFiles/pygmalion-chess-evaluation.dir/src/pygmalion-chess-evaluation.cpp.o
[ 75%] Linking CXX static library libpygmalion-search.a
[ 76%] Linking CXX static library libpygmalion-tictactoe-evaluation.a
[ 76%] Built target pygmalion-search
Scanning dependencies of target pygmalion-frontend
[ 78%] Building CXX object pygmalion-frontend/CMakeFiles/pygmalion-frontend.dir/src/pygmalion-frontend.cpp.o
[ 78%] Built target pygmalion-tictactoe-evaluation
Scanning dependencies of target pygmalion-tictactoe-search
Scanning dependencies of target pygmalion-tictactoe-evaluation-test
[ 79%] Building CXX object pygmalion-tictactoe-evaluation/CMakeFiles/pygmalion-tictactoe-evaluation-test.dir/test/main.cpp.o
[ 80%] Building CXX object pygmalion-tictactoe-search/CMakeFiles/pygmalion-tictactoe-search.dir/src/pygmalion-tictactoe-search.cpp.o
[ 81%] Linking CXX executable pygmalion-chess-dynamics-test
[ 81%] Built target pygmalion-chess-dynamics-test
[ 82%] Linking CXX static library libpygmalion-frontend.a
[ 83%] Linking CXX static library libpygmalion-chess-evaluation.a
[ 83%] Built target pygmalion-frontend
[ 84%] Linking CXX static library libpygmalion-tictactoe-search.a
[ 84%] Built target pygmalion-chess-evaluation
Scanning dependencies of target pygmalion-chess-evaluation-test
Scanning dependencies of target pygmalion-chess-search
[ 85%] Building CXX object pygmalion-chess-evaluation/CMakeFiles/pygmalion-chess-evaluation-test.dir/test/main.cpp.o
[ 86%] Building CXX object pygmalion-chess-search/CMakeFiles/pygmalion-chess-search.dir/src/pygmalion-chess-search.cpp.o
[ 86%] Built target pygmalion-tictactoe-search
Scanning dependencies of target pygmalion-tictactoe-search-test
[ 87%] Building CXX object pygmalion-tictactoe-search/CMakeFiles/pygmalion-tictactoe-search-test.dir/test/main.cpp.o
[ 89%] Linking CXX executable pygmalion-tictactoe-evaluation-test
[ 89%] Built target pygmalion-tictactoe-evaluation-test
[ 90%] Linking CXX static library libpygmalion-chess-search.a
[ 90%] Built target pygmalion-chess-search
Scanning dependencies of target pygmalion-chess-frontend
Scanning dependencies of target pygmalion-chess-search-test
[ 92%] Building CXX object pygmalion-chess-frontend/CMakeFiles/pygmalion-chess-frontend.dir/src/pygmalion-chess-frontend.cpp.o
[ 92%] Building CXX object pygmalion-chess-search/CMakeFiles/pygmalion-chess-search-test.dir/test/main.cpp.o
[ 93%] Linking CXX executable pygmalion-tictactoe-search-test
[ 93%] Built target pygmalion-tictactoe-search-test
[ 94%] Linking CXX executable pygmalion-chess-evaluation-test
[ 94%] Built target pygmalion-chess-evaluation-test
[ 95%] Linking CXX static library libpygmalion-chess-frontend.a
[ 95%] Built target pygmalion-chess-frontend
Scanning dependencies of target pygmalion-chess-frontend-test
[ 96%] Building CXX object pygmalion-chess-frontend/CMakeFiles/pygmalion-chess-frontend-test.dir/test/main.cpp.o
[ 97%] Linking CXX executable pygmalion-chess-search-test
[ 97%] Built target pygmalion-chess-search-test
[ 98%] Linking CXX executable pygmalion-chess-frontend-test
[ 98%] Built target pygmalion-chess-frontend-test
[100%] Linking CXX executable pygmalion-intrinsics-test
[100%] Built target pygmalion-intrinsics-test