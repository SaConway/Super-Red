#include "Cloud.h"
#include "Resource.h"
//-----------------------------------------------------------------------------

/* C-tor of Cloud */

Cloud::Cloud()
{
	m_sprite.setTexture(Resource::getInstance().getTexture(TextureID::_T_Clouds));

	//set random cloud picture position and speed of cloud
	m_sprite.setTextureRect({ (rand() % 1) * 256 , 0 , m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height});
	m_sprite.setPosition(Vector2f{ (float)(rand() % VideoMode().getDesktopMode().width), (float)(rand() % (int)(VideoMode().getDesktopMode().height / 2.3)) });
	m_speed = milliseconds(rand() % 10);

	m_sprite.setColor(Color(255, 255, 255, 200));
	m_clock.restart();
}

//-----------------------------------------------------------------------------

/* This function move the cloud */

void Cloud::move()
{ 
	if (m_clock.getElapsedTime() > m_speed) 
	{
		m_clock.restart();
		m_sprite.setPosition((float)m_sprite.getPosition().x + 1  ,m_sprite.getPosition().y);

		if (m_sprite.getPosition().x > VideoMode().getDesktopMode().width)
			m_sprite.setPosition({(float) - m_sprite.getTextureRect().width,m_sprite.getPosition().y });
	}
}

