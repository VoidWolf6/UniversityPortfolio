#pragma once
#include <SDL.h>
#include "Bitmap.h"

class Shot
{
public:
    Shot() : framesLeft(0) {}

    friend class ShotPool;

    void init(int x, int y, double xVel, double yVel, int lifetime);   
    bool move();
    bool Active() const { return framesLeft > 0; }
    Shot* getNext() const { return state.next; }
    void setNext(Shot* next) { state.next = next; }

protected:
    int framesLeft;
    Bitmap* s_bitmap;
    SDL_Rect s_collider;
    union 
    {
        struct 
        {
            int s_x, s_y;
            double s_xVel, s_yVel;
            
        } live;
        Shot* next;
    } state;
    
};

class ShotPool
{
public:
    ShotPool();
    void create(int x, int y, double xVel, double yVel, int lifetime);
    void motion()
    {
        for (int i = 0; i < POOL_SIZE; i++)
        {
            if (s_shots[i].move())
            {
                s_shots[i].setNext(prime);
                prime = &s_shots[i];
            }
        }
    }
    
private:
    static const int POOL_SIZE = 50;
    Shot s_shots[POOL_SIZE];
    Shot* prime;
};
