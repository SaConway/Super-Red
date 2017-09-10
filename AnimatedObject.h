#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include "Box2D\Box2D.h"

//-----------------------------------------------------------------------------

class AnimatedObject :public GameObject
{
public:
	AnimatedObject(const Texture & text, Vector2f & pos_by_pixel, Vector2i & size_of_pic, Vector2i & pos_in_pic)
		:GameObject(text, pos_by_pixel, size_of_pic, pos_in_pic) , m_start_pos_in_pic(pos_in_pic) {};
	virtual void draw(RenderWindow &) const = 0;
	virtual ~AnimatedObject() {};
	virtual void animate() = 0;
	void resetAnimate() { m_pos_in_pic = m_start_pos_in_pic; m_current_pic = 0; }

protected:
	Clock m_clock;
	Time m_speed;
	Vector2i m_pos_in_pic;
	int m_current_pic = 0 ;

private:
	const Vector2i m_start_pos_in_pic;
};