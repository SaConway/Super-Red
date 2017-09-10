#pragma once
#include <SFML/Graphics.hpp>
#include "InanimateObject.h"

//-----------------------------------------------------------------------------

class Environment : public InanimateObject
{
public:
	Environment(const Texture & text, Vector2f & pos_by_pixel, Vector2i & size_of_pic, Vector2i & pos_in_pic)
		:InanimateObject(text, pos_by_pixel, size_of_pic, pos_in_pic) {m_sprite.setOrigin(128, 128);};
};