#include "Controller.h"
#include "Resource.h"
//-----------------------------------------------------------------------------

/* Main function */

int main()
{
	try
	{
		Controller c;
		c.handleGame();
	}

	catch (exception & e)
	{
		cout << "Exception: " << e.what() << endl;
		cout << "Press any key to exit";
		cin.get();
	}

	return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------

/* C-tor of Controller */

Controller::Controller() 
{
	OpeningWindow ow(m_window);
	ow.drawSR();

	srand((unsigned)time(NULL));
	m_window.create(sf::VideoMode(), "Super Red", Style::Fullscreen);

	m_menuSound.setBuffer(Resource::getInstance().getSound(SoundID::_S_Menu));
	m_menuSound.setVolume(10.f);

	m_main_menu = make_unique<MainMenu>(m_window);
	m_level_select_menu = make_unique<LevelSelectMenu>(m_window);

	ow.drawPG();
}

//-----------------------------------------------------------------------------

/* This function handle the game - controlling main menu / second menu, and stage */

void Controller::handleGame()
{
	m_menuSound.play();
	m_menuSound.setLoop(true);

	op_level_select_menu op_level_select_menu;

	while (m_window.isOpen())
	{
		if (m_main_menu->runMenu() != op_main_menu::_Play) continue;

		while (true)
		{
			// if we got here, then wer'e in the second menu (level select)
			op_level_select_menu = m_level_select_menu->run();

			if (op_level_select_menu == op_level_select_menu::_BackToMainMenu) break; // back to main menu

			else if (op_level_select_menu == op_level_select_menu::_Stay) continue; // stay in level select menu

			// if we got here, then the user want to play level number...
			int level = op_level_select_menu;

			m_menuSound.stop();
			GameStatus gs = runLevel(level);
			m_menuSound.play();

			if (gs == GameStatus::_levelSuccess) 
			{			
				float score_percent = m_stages[level - 1]->SuccessPercent();
				m_level_select_menu->handleLevelSuccess(level - 1, score_percent);
			}
		}
	}
}

//-----------------------------------------------------------------------------

/* This function run the level selected, and return the game status after playing */

GameStatus Controller::runLevel(int level)
{
	if (m_stages.size() < level)
		m_stages.emplace_back(make_unique<Stage>("Maps\\Level" + to_string(level) + ".txt" ,m_window));
	else
		m_stages[level - 1]->clear();

	return m_stages[level - 1]->play();
}