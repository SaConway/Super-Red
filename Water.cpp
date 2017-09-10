#include "Water.h"

//-----------------------------------------------------------------------------

/* C-tor of Water */

Water::Water(Vector2f & pos_by_pixel, Vector2i & size_of_pic, Vector2i & pos_in_pic, unique_ptr <b2World> & world)
	:NotMovingObject(Resource::getInstance().getTexture(TextureID::_T_Water), pos_by_pixel, size_of_pic, pos_in_pic, world)
{
	m_speed = milliseconds(SPEED_WATER);
	m_body->SetUserData(this);

	//Set collition group
	b2Filter filter;
	filter.categoryBits = Collition_Group::GROUND;
	filter.maskBits = Collition_Group::RED | Collition_Group::ENEMY;
	m_body->GetFixtureList()->SetFilterData(filter);
}

//-----------------------------------------------------------------------------

/* This function animate the Water */

void Water::animate()
{
	if (m_clock.getElapsedTime() > m_speed) 
	{
		m_clock.restart();
		m_current_pic = (m_current_pic + 1) % NUM_OF_WATER_PIC;
		m_pos_in_pic.x = (m_current_pic * m_sprite.getTextureRect().width);
		Vector2i size = { m_sprite.getTextureRect().width, m_sprite.getTextureRect().height };
		m_sprite.setTextureRect({ m_pos_in_pic, size });
	}
}