#ifndef CONTENT_HPP
#define CONTENT_HPP
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include <string>
#include <map>

#include "animation.hpp"

namespace Suidao {

enum ContentType { GRAPHIC, SOUND, MUSIC, ANIMATION, SCRIPT, OTHER };
const int NUM_CONTENT_TYPES = (int)OTHER;


// This class provides access to the content folder by filename.
// It automatically reads in the entire contents of each of the content
// folders and provides a path-like interface to the content.
class Content {
    std::map<std::string,SDL_Texture*> _graphics;
    std::map<std::string,Animation> _animations;
    std::map<std::string,Mix_Chunk*> _sounds;
    std::map<std::string,Mix_Music*> _musics;
    std::map<std::string,std::string> _scripts;
    // Recursively loads a folder
    void _LoadFolder(std::string root, std::string path,
                     ContentType type, SDL_Renderer* renderer);
    ContentType _FileType(std::string path); // Deprecated
    Animation _LoadAnimation(std::string path);
    std::string _LoadScript(std::string path);
  public:
    // Loads a given content folder
    void LoadContent(std::string folder, SDL_Renderer* renderer);
    
    // Get various content
    SDL_Texture* GetGraphic(std::string path) const;
    Animation GetAnimation(std::string path) const;
    Mix_Chunk* GetSound(std::string path) const;
    Mix_Music* GetMusic(std::string path) const;
    std::string GetScript(std::string path) const;
};

}

#endif // CONTENT_HPP
