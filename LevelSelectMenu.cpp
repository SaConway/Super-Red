#include "LevelSelectMenu.h"
#include "Resource.h"
//-----------------------------------------------------------------------------

/* C-tor of LevelSelectMenu */

LevelSelectMenu::LevelSelectMenu(RenderWindow & window)
	: Menu(window)
{
	// background definition

	m_background.setTexture(Resource::getInstance().getTexture(TextureID::_T_LevelSelectBackground));
	Vector2f scaled_size = getScaledBackgoundSize(*m_background.getTexture());
	m_background.scale(scaled_size);

	if (scaled_size.y < 1.f) scaled_size.y = 1;

	// return button definition

	auto return_but = make_shared <Button>(Vector2f{ 10, 10 }, Vector2i{ 128, 125 }, Vector2i{ 128, 130 }, [this] {});
	return_but->setScale({ 0.8f, 0.75f });
	m_buttons.emplace_back(return_but);

	// level icon definitions

	for (int i = 0; i < NUM_OF_LEVELS; ++i)
	{
		LevelIcon li(i, scaled_size.y);
		m_level_icons.emplace_back(li);
	}

	// clouds definition

	for (int i = 0; i < NUM_OF_CLOUDS_LEVEL; i++)
		m_clouds[i] = make_unique<Cloud>();	
}

//-----------------------------------------------------------------------------

/* This function run the LevelSelectMenu */

op_level_select_menu LevelSelectMenu::run()
{
	while (m_window.isOpen())
	{
		draw();

		Vector2f mouse_pos = Vector2f(Mouse::getPosition());
		mouseOnButton(mouse_pos);
		for (int i = 0; i < m_level_icons.size(); ++i) m_level_icons[i].hilight(mouse_pos);

		updateClouds();

		op_level_select_menu op = eventHandler();
		if (op != op_level_select_menu::_Stay) return op;
	}

	return op_level_select_menu::_Stay;
}

//-----------------------------------------------------------------------------

/* This function handle the events of LevelSelectMenu */

op_level_select_menu LevelSelectMenu::eventHandler()
{
	Event event;

	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Escape) return op_level_select_menu::_BackToMainMenu;
				break;

			case Event::MouseButtonPressed:
			{
				// check if back to menu button was pressed
				if (m_buttons[0]->checkIfPressed((Vector2f)Mouse::getPosition()))
				{
					m_buttons[0]->handlePress();
					return op_level_select_menu::_BackToMainMenu;
				}

				for (int i = 0; i < m_level_icons.size(); ++i)
				{
					// check if player can access level
					if (!m_level_icons[i].getIsAccess()) continue;

					if (m_level_icons[i].isLevelSelected((Vector2f)Mouse::getPosition()))
					{
						m_level_icons[i].handlePress();
						return op_level_select_menu(i + 1);	
					}
				}
			}
		}
	}
	return op_level_select_menu::_Stay;
}

//-----------------------------------------------------------------------------

/* This function handle the case when the player succeeded a level */

void LevelSelectMenu::handleLevelSuccess(int level, float score_percent)
{
	if (!m_level_icons[level].getIsSuccess()) m_level_icons[level].updateSign();
	updateLevelSuccess(level);
	updateLevelAccess(level + 1);

	if (score_percent > 0.0f && score_percent <= 0.5f)
		updateStars(level, 1);

	else if (score_percent > 0.5f && score_percent < 1)
		updateStars(level, 2);

	else if (score_percent == 1)
		updateStars(level, 3);
}

//-----------------------------------------------------------------------------

/* This function draw LevelSelectMenu objects */

void LevelSelectMenu::draw() const
{
	m_window.setView(m_window.getDefaultView());
	m_window.clear();

	m_window.draw(m_background);
	for (auto &i : m_clouds) i->draw(m_window);
	for (auto i : m_level_icons) i.draw(m_window);
	for (auto i : m_buttons) i->draw(m_window);

	m_window.display();
}