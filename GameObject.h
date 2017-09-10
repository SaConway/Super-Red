#pragma once
#include <SFML/Graphics.hpp>
#include "WorldObject.h"
#include "Resource.h"
//-----------------------------------------------------------------------------

using namespace sf;
using namespace std;

//-----------------------------------------------------------------------------

class GameObject : public WorldObject
{
public:
	GameObject(const Texture &, Vector2f &, Vector2i &, Vector2i &);
	virtual void draw(RenderWindow & window) const = 0;
	virtual ~GameObject() {};
	
protected:
	Sprite m_sprite;
};