#include "SDL.h"
#include <iostream>
#include <math.h>   
#include <fstream>   
#include <iostream>   

using namespace std;
// Graphics
const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 720;
SDL_Window* g_main_window;
SDL_Renderer* g_main_renderer;

int SQUARE_HEIGHT = 32;
int SQUARE_WIDTH = 32;
int pos_x = 200;    
int pos_y = 200;  

int Hexagon_x = 200;
int Hexagon_y = 400;

int Circle_x = 800;
int Circle_y = 600;

int DEFAULT_STEP = 2;
int step = DEFAULT_STEP;
//////
int r = 5;
float angle = 10;

bool ToDown; 
bool ToRight;

bool ToTopCircle = true; 
bool ToOneSideRight;
bool ToDownCircle;
bool ToOneSideLeft;
///

// Colors
namespace Colors {
    const SDL_Color GREEN = { 0, 255, 0, SDL_ALPHA_OPAQUE };
    const SDL_Color BLACK = { 0, 0, 0, SDL_ALPHA_OPAQUE };
}

static void ClearScreen(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, Colors::BLACK.r, Colors::BLACK.g, Colors::BLACK.b, Colors::BLACK.a);
    SDL_RenderClear(renderer);
}

static bool Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL_Init failed with error: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    g_main_window = SDL_CreateWindow(
        "Timba Test",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL
    );

    if (g_main_window == nullptr) {
        std::cout << "Unable to crete the main window. Erro: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return EXIT_FAILURE;
    }

    g_main_renderer = SDL_CreateRenderer(g_main_window, -1, SDL_RENDERER_PRESENTVSYNC);

    return true;
}

void Shutdown()
{
    if (g_main_window != nullptr) {
        SDL_DestroyWindow(g_main_window);
        g_main_window = nullptr;
    }

    if (g_main_renderer != nullptr) {
        SDL_DestroyRenderer(g_main_renderer);
        g_main_renderer = nullptr;
    }

    SDL_Quit();
}

void DrawSquare(int x, int y) {
    SDL_Rect rect;
    rect.x = x - (SQUARE_WIDTH / 2);
    rect.y = y - (SQUARE_HEIGHT / 2);
    rect.w = SQUARE_WIDTH;
    rect.h = SQUARE_HEIGHT;

    SDL_SetRenderDrawColor(g_main_renderer, Colors::GREEN.r, Colors::GREEN.g, Colors::GREEN.b, Colors::GREEN.a);
    SDL_RenderFillRect(g_main_renderer, &rect);
}

void DrawTriangle(SDL_Renderer* Renderer, int _X, int _Y) {

    int Ax, Bx, Cx;
    int Ay, By, Cy;
    


    SDL_Point vertices[] = {
     {_X + 20, _Y},
     {_X,      _Y + 40},
     {_X + 40, _Y + 40},
     {_X + 20, _Y}
    };

   
  /*_X = (Ax + Bx + Cx) / 3;
    _Y = (Ay + By + Cy) / 3;*/


    SDL_RenderDrawLines(Renderer, vertices, 4);
    //Update the Renderer.
    SDL_RenderPresent(Renderer);
}

void DrawHexagon(SDL_Renderer* Renderer, int _X, int _Y) {

    //CircleRotation(_X, _Y);

    SDL_Point vertices[] = {
     {_X + 20, _Y},
     {_X     , _Y + 40},
     {_X + 20, _Y + 80},
     {_X + 60, _Y + 80},
     {_X + 80, _Y + 40},
     {_X + 60, _Y},
     {_X + 20, _Y}
    };

    SDL_RenderDrawLines(Renderer, vertices, 7);

    //Update the Renderer.
    SDL_RenderPresent(Renderer);
}

int DrawCircle(SDL_Renderer* renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;
    ////Set the draw color...
    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    ////Clear the screen.
    //SDL_RenderClear(renderer);

    //Setting the actual draw color.
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    while (offsety >= offsetx) {
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

void CheckEdgeH(int pos)
{
    if (pos == 10)
    {
        ToDown = true;
    }
    else if (pos == WINDOW_HEIGHT - 10)
    {
        ToDown = false;
    }
}
void CheckEdgeW(int pos)
{
    if (pos == 10)
    {
        ToRight = true;
    }
    else if (pos == WINDOW_WIDTH - 10)
    {
        ToRight = false;
    }

    
}

void CheckSquareMovement(int posX, int posY)
{
    if (posY == 400)
    {
        ToTopCircle = false;
        ToOneSideRight = true;
    }
    else if (posX == 1000)
    {
        ToOneSideRight = false;
        ToDownCircle = true;
    }
    else if (posY == WINDOW_HEIGHT - 150)
    {
        ToDownCircle = false;
        ToOneSideLeft = true;
    }
    else if (posX == 800)
    {
        ToOneSideLeft = false;
        ToTopCircle = true;
    }
}


int main(int argc, char* argv[])
{
    if (Init() == false) { Shutdown(); }

    // Draw loop
    SDL_Event event;
    bool running = true;

    while (running)
    {
        ClearScreen(g_main_renderer);
        

        //Square Movement
        CheckEdgeW(pos_x);
        if (ToRight)
        {
            pos_x += 10;
        }
        if (!ToRight)
        {
            pos_x -= 10;
        }
        //Triangle Movement
        CheckEdgeH(pos_y);
        if (ToDown)
        {
            pos_y += 10;
        }
        if (!ToDown)
        {
            pos_y -= 10;
        }
        //Hexagon Movement
        Hexagon_x -= r * cos(angle);
        Hexagon_y += r * sin(angle);
        angle -= 0.05;
        //Circle Movement
        CheckSquareMovement(Circle_x, Circle_y);
        if (ToTopCircle)
        {
            Circle_y -= 10;
        }
        else if (ToDownCircle)
        {
            Circle_y += 10;
        }
        else if (ToOneSideRight)
        {
            Circle_x += 10;
        }
        else if (ToOneSideLeft)
        {
            Circle_x -= 10;
        }

        DrawSquare(pos_x, 200);
        DrawTriangle(g_main_renderer, 500, pos_y);
        DrawHexagon(g_main_renderer, Hexagon_x, Hexagon_y);
        DrawCircle(g_main_renderer, Circle_x, Circle_y, 30);

        SDL_RenderPresent(g_main_renderer);
    }

    

    Shutdown();
    return EXIT_SUCCESS;
}