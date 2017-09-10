#include "Stage.h"
#include "Resource.h"
//-----------------------------------------------------------------------------

/* C-tor of Stage */

Stage::Stage(string level_name, RenderWindow & window)
	: m_collision_handler(*this),
	  m_stage_menu(m_window),
	  m_window(window)
{
	m_time = milliseconds(70);
	m_data._game_object.resize(8);

	// sound definition

	m_birdsSound.setBuffer(Resource::getInstance().getSound(SoundID::_S_Birds));
	m_birdsSound.setLoop(true);
	m_winSound.setBuffer(Resource::getInstance().getSound(SoundID::_S_Win));
	m_loseSound.setBuffer(Resource::getInstance().getSound(SoundID::_S_Lose));

	// world definition

	b2Vec2 gravity((float32)0, (float32)9.8f);
	m_data._box2dWorld = make_unique<b2World>(gravity);
	m_data._box2dWorld->SetContactListener(&m_collision_handler);

	// file definition

	MapLoader file(level_name);
	file.readFile(m_data);

	// background definition

	m_background.setTexture(Resource::getInstance().getTexture(TextureID::_T_Background));
	m_background.setOrigin({ WINDOW_W / 2, WINDOW_H / 2 });
	m_background.setScale({ 1.5f, 1.5f });

	// pause button definition
	
	auto pause = make_shared <Button>(Resource::getInstance().getSound(SoundID::_S_Pause),Vector2f{ 0, 0 }, Vector2i{ 126, 125 }, Vector2i{ 257, 1 }, [this] { menuHandler(); });
	m_buttons.emplace_back(pause);

	// text score definition

	m_textScore.setFont(Resource::getInstance().getFont(FontID::_F_Font));
	m_textScore.setCharacterSize(50);
	m_textScore.setStyle(Text::Bold);
	m_textScore.setFillColor(Color(67, 67, 67, 150));
	m_textScore.setString("Coins:\n" + to_string(0));	
}

//-----------------------------------------------------------------------------

/* This function manage this stage of the game */

GameStatus Stage::play()
{
	//start birds sound
	m_birdsSound.play();
	
	while (m_game_status == GameStatus::_Playing)
	{
		input();
		move();
		animation();
		draw();
		update();
	}
	
	//check if user has left the game
	if (m_game_status == _levelSuccess || m_game_status == _GameOver) {
		//if not, run end level screen
		EndLevelScreen end_screen;
		end_screen.handleEndlevel(*this);
	}

	//stop birds sound
	m_birdsSound.stop();
	//return status of how the game end
	return m_game_status;
}

//-----------------------------------------------------------------------------

/* This function read user events */

void Stage::input()
{
	Event event;
	
	while (m_window.pollEvent(event))
	{
		Vector2f world_pos = m_window.mapPixelToCoords(Mouse::getPosition());

		// check if pause buuton pressed
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape ||
			event.type == Event::MouseButtonPressed && m_buttons[_I_Pause]->checkIfPressed(world_pos))
		{
			m_game_status = GameStatus::_Pause;
			m_buttons[_I_Pause]->handlePress();
		}
	}

	if (m_clock.getElapsedTime() > m_time) 
	{
		m_clock.restart();

		if (Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Space))
			m_data._red->setDirection(Command::_UpLeft);

		else if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Space))
			m_data._red->setDirection(Command::_UpRight);

		else if (Keyboard::isKeyPressed(Keyboard::Right))
			m_data._red->setDirection(Command::_Right);

		else if (Keyboard::isKeyPressed(Keyboard::Left))
			m_data._red->setDirection(Command::_Left);

		else if (Keyboard::isKeyPressed(Keyboard::Space))
			m_data._red->setDirection(Command::_Up);

		else if (Keyboard::isKeyPressed(Keyboard::Down))
			m_data._red->setDirection(Command::_Down);
	}	
}

//-----------------------------------------------------------------------------

/* This function draw all objects on screen*/

