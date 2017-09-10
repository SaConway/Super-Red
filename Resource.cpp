#include "Resource.h"



//-----------------------------------------------------------------------------


Resource & Resource::getInstance()
{
	static Resource resource;
	return resource;	
}

//-----------------------------------------------------------------------------


Resource::Resource()
{
	//load all Texture files 
	loadFile<Texture, TextureID>(m_texture_map, TextureID::_T_Background,"Resources\\Pics\\Game\\Background.png");
	loadFile<Texture, TextureID>(m_texture_map, TextureID::_T_Ground,"Resources\\Pics\\Game\\Ground.png");
	loadFile<Texture, TextureID>(m_texture_map, TextureID::_T_Water, "Resources\\Pics\\Game\\Water.png");
	loadFile<Texture, TextureID>(m_texture_map, TextureID::_T_Coin, "Resources\\Pics\\Game\\Coin.png");
	loadFile<Texture, TextureID>(m_texture_map, TextureID::_T_Chest, "Resources\\Pics\\Game\\Chest.png");
	loadFile<Texture, TextureID>(m_texture_map, TextureID::_T_Trees, "Resources\\Pics\\Game\\Trees.png");
	loadFile<Texture, TextureID>(m_texture_map, TextureID::_T_Grass, "Resources\\Pics\\Game\\Grass.png");
	loadFile<Texture, TextureID>(m_texture_map, TextureID::_T_Mace, "Resources\\Pics\\Game\\Mace.png");
	loadFile<Texture, TextureID>(m_texture_map, TextureID::_T_Saw, "Resources\\Pics\\Game\\Saw.png");
	loadFile<Texture, TextureID>(m_texture_map, TextureID::_T_Spike, "Resources\\Pics\\Game\\Spike.png");
	loadFile<Texture, TextureID>(m_texture_map, TextureID::_T_Flowers, "Resources\\Pics\\Game\\Flowers.png");
	loadFile<Texture, TextureID>(m_texture_map, TextureID::_T_Red, "Resources\\Pics\\Game\\Red.png");
	loadFile<Texture, TextureID>(m_texture_map, TextureID::_T_Buttons, "Resources\\Pics\\Gui\\Buttons.png");
	loadFile<Texture, TextureID>(m_texture_map, TextureID::_T_MenuBackground, "Resources\\Pics\\Gui\\MenuBackground.png");
	loadFile<Texture, TextureID>(m_texture_map, TextureID::_T_LevelSelectBackground, "Resources\\Pics\\Gui\\LevelSelectBackground.png");
	loadFile<Texture, TextureID>(m_texture_map, TextureID::_T_Door, "Resources\\Pics\\Gui\\Door.png");
	loadFile<Texture, TextureID>(m_texture_map, TextureID::_T_Sign, "Resources\\Pics\\Gui\\Sign.png");
	loadFile<Texture, TextureID>(m_texture_map, TextureID::_T_Tape, "Resources\\Pics\\Gui\\Tape.png");
	loadFile<Texture, TextureID>(m_texture_map, TextureID::_T_Star, "Resources\\Pics\\Gui\\Star.png");
	loadFile<Texture, TextureID>(m_texture_map, TextureID::_T_Clouds, "Resources\\Pics\\Gui\\Clouds.png");

	for (auto &it : m_texture_map)
		it.second.setSmooth(1);

	//load all sound files
	loadFile<SoundBuffer, SoundID>(m_sound_map, SoundID::_S_Menu, "Resources\\Audio\\Menu.ogg");
	loadFile<SoundBuffer, SoundID>(m_sound_map, SoundID::_S_Click, "Resources\\Audio\\Click.ogg");
	loadFile<SoundBuffer, SoundID>(m_sound_map, SoundID::_S_Coin, "Resources\\Audio\\Coin.ogg");
	loadFile<SoundBuffer, SoundID>(m_sound_map, SoundID::_S_Win, "Resources\\Audio\\Win.ogg");
	loadFile<SoundBuffer, SoundID>(m_sound_map, SoundID::_S_Lose, "Resources\\Audio\\Lose.ogg");
	loadFile<SoundBuffer, SoundID>(m_sound_map, SoundID::_S_Jump, "Resources\\Audio\\Jump.ogg");
	loadFile<SoundBuffer, SoundID>(m_sound_map, SoundID::_S_Birds, "Resources\\Audio\\Birds.ogg");
	loadFile<SoundBuffer, SoundID>(m_sound_map, SoundID::_S_Player_Step1, "Resources\\Audio\\player_step1.ogg");
	loadFile<SoundBuffer, SoundID>(m_sound_map, SoundID::_S_Player_Step2, "Resources\\Audio\\player_step2.ogg");
	loadFile<SoundBuffer, SoundID>(m_sound_map, SoundID::_S_Player_Step3, "Resources\\Audio\\player_step3.ogg");
	loadFile<SoundBuffer, SoundID>(m_sound_map, SoundID::_S_Player_Step4, "Resources\\Audio\\player_step4.ogg");
	loadFile<SoundBuffer, SoundID>(m_sound_map, SoundID::_S_Player_Step5, "Resources\\Audio\\player_step5.ogg");
	loadFile<SoundBuffer, SoundID>(m_sound_map, SoundID::_S_Player_Step6, "Resources\\Audio\\player_step6.ogg");
	loadFile<SoundBuffer, SoundID>(m_sound_map, SoundID::_S_Pause, "Resources\\Audio\\Pause.ogg");
	
	//load font 
	loadFile<Font, FontID>(m_font_map, FontID::_F_Font, "Resources\\Font.ttf");

}

//-----------------------------------------------------------------------------

/*get resource from m_texture_map*/

const Texture & Resource::getTexture(TextureID ID)
{
	return getResource<Texture, TextureID>(m_texture_map, ID);
}

//-----------------------------------------------------------------------------

/*get resource from m_sound_map*/

const SoundBuffer & Resource::getSound(SoundID ID)
{
	return getResource<SoundBuffer, SoundID>(m_sound_map, ID);
}

//-----------------------------------------------------------------------------

/*get resource from m_font_map*/

const Font & Resource::getFont(FontID ID)
{
	return getResource<Font, FontID>(m_font_map, ID);
}
