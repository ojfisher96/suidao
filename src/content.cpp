#include "content.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include "jsoncpp/json/json.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include <fstream>

namespace Suidao {

const char *FOLDERS[] = {
    "graphics/",
    "sounds/",
    "music/",
    "animations/",
};

void Content::LoadContent(std::string folder,
                          SDL_Renderer* renderer) {
    // TODO: Write code to deal with wrapping default content.
    // i.e. the first folder loaded is default, and therefore
    // is accessed from some default folder in the Content
    // hierarchy, rather than from the actual folder name.

    if (*(folder.end()-1) != '/') {
        folder = folder + "/";
    }

    for (int t = 0; t < NUM_CONTENT_TYPES; t++) {
        _LoadFolder(folder + FOLDERS[t], "", (ContentType)t, renderer);
    }
}

SDL_Texture* Content::GetGraphic(std::string path) const {
    auto iterator = _graphics.find(path);
    SDL_Texture* asset = NULL;
    if (iterator != _graphics.end()) {
        asset = iterator->second;
    }
    return asset;
}

Mix_Chunk* Content::GetSound(std::string path) const {
    auto iterator = _sounds.find(path);
    Mix_Chunk* asset = NULL;
    if (iterator != _sounds.end()) {
        asset = iterator->second;
    }
    return asset;
}

Mix_Music* Content::GetMusic(std::string path) const {
    auto iterator = _musics.find(path);
    Mix_Music* asset = NULL;
    if (iterator != _musics.end()) {
        asset = iterator->second;
    }
    return asset;
}

Animation Content::GetAnimation(std::string path) const {
    auto iterator = _animations.find(path);
    Animation asset = Animation(NULL, -1);
    if (iterator != _animations.end()) {
        asset = iterator->second;
    }
    return asset;
}

void Content::_LoadFolder(std::string root, std::string path,
                          ContentType type, SDL_Renderer* renderer) {
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
                switch (type) {
                    case GRAPHIC:
                        loaded_image =
                                IMG_Load((root + file_path).c_str());
                        
                        if (loaded_image != NULL) {
                            _graphics[file_path] =
                                SDL_CreateTextureFromSurface(renderer,
                                                             loaded_image);
                        }
                        SDL_FreeSurface(loaded_image);
                        break;
                    case SOUND:
                        _sounds[file_path] =
                                Mix_LoadWAV((root + file_path).c_str());
                        break;
                    case MUSIC:
                        _musics[file_path] =
                                Mix_LoadMUS((root + file_path).c_str());
                        break;
                    case ANIMATION:
                        _animations[file_path] =
                                _LoadAnimation(root + file_path);
                        break;
                    default:
                        break;
                }
#ifdef _WIN32
            } else if (ent->d_type == DT_DIR) {
#else
            } else if (S_ISDIR(file_attributes.st_mode)) {
#endif
                _LoadFolder(root, std::string(file_path), type, renderer);
            }
        }
    }
    closedir(dir);
}

Animation Content::_LoadAnimation(std::string path) {
    Json::Value json_root;
    Json::Reader reader;

    std::ifstream json_file(path);
    std::string json_file_content(
        (std::istreambuf_iterator<char>(json_file)),
        std::istreambuf_iterator<char>());
    
    reader.parse(json_file_content, json_root);

    std::string graphic_name =
            json_root.get("graphic", "").asString();
    int height = json_root.get("height", -1).asInt();

    return Animation(GetGraphic(graphic_name), height);
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
