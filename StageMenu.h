#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"

//-----------------------------------------------------------------------------

enum op_stage_menu { _Resume, _Restart, _Home, _DisplayMenuStage };

//-----------------------------------------------------------------------------

const int STAGE_MENU_BUTTONS = 3;

//-----------------------------------------------------------------------------

class StageMenu : public Menu
{
public:
	StageMenu(RenderWindow &);
	op_stage_menu runMenu();

private:
	//functions
	op_stage_menu eventHandler();
	void displayMenu();

	//variables
	Text m_text;
	RectangleShape m_rect_menu;
	View m_view;
	Sound m_pauseSound;
};