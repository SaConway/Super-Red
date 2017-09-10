#include "InfoManager.h"
#include "Resource.h"
//-----------------------------------------------------------------------------

/* Info manager c-tor*/

InfoManager::InfoManager(RenderWindow & window)
	: Menu(window)
{
	m_background.setTexture(Resource::getInstance().getTexture(TextureID::_T_Background));
	m_background.scale(getScaledBackgoundSize(*m_background.getTexture()));
	m_text.setFont(Resource::getInstance().getFont(FontID::_F_Font));
	m_text.setCharacterSize(45);
	m_string = "							     Super Red						\n"
		       "								      v1.0                          \n\n"
		       "		   Super Red game is pretty simple,\n\n"
			   "	 Red mission is to collect as many coins \n\n"
			   "as possible, and gain 3 stats for each level.\n\n"
		       "Be aware that red doesn't know how to Swim\n\n"
			   "		      and he is affraid of sharp things.\n\n"
		       "  Use the arrows to move, and space to jump.\n\n"
			   "			              Help red get rich!\n\n"
			   "\n\n\n			                  Programmers:\n\n"
			   "			                  Sagee Conway\n\n"
			   "			                  Idan Marciano";

	m_text.setString(m_string);
	m_text_start_pos = { WINDOW_W / 2.f - (float)(m_text.getGlobalBounds().width / 2.f),(float)VideoMode::getDesktopMode().height };
	m_text.setPosition(m_text_start_pos);
	m_time = milliseconds(30);

	// return button
	auto back_button = make_shared <Button>(Vector2f{ 10, 10 }, Vector2i{ 128, 125 }, Vector2i{ 128, 130 }, [this] {});
	back_button->setScale({ 0.8f, 0.75f });
	m_buttons.emplace_back(back_button);
}

//-----------------------------------------------------------------------------

/* This function run info screen */

void InfoManager::runInfo()
{
	m_text.setPosition(m_text_start_pos);
	m_clock.restart();

	while (true) 
	{
		m_window.clear();

		//check exit event
		if (eventHandler()) break;

		updateObjectState();
		displayInfo();
	}
}

//-----------------------------------------------------------------------------

/* This function display info screen */

void InfoManager::displayInfo()
{
	m_window.draw(m_background);
	m_window.draw(m_text);
	for (auto i : m_buttons) i->draw(m_window);
	m_window.display();
}

//-----------------------------------------------------------------------------

/* This function handel info screen event */

bool InfoManager::eventHandler()
{
	Event event;
	m_window.pollEvent(event);

	if (event.type == Event::KeyPressed || m_text.getPosition().y < - 1200)
		return true;

	if (event.type == Event::MouseButtonPressed)
		if (m_buttons[0]->checkIfPressed((Vector2f)Mouse::getPosition()))
		{
			m_buttons[0]->handlePress();
			return true;
		}

	return false;
}

//-----------------------------------------------------------------------------

/* This function update all object in Info manager class */

void InfoManager::updateObjectState()
{
	//update text position
	if (m_clock.getElapsedTime() > m_time) 
	{
		m_text.setPosition(m_text.getPosition() + Vector2f{ 0,OFFSET });
		m_clock.restart();
	}

	mouseOnButton((Vector2f)Mouse::getPosition());
}