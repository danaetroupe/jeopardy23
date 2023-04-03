#include "Database.h"
#include "Window.h"

bool init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { 
        cout << "SDL could not initialize! SDL_Error:" << SDL_GetError() << endl; 
        return false;
    }
    return true;
}
    
int main(int argc, char* args[]) {
    if (init) {
        // Start Window
        Window wdw("Test");
        SDL_Renderer* render = wdw.getRenderer();

        //Load Jeapordy Screen
        Texture tx(render, "../assets/LoadingScreen.png");
        tx.render();
    };

    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) { quit = true; }
        }
    }
	return 0;
};

// 1-3 players. 
// side screen shows player1,2,3 and their points. 
// two winning screens at end based on single vs multiplayer