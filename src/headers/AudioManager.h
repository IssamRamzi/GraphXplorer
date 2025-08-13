#include "raylib.h"

#include <iostream>

struct Audio{
    char *path;
    Sound sound;

    void Load(){
        if(path == nullptr) return;
        
        sound = LoadSound(path);
    }

    void Play(){
        if(IsAudioDeviceReady()){
            PlaySound(sound);
        }
    }
};

class AudioManager{


public:
    AudioManager(){}
    ~AudioManager(){CloseAudioDevice();}

    void Init();
};

void AudioManager::Init(){
    InitAudioDevice();
}
