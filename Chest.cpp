#include "Chest.h"

//-----------------------------------------------------------------------------

/* C-tor of Chest */

Chest::Chest(Vector2f & pos_by_pixel, Vector2i & size_of_pic, Vector2i & pos_in_pic, unique_ptr <b2World> & world)
	:NotMovingObject(Resource::getInstance().getTexture(TextureID::_T_Chest), pos_by_pixel, size_of_pic, pos_in_pic, world)
{
	m_sprite.setOrigin(32, 128);
	m_speed = milliseconds(SPEED_CHEST);

	//set collition group
	b2Filter filter;
	filter.categoryBits = Collition_Group::COIN;
	filter.maskBits = Collition_Group::ENEMY | Collition_Group::RED;

	m_body->GetFixtureList()->SetFilterData(filter);
	m_body->SetUserData(this);
}

//-----------------------------------------------------------------------------

/* This function animate chest object */

void Chest::animate()
{
	if (m_clock.getElapsedTime() > m_speed)
	{
		Vector2i size(m_sprite.getTextureRect().width, m_sprite.getTextureRect().height);

		m_clock.restart();

		m_current_pic = (m_current_pic + 1) % NUM_OF_CHEST_PIC;
		m_pos_in_pic.x = m_current_pic * size.x;
		m_sprite.setTextureRect({ m_pos_in_pic, size });
	}
}