#include "StageMenu.h"
#include "Resource.h"
//-----------------------------------------------------------------------------

/* C-tor of StageMenu */

StageMenu::StageMenu(RenderWindow & window)
	: Menu(window), m_view(FloatRect{ 0, 0, 300, WINDOW_H })
{
	m_pauseSound.setBuffer(Resource::getInstance().getSound(SoundID::_S_Pause));

	m_view.setViewport(FloatRect(0, 0, 0.20f, 1));

	Vector2f pos_by_pixel;
	Vector2i size_of_pic, pos_in_pic;

	m_rect_menu.setSize(Vector2f{ m_view.getSize().x - 5, m_view.getSize().y });
	m_rect_menu.setFillColor(Color(41, 134, 115, 255));
	m_rect_menu.setOutlineThickness(5);
	m_rect_menu.setOutlineColor(Color(204, 179, 13, 255));

	m_text.setCharacterSize(60);
	m_text.setFont(Resource::getInstance().getFont(FontID::_F_Font));
	m_text.setFillColor(Color(255, 255, 255, 255));
	m_text.setString("PAUSED");
	m_text.setPosition(Vector2f{ m_rect_menu.getSize().x / 2, m_rect_menu.getLocalBounds().top + 200 });
	m_text.setOrigin(Vector2f{ m_text.getLocalBounds().width / 2, m_text.getLocalBounds().top + 100 });

	//Resume button

	pos_by_pixel = { m_rect_menu.getSize().x / 2, m_rect_menu.getLocalBounds().top + 500 };
	pos_in_pic = { 640, 128 };
	size_of_pic = { BUTTONS_SIZE , BUTTONS_SIZE };

	auto resume = make_shared <Button>(pos_by_pixel, size_of_pic, pos_in_pic, [this] {});

	resume->setScale({ 0.7f,1 });
	resume->setOrigin({ m_text.getLocalBounds().width / 2 - 25, m_text.getLocalBounds().top + 100 });
	m_buttons.emplace_back(resume);

	//Restart button

	pos_by_pixel = { m_rect_menu.getSize().x / 2, m_rect_menu.getLocalBounds().top + 700 };
	pos_in_pic = { 896,256 };

	auto restart = make_shared <Button>(pos_by_pixel, size_of_pic, pos_in_pic, [this] {});

	restart->setScale({ 0.7f,1 });
	restart->setOrigin({ m_text.getLocalBounds().width / 2 - 25, m_text.getLocalBounds().top + 100 });
	m_buttons.emplace_back(restart);

	//Home button

	pos_by_pixel = { m_rect_menu.getSize().x / 2, m_rect_menu.getLocalBounds().top + 900 };
	pos_in_pic = { 768,256 };

	auto homebutton = make_shared <Button>(pos_by_pixel, size_of_pic, pos_in_pic, [this] {});

	homebutton->setScale({ 0.7f,1 });
	homebutton->setOrigin({ m_text.getLocalBounds().width / 2 - 25, m_text.getLocalBounds().top + 100 });
	m_buttons.emplace_back(homebutton);
}

//-----------------------------------------------------------------------------

/* This function run the Stage Menu */

op_stage_menu StageMenu::runMenu()
{
	displayMenu();

	mouseOnButton(m_window.mapPixelToCoords(Mouse::getPosition()));

	op_stage_menu event = eventHandler();
	if (event != _DisplayMenuStage)
		return event;

	return _DisplayMenuStage;
}

//------------------------------------------------------------------------------

/* This function handler the stage menu */

op_stage_menu StageMenu::eventHandler()
{
	Event event;

	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Escape)
				{
					m_pauseSound.play();
					return _Resume;
				}
				break;

			case Event::MouseButtonPressed:
			{
				Vector2f world_pos = m_window.mapPixelToCoords(Mouse::getPosition());

				for (int button = 0; button < m_buttons.size(); button++)
					if (m_buttons[button]->checkIfPressed(world_pos))
					{
						m_buttons[button]->handlePress();
						return (op_stage_menu)button;
					}
			}
		}
	}
	return _DisplayMenuStage;
}

//-----------------------------------------------------------------------------

/* This function draw the stage menu */

void StageMenu::displayMenu()
{
	m_window.setView(m_view);
	m_window.draw(m_rect_menu);
	m_window.draw(m_text);
	
	for (auto it : m_buttons)
		it->draw(m_window);

	m_window.display();
}