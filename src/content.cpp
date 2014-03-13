#include "content.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

namespace Suidao {

void Content::LoadContent(std::string folder,
                          SDL_PixelFormat* format) {
    // TODO: Write code to deal with wrapping default content.
    // i.e. the first folder loaded is default, and therefore
    // is accessed from some default folder in the Content
    // hierarchy, rather than from the actual folder name.
    _LoadFolder(folder, "", format);
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

void Content::_LoadFolder(std::string root, std::string path,
                          SDL_PixelFormat* format) {
    DIR *dir;
    dirent *ent;
    dir = opendir((root + path).c_str());
    if (dir != NULL) {
        if (*(root.end()-1) != '/') {
            root = root + "/";
        }
        while ((ent = readdir (dir)) != NULL) {
            std::string file_path;
            if (ent->d_name[0] == '.') {
                continue;
            }
            if (path.size() != 0 && *(path.end()-1) != '/') {
                file_path = path + "/" + std::string(ent->d_name);
            } else {
                file_path = path + std::string(ent->d_name);
            }
            
            SDL_Surface* loaded_image;
            
#ifdef _WIN32
            if (ent->d_type == DT_REG) {
#else
            struct stat file_attributes;
            stat((root + file_path).c_str(), &file_attributes);
            if (S_ISREG(file_attributes.st_mode)) {
#endif
                switch (_FileType(ent->d_name)) {
                    case GRAPHIC:
                        loaded_image =
                                IMG_Load((root + file_path).c_str());
                        
                        if (loaded_image != NULL) {
                            _graphics[file_path] =
                                    SDL_ConvertSurface(loaded_image,
                                                       format, 0);
                        }
                        break;
                    case SOUND:
                        _sounds[file_path] =
                                Mix_LoadWAV((root + file_path).c_str());
                        break;
                    case MUSIC:
                        _musics[file_path] =
                                Mix_LoadMUS((root + file_path).c_str());
                            break;
                    default:
                        break;
                }
#ifdef _WIN32
            } else if (ent->d_type == DT_DIR) {
#else
            } else if (S_ISDIR(file_attributes.st_mode)) {
#endif
                _LoadFolder(root, std::string(file_path), format);
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
