#pragma once

#include "raylib.h"

#include <iostream>
#include <vector>
#include <filesystem>

#include "utils.h"

struct Audio{
    const char *path;
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
private:
    std::vector<Audio> audios;

public:
    AudioManager(){}
    ~AudioManager(){CloseAudioDevice();}

    std::vector<Audio> GetAudios() const{
        return audios;
    }

    void Init(std::string folder) {
        namespace fs = std::filesystem;
        InitAudioDevice();
        SetMasterVolume(0.1f);
        if (fs::is_directory(folder) && !fs::is_empty(folder)) {
            logger.Log(INFO, "Loading audios...");
            for (auto const& dir_entry : std::filesystem::directory_iterator{folder}) {
                std::cout << dir_entry.path() << '\n';
                std::string audio_path = dir_entry.path().string();
                Audio audio = {.path = audio_path.c_str()};
                audio.Load();
                audios.push_back(audio);
            }
        }
    }

    void Play(Audio audio) {
        audio.Play();
    }
};
