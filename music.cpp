#include <iostream>
#include <windows.h>

void bgSound() {
    // Loop the background music indefinitely
    if (true) {
        PlaySound(TEXT("PikachuSong.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    }
}

void tapSound() {
    PlaySound(TEXT("click.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void correctSound() {
    PlaySound(TEXT("correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void wrongSound() {
    PlaySound(TEXT("wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void stopBgSound() {
    PlaySound(nullptr, 0, 0);
}
