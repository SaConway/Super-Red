#pragma once
#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#elif defined(NDEBUG)
#pragma comment(lib, "sfml-main.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-audio.lib")
#else
#error "Unrecognized configuration!"
#endif

//-----------------------------------------------------------------------------

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <memory>
#include "Stage.h"
#include "MainMenu.h"
#include "LevelSelectMenu.h"
#include "OpeningWindow.h"

//-----------------------------------------------------------------------------

class Controller
{
public:
	Controller();
	void handleGame();
	GameStatus runLevel(int);

private:
	unique_ptr <MainMenu> m_main_menu;
	unique_ptr <LevelSelectMenu> m_level_select_menu;
	vector <unique_ptr<Stage>> m_stages;

	//SFML staf
	RenderWindow m_window;
	Sprite m_SBackground;
	Texture m_TBackround;
	Font m_font;
	Sound m_menuSound;
};