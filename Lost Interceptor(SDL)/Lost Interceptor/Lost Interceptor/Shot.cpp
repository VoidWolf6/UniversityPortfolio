#include "Shot.h"
#include <cassert>

void Shot::init(int x, int y, double xVel, double yVel, int lifetime)
{
    state.live.s_x = x; 
    state.live.s_y = y;
    state.live.s_xVel = xVel;
    state.live.s_yVel = yVel;
    framesLeft = lifetime;
    
}

bool Shot::move()
{
    if (!Active()) return false;

    framesLeft--;
    state.live.s_x += state.live.s_xVel;
    state.live.s_y += state.live.s_yVel;

    return framesLeft == 0;
}

ShotPool::ShotPool()
{
    prime = &s_shots[0];

    for (int i = 0; i < POOL_SIZE - 1; i++)
    {
        s_shots[i].setNext(&s_shots[i + 1]);
    }

    // The last one terminates the list.
    s_shots[POOL_SIZE - 1].setNext(NULL);
}

void ShotPool::create(int x, int y, double xVel, double yVel, int lifetime)
{
    assert(prime != NULL);

    Shot* newShot = prime;
    prime = newShot->getNext();

  
}

