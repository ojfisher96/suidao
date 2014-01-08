#include "content.hpp"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

namespace Suidao {

void Content::LoadContent(std::string folder) {
    // TODO: Write code to deal with wrapping default content.
    // i.e. the first folder loaded is default, and therefore
    // is accessed from some default folder in the Content
    // hierarchy, rather than from the actual folder name.
    _LoadFolder(folder);
}

SDL_Surface* Content::GetGraphic(std::string path) {
    return _graphics[path];
}

Mix_Chunk* Content::GetSound(std::string path) {
    return _sounds[path];
}

Mix_Music* Content::GetMusic(std::string path) {
    return _musics[path];
}

void Content::_LoadFolder(std::string path) {
    DIR *dir;
    dirent *ent;
    dir = opendir(path.c_str());
    if (dir != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            std::string full_path;
            if (ent->d_name[0] == '.') {
                continue;
            }
            if (*(path.end()-1) != '/') {
                full_path = path + "/" + std::string(ent->d_name);
            } else {
                full_path = path + std::string(ent->d_name);
            }
            

            SDL_Surface* loaded_image;
            
            struct stat file_attributes;
            stat(full_path.c_str(), &file_attributes);
            
            if (S_ISREG(file_attributes.st_mode)) {
                switch (_FileType(ent->d_name)) {
                    case GRAPHIC:
                        loaded_image = IMG_Load(full_path.c_str());
                        if (loaded_image != NULL) {
                            _graphics[full_path] =
                                    SDL_DisplayFormat(loaded_image);
                        }
                        break;
                    case SOUND:
                        _sounds[full_path] =
                                Mix_LoadWAV(full_path.c_str());
                        break;
                    case MUSIC:
                        _musics[full_path] =
                                Mix_LoadMUS(full_path.c_str());
                            break;
                    default:
                        break;
                }
            } else if (S_ISDIR(file_attributes.st_mode)) {
                _LoadFolder(std::string(full_path));
            }
        }
    }
    closedir(dir);
}

ContentType Content::_FileType(std::string path) {
    int dot = path.find_first_of('.');
    if (dot == -1) { // Fairly sure this is right.
        return OTHER;
    }
    if (0 == path.compare(dot + 1, path.length(), "png")) {
        return GRAPHIC;
    } else if (0 == path.compare(dot + 1, path.length(), "wav")) {
        return SOUND;
    } else if (0 == path.compare(dot + 1, path.length(), "ogg")) {
        return MUSIC;
    }
    return OTHER;
}

}
