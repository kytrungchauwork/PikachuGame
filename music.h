
#ifndef _MUSIC_H                    // Header Guard: This ensures that the header file is included only once during compilation.
#define _MUSIC_H

#include <iostream>
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib, "Winmm.lib")
using namespace std;
void bgSound();            // Play background music

void tapSound();                    // Play if player choose one pokemon when playing

void correctSound();         // Play if 2 pokemon connected successfully 

void wrongSound();            // Play if 2 pokemon connected unsuccessfully 

void stopBgSound();

#endif