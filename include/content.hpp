#ifndef CONTENT_HPP
#define CONTENT_HPP
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include <string>
#include <map>

namespace Suidao {

enum ContentType { GRAPHIC, SOUND, MUSIC, OTHER };
    
class Content {
    std::map<std::string,SDL_Surface*> _graphics;
    std::map<std::string,Mix_Chunk*> _sounds;
    std::map<std::string,Mix_Music*> _musics;
    void _LoadFolder(std::string path);
    ContentType _FileType(std::string path);
  public:
    void LoadContent(std::string folder);
    SDL_Surface* GetGraphic(std::string path);
    Mix_Chunk* GetSound(std::string path);
    Mix_Music* GetMusic(std::string path);
};

}

#endif // CONTENT_HPP
