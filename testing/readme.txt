The version of Pygmalion in this folder was build for Marcel Vanthoor (http://talkchess.com/forum3/memberlist.php?mode=viewprofile&u=11930) who has been so kind to help me testing the current strength of the engine, with the goal of getting a rough estimate of it's ELO rating on the CCRL scale.

There is one version built to run against Debian GNU/Linux 11 (bullseye) on an Intel Skylake CPU. The source code used for this build is commit 2a31bc385264de0a5d4c01e2c6ab1f8e8d3299f7 (special version for elo testing) of the master branch. 

The other version is built to run on Windows (x64) on an Intel Skylake CPU. The source code used for this build is commit 9b9421d63bc8ba253a38a90dd99259e3347ae2d6 (elo testing version for windows) of the master branch. 

Both versions have the transposition table size hardcoded to 16MB and require the following CPU features to run properly:
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
