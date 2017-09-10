#include "LevelIcon.h"
#include "Resource.h"

//-----------------------------------------------------------------------------

/* C-tor of Level Icon */

LevelIcon::LevelIcon(int level, float h)
{
	// level definition

	m_levelSign.first.setTexture(Resource::getInstance().getTexture(TextureID::_T_Sign));
	m_levelSign.first.setTextureRect({ 0, 0, 129, 53 });
	m_levelSign.first.setPosition(200.f + 250.f * level, (float)VideoMode::getDesktopMode().height - (h * 250.f));

	m_levelSign.second.setCharacterSize(30);
	m_levelSign.second.setFont(Resource::getInstance().getFont(FontID::_F_Font));
	m_levelSign.second.setFillColor(Color(255, 255, 255, 255));
	m_levelSign.second.setPosition({ m_levelSign.first.getPosition().x + 20.f, m_levelSign.first.getPosition().y + 10.f });
	m_levelSign.second.setString("LEVEL " + to_string(level + 1));

	// door definition

	Vector2f pos_by_pixel = { m_levelSign.first.getPosition().x,  m_levelSign.first.getPosition().y + 50.f };
	Vector2i pos_in_pic = { 0, 0 };
	Vector2i size_of_pic = { 128, 119 };
	m_door = make_shared <Button>(Resource::getInstance().getTexture(TextureID::_T_Door),pos_by_pixel, size_of_pic, pos_in_pic, [this] {});

	// tape definition

	m_tape.setTexture(Resource::getInstance().getTexture(TextureID::_T_Tape));
	m_tape.setTextureRect({ 0, 0, 118, 71 });
	m_tape.setPosition({ m_door->getPosition().x + 5.f, m_door->getPosition().y + 60.f });

	// at the begining, level 1 is accessible
	if (level == 0) m_levelAccess = true;

	// stars definition

	for (int i = 0; i < m_stars.size(); ++i)
	{
		m_stars[i].setTexture(Resource::getInstance().getTexture(TextureID::_T_Star));
		m_stars[i].setTextureRect({ 0, 0, 35, 35 });
		m_stars[i].setPosition({ m_levelSign.first.getPosition().x + i * 40.f + 5.f, m_levelSign.first.getPosition().y - 40.f });
		m_stars[i].setColor(Color(220, 220, 220, 150));
	}
}

//-----------------------------------------------------------------------------

/* This function draw all staf of Level Icon */

void LevelIcon::draw(RenderWindow & window) const
{
	window.draw(m_levelSign.first);
	window.draw(m_levelSign.second);
	m_door->draw(window);

	if (!m_levelAccess) window.draw(m_tape);

	for (int i = 0; i < m_stars.size(); ++i) window.draw(m_stars[i]);
}

//-----------------------------------------------------------------------------

/* This function update the stars status, i.e. their color */

void LevelIcon::updateStars(int stars)
{
	for (int i = m_numOfStars; i < stars; ++i)
		m_stars[i].setColor(Color(255, 255, 255, 255));
}