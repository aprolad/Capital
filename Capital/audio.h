#pragma once
#include <string>
#include <memory>
#include <sdl/SDL_mixer.h>
class sample {
public:
    sample(const std::string& path, int volume);
    void play();
    void play(int times);
    void set_volume(int volume);

private:
    std::unique_ptr<Mix_Chunk, void (*)(Mix_Chunk*)> chunk;
};