#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

//-----------------------------------------------------------------------------

class InanimateObject : public GameObject
{
public:
	InanimateObject(const Texture & text, Vector2f & pos_by_pixel, Vector2i & size_of_pic, Vector2i & pos_in_pic)
		:GameObject(text, pos_by_pixel, size_of_pic, pos_in_pic) {};
	virtual void draw(RenderWindow & window) const { window.draw(m_sprite); }
	virtual ~InanimateObject() {};
};