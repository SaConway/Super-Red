#include "GameObject.h"

//-----------------------------------------------------------------------------

/* c-tor of GameObject */

GameObject::GameObject(const Texture & text, Vector2f & pos_by_pixel, Vector2i & size_of_pic, Vector2i & pos_in_pic)
{
	m_sprite.setOrigin(float(size_of_pic.x / 2.f), float(size_of_pic.y / 2.f));
	m_sprite.setTexture(text);
	m_sprite.setTextureRect({ pos_in_pic.x, pos_in_pic.y, size_of_pic.x, size_of_pic.y });
	m_sprite.setPosition(pos_by_pixel);
}