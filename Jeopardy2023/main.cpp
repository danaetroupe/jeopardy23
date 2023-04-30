#include "database.h"
#include "window.h"
#include "rectangle.h"
#include "texture.h"
#include "text.h"
#include "timer.h"

bool _CLICKRECT[6][5];
int _PLAYERS = 1;
const string _NORMAL = "C:/Users/danae/Desktop/Programming/databases/Jeopardy2023/assets/Normal.ttf";
const string _BOLD = "C:/Users/danae/Desktop/Programming/databases/Jeopardy2023/assets/Bold.ttf";
//Text Colors
SDL_Color yellow{ 211, 157, 74 };
SDL_Color white{ 255, 255, 255 };
//Rect Colors
int green[4]{ 1, 167, 79, 0 };
int red[4]{ 242, 1, 3, 0 };
int blue[4]{ 7, 18, 119, 225 };

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
            _CLICKRECT[i][j] = false;
        }
    }
    return true;
}

bool showLoadingScreen(SDL_Renderer* render, int width, int height) {
    Texture tx(render, "../assets/LoadingScreen.png");
    tx.render(0, 0);
    // Render player selection Text
    return true;
}

void showRectangles(SDL_Renderer* render, int SCREEN_WIDTH, int SCREEN_HEIGHT, string categoryName[6]) {
    // Set inital values
    int iterateX = SCREEN_WIDTH / 6;
    int iterateY = SCREEN_HEIGHT / 6;
    int rectWidth = iterateX - 2;
    int rectHeight = iterateY - 3;
    
    // Clear Window
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    SDL_RenderClear(render);
    // Render Rectangles
    for (int i = 2; i < SCREEN_WIDTH; i += iterateX) {
        for (int z = 2; z < SCREEN_HEIGHT; z += iterateY) {
            Rectangle rect(render, blue, i, z, rectWidth, rectHeight);
        }
    }  
    // Render Category Names
    Text cat(render, _NORMAL, white, 20, iterateX-6);
    for (int i = 0; i < 6; i ++) {
        cat.loadFromRenderedText(categoryName[i]);
        int width = cat.getWidth();
        int height = cat.getHeight();
        int x = (((rectWidth) - width) / 2) + (iterateX * i + 2);
        int y = ((2 + rectHeight) - height) / 2;
        cat.render(x , y);
    }
    // Render Dollar Texts
    Text dollar(render, _BOLD, yellow, 48, iterateX);
    string dollarText[5] = {"$200", "$400", "$600", "$800", "$1000"};
    for (int i = 0; i < 6; i ++) {
        for (int z = 0; z < 5; z++) {
            if (_CLICKRECT[i][z] == false) { dollar.loadFromRenderedText(dollarText[z]); }
            else { dollar.loadFromRenderedText(" "); }
            int width = dollar.getWidth();
            int height = dollar.getHeight();
            int x = ((rectWidth) - width) / 2 + (iterateX * i + 2);
            int y = ((z+1) * iterateY + 2) + (((rectHeight) - height) / 2);
            dollar.render(x, y, width, height);
        }
    }
    // Render Screen
    SDL_RenderPresent(render);
}

void showTime(Uint32 time, SDL_Renderer* render, const int SCREEN_WIDTH, const int SCREEN_HEIGHT) {
    Text timeDisplay(render, _NORMAL, yellow, 40, 0);
    string stime = to_string(time);
    timeDisplay.loadFromRenderedText(stime);
    int width = timeDisplay.getWidth();
    int height = timeDisplay.getHeight();
    timeDisplay.render(SCREEN_WIDTH - width - 10, 10, width, height);
    SDL_RenderPresent(render);
}

bool showAnswer(string answer, SDL_Renderer* render, const int SCREEN_WIDTH, const int SCREEN_HEIGHT) {
    cout << "showanser" << endl;
    SDL_RenderClear(render);
    Text answerDisplay(render, _NORMAL, yellow, 64, SCREEN_WIDTH - 50);
    answerDisplay.loadFromRenderedText(answer);
    answerDisplay.render((SCREEN_WIDTH - answerDisplay.getWidth()) / 2, 100, answerDisplay.getWidth(), answerDisplay.getHeight());
    SDL_RenderPresent(render);

    Timer tempTime(3);
    tempTime.start();
    while (tempTime.getTime() != 0) {
        continue;
    }
    tempTime.stop();

    Text click(render, _NORMAL, white, 48, SCREEN_WIDTH - 50);
    click.loadFromRenderedText("Did you answer correctly?");
    int clickWidth = click.getWidth();
    int clickHeight = click.getHeight();
    int x = (SCREEN_WIDTH - clickWidth) / 2;
    click.render(x, answerDisplay.getHeight() + 200, clickWidth, clickHeight);

    int yesX = SCREEN_WIDTH / 5;
    int noX = 3 * SCREEN_WIDTH / 5;
    int yesY = SCREEN_HEIGHT - 150;
    int width = SCREEN_WIDTH / 5;
    int height = 100;
    Rectangle yesRect(render, green, yesX, yesY, width, height);
    Rectangle noRect(render, red, noX, yesY, width, height);
    Text select(render, _NORMAL, white, 80, width);
    select.loadFromRenderedText("YES");

    select.render(yesX, yesY);
    select.loadFromRenderedText("NO");
    select.render(noX, yesY);
    SDL_RenderPresent(render);

    SDL_Event e;
    while (true) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (x >= yesX && x <= yesX + width && y >= yesY && y <= yesY + height) {
                    return true;
                }
                else if (x >= noX && x <= noX + width && y >= yesY && y <= yesY + height) {
                    return false;
                }
            }
        }
    }
}

