#ifdef NXDK
//XBOX INCLUDES
#include <hal/debug.h>
#include <hal/video.h>
#include <hal/xbox.h>
#include <windows.h>
#endif
//SDL INCLUDES
#include <SDL.h>
#include <SDL_image.h>
/* #include <SDL_mixer.h> */

//GENERAL PURPOSE INCLUDES
#include <string>
/* #include <iostream> */
/* using namespace std; */

//PROJECT-SPECIFIC INCLUDES
#include "classes.h"
#include "projFunctions.hpp"

#define INITSCRWIDTH 800
#define INITSCRHEIGHT 600
#define SPRWIDTH 32
#define SPRHEIGHT 32
#define SPRDESTWIDTH 64
#define SPRDESTHEIGHT 64
#define INITSPRSPEED 2
#define INITSPRSHFTSPEED 3


int main() {
    Sprite_SDL162 player;
    NPCSprite_SDL162 npc1;

    //declare window, renderer and events
    SDL_Window* win = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Event events;

    //declare image file surface and texture
    SDL_Surface* imgSurface;

    SDL_Texture* bgTexture;

    //declare screen dimension vars
    int scrWidth = INITSCRWIDTH;
    int scrHeight = INITSCRHEIGHT;

    //declare background rects
    SDL_Rect bgDestRect = { 0, 0, scrWidth, scrHeight };
    //  SDL_Rect bgSrcRect = {0, 0, scrWidth / 2, scrHeight / 2};

    /*   //declare music
  Mix_Music *bgmusic = NULL;

  Mix_Chunk *sfx1 = NULL; */

    //init
    player.setSpriteDims(32, 32);
    player.setRects(5, 5, SPRDESTWIDTH, SPRDESTHEIGHT, SPRWIDTH, SPRHEIGHT);
    player.shiftSpeed = 3;
    player.speed = 2;

    npc1.setSpriteDims(32, 32);
    npc1.setRects(120, 120, SPRDESTWIDTH, SPRDESTHEIGHT, SPRWIDTH, SPRHEIGHT);
    npc1.shiftSpeed = 4;
    npc1.speed = 2;

    /*   std::stringstream error;
  try{ */
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {                      //SDL library functions init.
        printErrorAndReboot(("Failed to initialize SDL: " + string(SDL_GetError())).c_str());  //in case of errors, throw them
    }
    if ((win = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, scrWidth, scrHeight, SDL_WINDOW_RESIZABLE)) == NULL) {  //create main SDL window, 640 * 480, centered in both axis and resizable
        printErrorAndReboot("Failed to create a window");
    }
    if ((renderer = SDL_CreateRenderer(win, -1, (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) == NULL) {  //create renderer for main window in index -1, accelerated and using VSync
        printErrorAndReboot("Failed to initialize renderer");
    }

    player.loadTexture("res/spritesheets/link.png", renderer);
    npc1.loadTexture("res/spritesheets/malon.png", renderer);

    // load background
    if ((imgSurface = IMG_Load("res/bg/grass_2.png")) == NULL) {
        printErrorAndReboot("Failed to load image to surface");
    }
    if ((bgTexture = SDL_CreateTextureFromSurface(renderer, imgSurface)) == NULL) {
        printErrorAndReboot("Failed to initialize image texture");
    }
    SDL_FreeSurface(imgSurface);
    /*      //init audio
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
      error << "Failed to initialize audio: " << SDL_GetError();
      throw(error.str());
    }

    //load music
    if ((bgmusic = Mix_LoadMUS("res/music/bgmusic.ogg")) == NULL){
      error << "Failed to load music: " << SDL_GetError();
      throw(error.str());
    }
    
    //load sfxs
    if ((sfx1 = Mix_LoadWAV("res/sfx/bruh.ogg")) == NULL) {
      error << "Failed to load SFXs: " << SDL_GetError();
      throw(error.str());
    }
  }
 */

    //mainloop()

    bool mainLoop = true;

    /*   Mix_PlayMusic(bgmusic, -1); */

    while (mainLoop) {
        player.moving = false;
        SDL_PumpEvents();
        while (SDL_PollEvent(&events)) {
            switch (events.type) {
                //handle window events
                case SDL_WINDOWEVENT:
                    switch (events.window.event) {
                        case SDL_WINDOWEVENT_RESIZED:
                            bgDestRect.w = scrWidth = events.window.data1;
                            bgDestRect.h = scrHeight = events.window.data2;
                            break;
                    }
                    break;
                case SDL_QUIT:
                    mainLoop = false;
                    break;
            }
        }
        const Uint8* state = SDL_GetKeyboardState(NULL);

        //if Z is pressed
        if (state[SDL_SCANCODE_Z]) {
            //      Mix_PlayChannel(-1, sfx1, 0);
        }

        //if X is pressed
        if (state[SDL_SCANCODE_X]) {
            player.speed = 4;
        }

        else
            player.speed = 2;

        //if left arrow is pressed
        if (state[SDL_SCANCODE_LEFT]) {
            player.srcRect.y = 32;
            if (player.destRect.x > 0) {
                player.destRect.x -= player.speed;
                player.moving = true;
            }
        }

        //right arrow is pressed
        else if (state[SDL_SCANCODE_RIGHT]) {
            player.srcRect.y = 64;
            if (player.destRect.x < scrWidth - player.destRect.w) {
                player.destRect.x += player.speed;
                player.moving = true;
            }
        }

        //up arrow is pressed
        else if (state[SDL_SCANCODE_UP]) {
            player.srcRect.y = 96;
            if (player.destRect.y > 0) {
                player.destRect.y -= player.speed;
                player.moving = true;
            }
        }

        //down arrow is pressed
        else if (state[SDL_SCANCODE_DOWN]) {
            player.srcRect.y = 0;
            if (player.destRect.y < scrHeight - player.destRect.h) {
                player.destRect.y += player.speed;
                player.moving = true;
            }
        }

        else
            player.moving = false;

        npc1.movePath();
        npc1.ts += 1;

        SDL_QueryTexture(player.texture, NULL, NULL, &player.spriteSheetWidth, &player.spriteSheetHeight);
        SDL_QueryTexture(npc1.texture, NULL, NULL, &npc1.spriteSheetWidth, &npc1.spriteSheetHeight);

        if (player.srcRect.x == (player.spriteSheetWidth - player.sprWidth)) {
            player.srcRect.x = 32;
        }

        if (npc1.srcRect.x == (npc1.spriteSheetWidth - npc1.sprWidth)) {
            npc1.srcRect.x = 32;
        }

        if (player.moving) {
            if (player.shiftCont > player.shiftSpeed) {
                player.srcRect.x += player.sprWidth;
                player.shiftCont = 0;
            } else
                player.shiftCont++;
        }

        else {
            player.srcRect.x = 0;
        }

        if (npc1.moving) {
            if (npc1.shiftCont > npc1.shiftSpeed) {
                npc1.srcRect.x += npc1.sprWidth;
                npc1.shiftCont = 0;
            } else
                npc1.shiftCont++;
        }

        else {
            npc1.srcRect.x = 0;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, bgTexture, NULL, &bgDestRect);

        SDL_RenderCopy(renderer, player.texture, &player.srcRect, &player.destRect);

        SDL_RenderCopy(renderer, npc1.texture, &npc1.srcRect, &npc1.destRect);

        SDL_RenderPresent(renderer);
    }

    if (player.texture) SDL_DestroyTexture(player.texture);
    if (npc1.texture) SDL_DestroyTexture(npc1.texture);
    if (bgTexture) SDL_DestroyTexture(bgTexture);

    if (renderer) SDL_DestroyRenderer(renderer);
    if (win) SDL_DestroyWindow(win);

/*     if (bgmusic) Mix_FreeMusic(bgmusic);

    Mix_Quit(); */
    IMG_Quit();
    SDL_Quit();
    return 0;
}