void Stage::draw() const
{
	m_window.draw(m_background);

	for (auto &row : m_data._game_object) 
		for (auto col : row)
			col->draw(m_window);

	m_data._red->draw(m_window);

	m_buttons[_I_Pause]->draw(m_window);
	m_window.draw(m_textScore);

	if (m_game_status != GameStatus::_Pause && m_game_status != GameStatus::_GameOver && m_game_status != GameStatus::_levelSuccess)
		m_window.display();
}

//-----------------------------------------------------------------------------

/* This function animate all animated objects */

void Stage::animation()
{
	for (auto it : m_data._animated_object) it->animate();
}

//-----------------------------------------------------------------------------

/* This function move all moving objects */

void Stage::move()
{
	for (auto it : m_data._moving_object) it->move();
}

//-----------------------------------------------------------------------------

/* This function update stage parameters: view,position ... */

void Stage::update()
{
	m_data._red->setDirection(_Still);

	updateView();

	//update buttons and backgournd positions
	Vector2f pos_pause = { m_view.getCenter().x - (m_view.getSize().x / 2 - 10) , m_view.getCenter().y - (m_view.getSize().y / 2 - 10) };
	Vector2f pos_score = { pos_pause.x + m_view.getSize().x - 170, pos_pause.y };
	
	m_background.setPosition(m_view.getCenter());
	m_buttons[_I_Pause]->Hilight(m_window.mapPixelToCoords(Mouse::getPosition()));
	m_buttons[_I_Pause]->setPosition(pos_pause);
	m_textScore.setPosition(pos_score);

	m_window.clear();

	//update Box2d world
	m_data._box2dWorld->Step(1.f / 60.0f, 8, 3);
}

//-----------------------------------------------------------------------------

/* This function update view status according to red position */

void Stage::updateView()
{
	Vector2f tmp, newPos;

	tmp = newPos = { m_data._red->getPosition().x + 10.f - (float)(WINDOW_W / 2.f), m_data._red->getPosition().y + 10.f - (float)(WINDOW_H / 1.5) };

	//block view of left side
	if (tmp.x < 386) newPos.x = 386;
	//block view of top side
	if (tmp.y < 256) newPos.y = 256;

	tmp = { m_data._red->getPosition().x + 10.f + (float)(WINDOW_W / 2.f), m_data._red->getPosition().y + 10.f + (float)(WINDOW_H / 1.5) };

	//block view of right side
	if (tmp.x > m_data._map_size.x - 640) newPos.x = (float)m_data._map_size.x - WINDOW_W - 640;

	m_view.reset({ newPos.x, newPos.y, WINDOW_W, WINDOW_H });
	m_view.zoom(1.5f);
	m_window.setView(m_view);
}

//-----------------------------------------------------------------------------

/* This function handle stage menu operation */

void Stage::menuHandler()
{
	m_birdsSound.pause();

	while (m_game_status == GameStatus::_Pause)
	{	
		draw();

		switch (m_stage_menu.runMenu())
		{
			case _Restart:
				clear();	

			case _Resume:
				m_game_status = GameStatus::_Playing;
				break;

			case _Home:
				m_game_status = GameStatus::_GoToMenu;
				break;
		}
		m_window.setView(m_view);
		m_window.clear();
	}
	m_birdsSound.play();
}

//-----------------------------------------------------------------------------

/* This function clear the stage, i.e. after function execution the stage will start from the beginning */

void Stage::clear()
{
	for (int i = 0; i < m_data._game_object[Index::I_Coin].size(); i++) 
	{
		Coin * coin = static_cast<Coin *>(m_data._game_object[Index::I_Coin][i].get());
		coin->setOnMap(true);
	}

	for (auto it : m_data._animated_object) it->resetAnimate();
	for (auto it : m_data._moving_object) it->setStartPos();

	m_game_status = _Playing;
	m_score = 0;
	m_textScore.setString("Coins:\n" + to_string(m_score));
}