#include "MainMenu.h"
#include "Resource.h"
//-----------------------------------------------------------------------------

// C-tor of Menu

MainMenu::MainMenu(RenderWindow & window)
	: Menu(window), m_info_manager(window)
{
	Vector2f pos_by_pixel;
	Vector2i size_of_pic, pos_in_pic;

	//fit backgorund to screen size
	m_background.setTexture(Resource::getInstance().getTexture(TextureID::_T_MenuBackground));
	m_background.scale(getScaledBackgoundSize(*m_background.getTexture()));

	//Play button definition

	pos_by_pixel = { ((float)VideoMode::getDesktopMode().width / 2) - 128, (float)VideoMode::getDesktopMode().height / 2 + 128 };
	pos_in_pic = { 1024,256 };
	size_of_pic = { BUTTONS_SIZE * 2 , BUTTONS_SIZE };

	auto play = make_shared <Button>(pos_by_pixel, size_of_pic, pos_in_pic, [this] {});
	m_buttons.emplace_back(play);

	//Exit button definition

	pos_by_pixel = { (float)VideoMode::getDesktopMode().width - 110, (float)VideoMode::getDesktopMode().height - 105 };
	pos_in_pic = { 256,256 };
	size_of_pic = { BUTTONS_SIZE, BUTTONS_SIZE };

	auto exit = make_shared <Button>(pos_by_pixel, size_of_pic, pos_in_pic, [this] { exitGame(); });
	exit->setScale({ 0.8f, 0.75f });
	m_buttons.emplace_back(exit);

	//Info button definition

	pos_by_pixel = { 10, (float)VideoMode::getDesktopMode().height - 105 };
	pos_in_pic = { 128,256 };

	auto info = make_shared <Button>(pos_by_pixel, size_of_pic, pos_in_pic, [this] { runInfo(); });
	info->setScale({ 0.8f, 0.75f });
	m_buttons.emplace_back(info);

	//Clouds definition

	for (int i = 0; i < NUM_OF_CLOUDS; i++)
		m_cloud[i] = make_unique<Cloud>();	
}

//-----------------------------------------------------------------------------

/* This function run main menu */

op_main_menu MainMenu::runMenu()
{
	op_main_menu event;

	while (true) 
	{
		displayMenu();
		mouseOnButton((Vector2f)Mouse::getPosition());
		updateClouds();

		if ((event = eventHandler()) != _DisplayMainMenu)
			return event;
	}
}
//-----------------------------------------------------------------------------

/* This function display menu */

void MainMenu::displayMenu() const 
{
	m_window.setView(m_window.getDefaultView());		// update to default view
	m_window.clear();

	m_window.draw(m_background);

	for (auto i : m_buttons) i->draw(m_window);
	
	for (int i = 0; i < NUM_OF_CLOUDS; ++i) 
		m_cloud[i]->draw(m_window);
	
	m_window.display();
}

//-----------------------------------------------------------------------------

/* This function handle eventes of main menu */

op_main_menu MainMenu::eventHandler()
{
	Event event;

	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
			case Event::MouseButtonPressed:
			{
				Vector2f mouse_location((float)event.mouseButton.x, (float)event.mouseButton.y);

				if (m_buttons[_Play]->checkIfPressed(mouse_location))
				{
					m_buttons[_Play]->handlePress();
					return _Play;
				}

				if (m_buttons[_Escape]->checkIfPressed(mouse_location))
				{
					m_buttons[_Escape]->handlePress();
					return _Escape;
				}

				if (m_buttons[_Info]->checkIfPressed(mouse_location))
				{
					m_buttons[_Info]->handlePress();
				}
			}

			case Event::KeyPressed:
				if (event.key.code == Keyboard::Escape) {
					exitGame();
					return _Escape;
				}
			}
	}	
	displayMenu();
	return _DisplayMainMenu;
}