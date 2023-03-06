#pragma once
#include <SDL.h>
#include <iostream>
#include <conio.h>

using namespace std;

class Buffer
{
public:
    Buffer() { clear(); }
    void clear();
    void create();
    void draw();
    void destroy();
    const char* getPixels()
    {
        return pixels_;
    }
    SDL_Renderer* GetRenderer() { return m_renderer; }
    int GetOffset() { return Y_offset; }

private:
    static const int WIDTH = 1024;
    static const int HEIGHT = 1024;
    int Y_offset = 0;
    int background_start = 56;
    
    SDL_Window* m_window{ nullptr };
    SDL_Renderer* m_renderer{ nullptr };
    SDL_Surface* m_backdrop{ nullptr };
    SDL_Texture* m_texture{ nullptr };

    SDL_Rect view_1 = { 448, (Y_offset + background_start), 1024, 1024 };   
    SDL_Rect view_2 = { 448, ((Y_offset - 1024) + background_start), 1024, 1024 };

    char pixels_[WIDTH * HEIGHT];
};

