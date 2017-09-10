#pragma once
#include "InanimateObject.h"
#include <SFML/Graphics.hpp>

//-----------------------------------------------------------------------------

class Ground : public InanimateObject
{
public:
	Ground(Vector2f & pos_by_pixel, Vector2i & size_of_pic, Vector2i & pos_in_pic)
		:InanimateObject(Resource::getInstance().getTexture(TextureID::_T_Ground), pos_by_pixel, size_of_pic, pos_in_pic) {}
};