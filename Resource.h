#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <memory>

//-----------------------------------------------------------------------------

using namespace std;
using namespace sf;

const float WINDOW_W = 2048;
const float WINDOW_H = 1536;

enum TextureID {
	_T_Background,
	_T_Ground,
	_T_Water,
	_T_Coin,
	_T_Chest,
	_T_Trees,
	_T_Grass,
	_T_Mace,
	_T_Saw,
	_T_Spike,
	_T_Flowers,
	_T_Red,
	_T_Buttons,
	_T_MenuBackground,
	_T_LevelSelectBackground,
	_T_Door,
	_T_Sign,
	_T_Tape,
	_T_Star,
	_T_Clouds
};

enum SoundID {
	_S_Menu,
	_S_Click,
	_S_Coin,
	_S_Win,
	_S_Lose,
	_S_Jump,
	_S_Birds,
	_S_Player_Step1,
	_S_Player_Step2,
	_S_Player_Step3,
	_S_Player_Step4,
	_S_Player_Step5,
	_S_Player_Step6,
	_S_Pause
};

enum FontID {
	_F_Font
};

//-----------------------------------------------------------------------------

class Resource
{
public:
	static Resource & getInstance();
	const Texture & getTexture(TextureID);
	const SoundBuffer & getSound(SoundID);
	const Font & getFont(FontID);
	~Resource() = default;

private:
	Resource();
	Resource(const Resource & other) = delete;
	void operator = (const Resource & other) = delete;

	map<TextureID, Texture> m_texture_map;
	map<SoundID, SoundBuffer> m_sound_map;
	map<FontID, Font> m_font_map;
};

//-----------------------------------------------------------------------------
 
/*This function is loading file from memory*/

template <class T1,class T2, class T3>
void loadFile(map<T2, T1> & map , T3 ID , string str)
{
	T1 temp;
	
	if (!temp.loadFromFile(str)) 
		throw runtime_error("Resource could not load " + str +" path not found.");

	map[ID] = temp;
}

//-----------------------------------------------------------------------------

/*This function is accessing data from map*/

template <class T1, class T2, class T3>
const T1 & getResource(map<T2, T1> & map, T3 ID)
{
	auto it = map.find(ID);
	
	if (it == map.end())
		throw runtime_error("Error access map");

	return it->second;
}