bool showQuestion(string question, string answer, SDL_Renderer* render, const int SCREEN_WIDTH, const int SCREEN_HEIGHT) {
    SDL_RenderClear(render);
    // render question in big letters for 1/2 of screen
    Text questionText(render, _BOLD, { 211, 157, 74 }, 64, SCREEN_WIDTH - 50);
    questionText.loadFromRenderedText(question);
    questionText.render(25, 50, SCREEN_WIDTH, questionText.getHeight());

    Timer timer(30);
    int currentTime = 0;
    timer.start();
    Uint32 time = timer.getTime();
    bool clicked = false;
    SDL_Event e;
    while ((time != 0) && (clicked == false)) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_KEYDOWN) {
               if (e.key.keysym.sym == SDLK_SPACE) {
                   clicked = true;
                   timer.stop();
                   Text click(render, _NORMAL, { 255, 255, 255 }, 48, SCREEN_WIDTH - 50);
                   click.loadFromRenderedText("Click to reveal answer...");
                   int clickWidth = click.getWidth();
                   int clickHeight = click.getHeight();
                   int x = (SCREEN_WIDTH - clickWidth) / 2;
                   click.render(x, questionText.getHeight() + 100, clickWidth, clickHeight);
                   SDL_RenderPresent(render);
                }
            }
        }
        Uint32 newTime = timer.getTime();
        if (currentTime != newTime && clicked == false) {
            SDL_RenderClear(render);
            currentTime = newTime;
            questionText.render(25, 50, SCREEN_WIDTH, questionText.getHeight());
            showTime(currentTime, render, SCREEN_WIDTH, SCREEN_HEIGHT);
        }
    }
    
    while (true) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                bool correct = showAnswer(answer, render, SCREEN_WIDTH, SCREEN_HEIGHT);
                return correct;
            }
        }
    }
    // timer in top right corner counting down from 30 seconds
    // render Text that says "Show Answer"
    // if timer = 0 OR Text pressed DISPLAY ANSWER in place of Text
    // new Text appears with a check or X 
    // if check Text pressed, return true
    // if x Text pressed, return false
}

int main(int argc, char* args[]) {
    // Initalize SDL and initial values
    init();
    Database data; 
    int scores[2]{ 0, 0 };
    int difficulties[5] = { 1, 3, 5, 7, 9 };
    int points[5] = { 200, 400, 600, 800, 1000 };
    bool quit = false;
    // Start Window
    Window wdw("Play Jeopardy");
    int SCREEN_WIDTH = wdw.getWidth();
    int SCREEN_HEIGHT = wdw.getHeight();
    SDL_Renderer* render = wdw.getRenderer();
    /* 
    // Render loading screen
    showLoadingScreen(render, SCREEN_WIDTH, SCREEN_HEIGHT);
     */
    // Render Inital Rectangles
    showRectangles(render, SCREEN_WIDTH, SCREEN_HEIGHT, data.categoryName);
    // Set Up Event Handling
    SDL_Event e;
    while (!quit) {        while (SDL_PollEvent(&e) != 0) {
            // EXIT PROGRAM
            if (e.type == SDL_QUIT) { 
                quit = true; 
            }
            // CLICK HANDLING
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                // Identify x, y coordinates of click
                int x, y;
                int iterateX = SCREEN_WIDTH / 6;
                int iterateY = SCREEN_HEIGHT / 6;
                SDL_GetMouseState(&x, &y);
                // Identify section of screen that was clicked
                int h = x / iterateX;
                int v = y / iterateY - 1;
                // Show Question if Text is clicked
                if (v >= 0 and _CLICKRECT[h][v] == false) {
                    // keep track of times clicked. when it reaches 30, ENDGAME (new func?)
                    _CLICKRECT[h][v] = true;
                    int category = data.categoryID[h];
                    int difficulty = difficulties[v];
                    tuple<string, string> info = data.getQuestion(category, difficulty);

                    bool correct = showQuestion(get<0>(info), get<1>(info),render, SCREEN_WIDTH,SCREEN_HEIGHT);
                    if (correct) {
                        scores[0] += points[v];
                    }
                    cout << "points: " << scores[0] << endl;
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