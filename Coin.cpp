#include "Coin.h"
//-----------------------------------------------------------------------------

//static variable for all coin class

Sound Coin::m_coin_sound(Resource::getInstance().getSound(SoundID::_S_Coin));

//-----------------------------------------------------------------------------

/* C-tor of Coin */

Coin::Coin(Vector2f & pos_by_pixel, Vector2i & size_of_pic, Vector2i & pos_in_pic, unique_ptr <b2World> & world)
	:NotMovingObject(Resource::getInstance().getTexture(TextureID::_T_Coin), pos_by_pixel, size_of_pic, pos_in_pic, world)
{
	m_speed = milliseconds(SPEED_COIN);

	//correct offset
	m_sprite.setPosition({ pos_by_pixel + Vector2f{ -90, -80 } });
	m_body->SetTransform({ (pos_by_pixel.x - 90.f) / RATIO , (pos_by_pixel.y - 80.f) / RATIO }, 0);

	//set collition group
	b2Filter filter;
	filter.categoryBits = Collition_Group::COIN;
	filter.maskBits = Collition_Group::RED;
	m_body->GetFixtureList()->SetFilterData(filter);

	//update data
	m_body->SetUserData(this);
}

//-----------------------------------------------------------------------------

/* This function animate coin object */

void Coin::animate()
{
	if (m_clock.getElapsedTime() > m_speed) 
	{
		m_clock.restart();
		m_current_pic = (m_current_pic + 1 ) % NUM_OF_COIN_PIC;
		m_pos_in_pic.x = (m_current_pic * m_sprite.getTextureRect().width);
		Vector2i size = { m_sprite.getTextureRect().width, m_sprite.getTextureRect().height };
		m_sprite.setTextureRect({ m_pos_in_pic, size });
	}
}