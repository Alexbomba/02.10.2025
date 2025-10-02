#include "project_02.10.2025.h"
#pragma comment(lib, "winmm.lib")

DWORD WINAPI MusicThread(void* param) {
    PlaySoundA("Pac-Man-intro-music.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    return 0;
}