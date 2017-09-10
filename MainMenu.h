#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "Menu.h"
#include <memory>
#include "Cloud.h"
#include "InfoManager.h"

//-----------------------------------------------------------------------------

enum op_main_menu {_Play, _Escape, _Info, _DisplayMainMenu};
const int MAIN_MENU_BUTTONS = 3;
const int NUM_OF_CLOUDS = 10;

//-----------------------------------------------------------------------------

class MainMenu : public Menu
{
public:
	MainMenu(RenderWindow &);
	op_main_menu runMenu();
	op_main_menu eventHandler();

private:
	//functions
	void displayMenu() const ;
	void updateClouds() { for (auto &i : m_cloud) i->move();}
	void runInfo() { m_info_manager.runInfo(); }
	void exitGame() { m_window.close(); }
	
	//variables
	Sprite m_background;
	array<unique_ptr<Cloud>, NUM_OF_CLOUDS> m_cloud;
	InfoManager m_info_manager;
};