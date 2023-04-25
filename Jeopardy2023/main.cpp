#include "database.h"
#include "window.h"
#include "rectangle.h"
#include "texture.h"

bool CLICKRECT[6][5];

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
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            CLICKRECT[i][j] = false;
        }
    }
    return true;
}

bool showQuestion(string question, string answer) {
    return true;
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
            if (CLICKRECT[i][z] == false) { dollar.loadFromRenderedText(dollarText[z]); }
            else { dollar.loadFromRenderedText(" "); }
            int width = cat.getWidth();
            int height = cat.getHeight();
            int x = ((rectWidth) - width) / 2 + (iterateX * i + 2);
            int y = ((z+1) * iterateY + 2) + (((rectHeight) - height) / 2);
            dollar.render(x, y);
        }
    }
   
    SDL_RenderPresent(render);
}

bool showQuestion(string question, string answer) {
    // render question in big letters for 1/2 of screen
    // timer in top right corner counting down from 30 seconds
    // render button that says "Show Answer"
    // if timer = 0 OR button pressed DISPLAY ANSWER in place of button
    // new button appears with a check or X 
    // if check button pressed, return true
    // if x button pressed, return false
}
    

int main(int argc, char* args[]) {
    init();

    Database data; 
    int scores[3] = { 0, 0, 0 };

    // Start Window
    Window wdw("Test");
    SDL_Renderer* render = wdw.getRenderer();

    //Load Jeapordy Screen
    //Texture tx(render, "../assets/LoadingScreen.png");
    //tx.render();
    int SCREEN_WIDTH = wdw.getWidth();
    int SCREEN_HEIGHT = wdw.getHeight();
    showRectangles(render, SCREEN_WIDTH, SCREEN_HEIGHT, data.categoryName);
    int difficulties[5] = { 1, 3, 5, 7, 9 };
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) { quit = true; }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                int iterateX = SCREEN_WIDTH / 6;
                int iterateY = SCREEN_HEIGHT / 6;
                SDL_GetMouseState(&x, &y);
                int h = x / iterateX;
                int v = y / iterateY - 1;
                if (v >= 0 and CLICKRECT[h][v] == false) {
                    // keep track of times clicked. when it reaches 30, ENDGAME (new func?)
                    CLICKRECT[h][v] = true;
                    int category = data.categoryID[h];
                    int difficulty = difficulties[v];
                    tuple<string, string> info = data.getQuestion(category, difficulty);

                    /* 
                    bool correct = showQuestion(get<0>(info), get<1>(info))
                    if (correct) {
                        // award points to player
                    }
                    */
                    showRectangles(render, SCREEN_WIDTH, SCREEN_HEIGHT, data.categoryName);
                    
                }
            }
        }
    }
	return 0;
};

// 1-3 players. 
// side screen shows player1,2,3 and their points. 
// two winning screens at end based on single vs multiplayer