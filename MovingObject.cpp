#include "MovingObject.h"


//-----------------------------------------------------------------------------

/* C-tor of MovingObject */

MovingObject::MovingObject(const Texture & text, Vector2f & pos_by_pixel, Vector2i & size_of_pic, Vector2i & pos_in_pic)
	:AnimatedObject(text, pos_by_pixel, size_of_pic, pos_in_pic), m_start_pos(pos_by_pixel){}

//-----------------------------------------------------------------------------

/* This function set position of moving object to the start postion */

void MovingObject::setStartPos()
{
	m_sprite.setPosition(m_start_pos);
	m_body->SetTransform({ (float32)m_start_pos.x / RATIO, (float32)m_start_pos.y / RATIO }, 0);
}