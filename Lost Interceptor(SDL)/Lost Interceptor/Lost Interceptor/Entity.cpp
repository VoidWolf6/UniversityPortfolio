#include "Entity.h"

Entity::Entity(int x, int y, const std::string& filename, SDL_Renderer* renderer)
{
	m_Xpos = x;
	m_Ypos = y;
	e_bitmap = new Bitmap(renderer, filename.c_str());
	e_collider = new SDL_Rect{ m_Xpos, m_Ypos, e_bitmap->getWidth(), e_bitmap->getHeight() };
}

Entity::~Entity()
{
}
//uses bitmaps, as double buffer doesn't work.
void Entity::Draw()
{
	e_bitmap->Draw(m_Xpos, m_Ypos);
}

void Entity::Destroy()
{
}

void Entity::SetXpos(float x)
{
	m_Xpos = x;
	e_collider->x = x;
}

void Entity::SetYpos(float y)
{
	m_Ypos = y;
	e_collider->y = y;
}

void Entity::IncXpos(float amount)
{
	m_Xpos += amount;
	e_collider->x += amount;
}

void Entity::IncYpos(float amount)
{
	m_Ypos += amount;
	e_collider->y += amount;
}

int Entity::GetXpos()
{
	return m_Xpos;
}

int Entity::GetYpos()
{
	return m_Ypos;
}

SDL_Rect* Entity::ReturnCollider()
{
	return e_collider;
}

//much simpler than first thought! takes in two rectangles, the colliders, and sees if they intersect
bool Entity::CheckEntityCollision(SDL_Rect* a, SDL_Rect* b)
{
	return SDL_HasIntersection(a, b);
}
