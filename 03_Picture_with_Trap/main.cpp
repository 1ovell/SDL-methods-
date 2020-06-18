#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

const int SCREEN_WIDTH = 1204;
const int SCREEN_HEIGHT = 1688;

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

//The surface contained by the window
SDL_Surface* gScreenSurface = nullptr;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = nullptr;


//Starts up SDL and creates window
bool init(){
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << "SDL could not initialize! SDL_Error:\n" << SDL_GetError();
        success = false;
    }
    else{
        //Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if(gWindow == nullptr){
            cout << "Window could not be created! SDL_Error:\n" << SDL_GetError();
            success = false;
        }
        else{
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}


//Loads media
bool loadMedia(){
    //Loading success flag
    bool success = true;

    //Load splash image
    gHelloWorld = SDL_LoadBMP( "C:\\Users\\Sergey\\Documents\\CGames\\1zbDQPMQf2Q.bmp" );
    if(gHelloWorld == nullptr){
        cout << "Unable to load image! SDL Error:\n" << R"(C:\Users\Sergey\Documents\CGames\1zbDQPMQf2Q.bmp)" <<
                SDL_GetError();
        success = false;
    }

    return success;
}

//Frees media and shuts down SDL
void close(){
    //Deallocate surface
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = nullptr;

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    //Quit SDL subsystems
    SDL_Quit();
}

int main(int argv, char** args){
    bool quit = false;
    //Event handler
    SDL_Event e;
    while(!quit) {
        while(SDL_PollEvent(&e) != 0){
            //User requests quit
            if( e.type == SDL_QUIT ){
                quit = true;
            }
        }
//Start up SDL and create window
        if (!init()) {
            cout << "Failed to initialize!\n";
        } else {
            //Load media
            if (!loadMedia()) {
                cout << "Failed to load media!\n";
            } else {
                //Apply the image
                SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);
                //Update the surface
                SDL_UpdateWindowSurface(gWindow);
                //Wait two seconds
                SDL_Delay(2000);
            }
        }
    }
    //Free resources and close SDL
    close();
    return 0;
}
