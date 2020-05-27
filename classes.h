#ifndef CLASSES_H

#include <iostream>
#include <string>

#include "projFunctions.hpp"
using namespace std;

#define CLASSES_H
#define NPCDIR_LEFT 32
#define NPCDIR_RIGHT 64
#define NPCDIR_DOWN 0
#define NPCDIR_UP 96

//define NPCsprite class
class PlaceSprite_SDL162 {
        public:
    //constructor
    PlaceSprite_SDL162(){};

    void loadTexture(const char* path, SDL_Renderer* render) {
        SDL_Surface* tmpSurface = NULL;
        /*     stringstream error;
    try { */
        // load player spritesheet
        if ((tmpSurface = IMG_Load(path)) == NULL) {
            printErrorAndReboot(("Failed to load image to surface: " + string(SDL_GetError())).c_str());
        }

        if ((texture = SDL_CreateTextureFromSurface(render, tmpSurface)) == NULL) {
            printErrorAndReboot(("Failed to initialize image texture: " + string(SDL_GetError())).c_str());
        }
        /*     } */

        /*     catch (string error_str) {
      cout << error_str << "\n";
    } */

        SDL_FreeSurface(tmpSurface);
    }

    void setRects(int x, int y, int destW, int destH, int srcW, int srcH) {
        destRect = { x, y, destW, destH };
        srcRect = { 0, 0, srcW, srcH };
    }

    void setSpriteDims(int w, int h) {
        sprWidth = w;
        sprHeight = h;
    }

    int ts = 0;

    int sprWidth;
    int sprHeight;

    int destWidth;
    int destHeight;

    //declare destination and source rects
    SDL_Rect destRect;
    SDL_Rect srcRect;

    //declare source coords
    int srcX = 0;
    int srcY = 0;

    //declare image width and height vars
    int spriteSheetWidth = 0;
    int spriteSheetHeight = 0;

    //sprite texture
    SDL_Texture* texture = NULL;
    //sprite animation speed
    int shiftSpeed;
    //sprite movement speed
    int speed;
};

//define NPCsprite class
class NPCSprite_SDL162 {
        public:
    //constructor
    NPCSprite_SDL162(){};

    void movePath() {
        if (ts >= 0 && ts < 63) {
            this->srcRect.y = NPCDIR_DOWN;
            this->destRect.y += speed;
            moving = true;
        }
        if (ts >= 63 && ts < 127) {
            this->srcRect.y = NPCDIR_RIGHT;
            this->destRect.x += speed;
            moving = true;
        }
        if (ts >= 127 && ts < 191) {
            this->srcRect.y = NPCDIR_UP;
            this->destRect.y -= speed;
            moving = true;
        }
        if (ts >= 191 && ts < 255) {
            this->srcRect.y = NPCDIR_LEFT;
            this->destRect.x -= speed;
            moving = true;
        }

        if (ts >= 255) ts = 0;
    }

    void loadTexture(const char* path, SDL_Renderer* render) {
        SDL_Surface* tmpSurface = NULL;
        /*     stringstream error;
    try { */
        // load player spritesheet
        if ((tmpSurface = IMG_Load(path)) == NULL) {
            printErrorAndReboot(("Failed to load image to surface: " + string(SDL_GetError())).c_str());
        }

        if ((texture = SDL_CreateTextureFromSurface(render, tmpSurface)) == NULL) {
            printErrorAndReboot(("Failed to initialize image texture: " + string(SDL_GetError())).c_str());
        }
        /*     } */

        /*     catch (string error_str) {
      cout << error_str << "\n";
    } */

        SDL_FreeSurface(tmpSurface);
    }

    void setRects(int x, int y, int destW, int destH, int srcW, int srcH) {
        destRect = { x, y, destW, destH };
        srcRect = { 0, 0, srcW, srcH };
    }

    void setSpriteDims(int w, int h) {
        sprWidth = w;
        sprHeight = h;
    }

    int ts = 0;

    int sprWidth;
    int sprHeight;

    int destWidth;
    int destHeight;

    //declare destination and source rects
    SDL_Rect destRect;
    SDL_Rect srcRect;

    //declare source coords
    int srcX = 0;
    int srcY = 0;

    //declare image width and height vars
    int spriteSheetWidth = 0;
    int spriteSheetHeight = 0;

    //sprite texture
    SDL_Texture* texture = NULL;
    //sprite animation speed
    int shiftSpeed;
    //sprite movement speed
    int speed;

    bool moving;

    int shiftCont;
};

//define sprite class
class Sprite_SDL162 {
        public:
    //constructor
    Sprite_SDL162(){};

    void loadTexture(const char* path, SDL_Renderer* render) {
        SDL_Surface* tmpSurface = NULL;
        /*     stringstream error;
    try { */
        // load player spritesheet
        if ((tmpSurface = IMG_Load(path)) == NULL) {
            printErrorAndReboot(("Failed to load image to surface: " + string(SDL_GetError())).c_str());
        }

        if ((texture = SDL_CreateTextureFromSurface(render, tmpSurface)) == NULL) {
            printErrorAndReboot(("Failed to initialize image texture: " + string(SDL_GetError())).c_str());
        }
        /*     } */

        /*     catch (string error_str) {
      cout << error_str << "\n";
    } */

        SDL_FreeSurface(tmpSurface);
    }

    void setRects(int x, int y, int destW, int destH, int srcW, int srcH) {
        destRect = { x, y, destW, destH };
        srcRect = { 0, 0, srcW, srcH };
    }

    void setSpriteDims(int w, int h) {
        sprWidth = w;
        sprHeight = h;
    }

    int sprWidth;
    int sprHeight;

    int destWidth;
    int destHeight;

    //declare destination and source rects
    SDL_Rect destRect;
    SDL_Rect srcRect;

    //declare source coords
    int srcX = 0;
    int srcY = 0;

    //declare image width and height vars
    int spriteSheetWidth = 0;
    int spriteSheetHeight = 0;

    //sprite texture
    SDL_Texture* texture = NULL;
    //sprite animation speed
    int shiftSpeed;
    //sprite movement speed
    int speed;

    bool moving;

    int shiftCont = 0;
};
#endif
