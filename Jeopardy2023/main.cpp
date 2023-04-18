#include "database.h"
#include "window.h"
#include "rectangle.h"
#include "texture.h"

bool init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { 
        cout << "SDL could not initialize! SDL_Error:" << SDL_GetError() << endl; 
        return false;
    }
    if (TTF_Init() == -1)
    {
        cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
        return false;
    }
    return true;
}

bool showQuestion(string question, string answer) {

}


void showRectangles(SDL_Renderer* render, int SCREEN_WIDTH, int SCREEN_HEIGHT, string categoryName[6]) {
    int iterateX = SCREEN_WIDTH / 6;
    int iterateY = SCREEN_HEIGHT / 6;
    int rectWidth = iterateX - 2;
    int rectHeight = iterateY - 3;
    int color[4]{ 7, 18, 119, 225 };

   

    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    SDL_RenderClear(render);

    for (int i = 2; i < SCREEN_WIDTH; i += iterateX) {
        for (int z = 2; z < SCREEN_HEIGHT; z += iterateY) {
            Rectangle rect(render, color, i, z, rectWidth, rectHeight);
        }
    }    

    Texture cat(render, "C:/Users/danae/Desktop/Programming/databases/Jeopardy2023/assets/Normal.ttf", true, { 255, 255, 255 }, 20, iterateX-6);
    for (int i = 0; i < 6; i ++) {
        cat.loadFromRenderedText(categoryName[i]);
        int width = cat.getWidth();
        int height = cat.getHeight();
        int x = (((rectWidth) - width) / 2) + (iterateX * i + 2);
        int y = ((2 + rectHeight) - height) / 2;
        cat.render(x , y);
    }

    Texture dollar(render, "C:/Users/danae/Desktop/Programming/databases/Jeopardy2023/assets/Bold.ttf", true, { 211, 157, 74 }, 48, iterateX);
    string dollarText[5] = {"$200", "$400", "$600", "$800", "$1000"};
    for (int i = 0; i < 6; i ++) {
        for (int z = 0; z < 5; z++) {
            dollar.loadFromRenderedText(dollarText[z]);
            int width = cat.getWidth();
            int height = cat.getHeight();
            int x = ((rectWidth) - width) / 2 + (iterateX * i + 2);
            int y = ((z+1) * iterateY + 2) + (((rectHeight) - height) / 2);
            dollar.render(x, y);
        }
    }
   
    SDL_RenderPresent(render);
}

    

int main(int argc, char* args[]) {
    init();

    Database data; 
    int scores[3] = { 0, 0, 0 };
    bool clickRect[6][5];

    // Start Window
    Window wdw("Test");
    SDL_Renderer* render = wdw.getRenderer();

    //Load Jeapordy Screen
    //Texture tx(render, "../assets/LoadingScreen.png");
    //tx.render();
    int SCREEN_WIDTH = wdw.getWidth();
    int SCREEN_HEIGHT = wdw.getHeight();
    showRectangles(render, SCREEN_WIDTH, SCREEN_HEIGHT, data.categoryName);
    
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) { quit = true; }
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            int iterateX = SCREEN_WIDTH / 6;
            int iterateY = SCREEN_HEIGHT / 6;
            SDL_GetMouseState(&x, &y);
            int xr = SCREEN_WIDTH % x;
            int h = (x - xr) / (iterateX);
            int yr = SCREEN_HEIGHT % y;
            int v = ((y - yr) / (iterateY)) - 1;
            if (xr <= iterateX && yr <= iterateY) {
                clickRect[h][v] = true;
                tuple<string, string> info = data.getQuestion(h, v);
                showRectangles(render, SCREEN_WIDTH, SCREEN_HEIGHT, data.categoryName);
            }

        }
    }
	return 0;
};

// 1-3 players. 
// side screen shows player1,2,3 and their points. 
// two winning screens at end based on single vs multiplayer