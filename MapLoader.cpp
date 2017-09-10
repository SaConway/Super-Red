#include "MapLoader.h"
#include "Stage.h"
#include <sstream>
#include <new>
#include <algorithm>
#include "Resource.h"
//-----------------------------------------------------------------------------

/* c-tor of file */

MapLoader::MapLoader(string level_name)
{
	m_file.open(level_name);

	if (!m_file.is_open()) throw runtime_error(level_name + ":file Level problem");
}

//-----------------------------------------------------------------------------

/* This function read level into data stracturs */

void MapLoader::readFile(MapData & data)
{
	std::string line;
	Vector2f pos_by_pixel; 
	Vector2i size_of_pic, pos_in_pic;

	while (getline(m_file, line))
	{
		if (line.find("width") != string::npos) data._map_size.x = readMapSize(line);
		if (line.find("height") != string::npos) data._map_size.y = readMapSize(line);

		if (line.find("Red") != string::npos)
		{
			readObjectData(line, pos_by_pixel, size_of_pic, pos_in_pic);

			data._red = make_shared<Red>(pos_by_pixel, size_of_pic, pos_in_pic, data._box2dWorld);
			data._animated_object.push_back(data._red);
			data._moving_object.push_back(data._red);
		}

		if (line.find("Mace") != string::npos)
		{
			readObjectData(line, pos_by_pixel, size_of_pic, pos_in_pic);

			shared_ptr<Mace> mace = make_shared<Mace>(pos_by_pixel, size_of_pic, pos_in_pic, data._box2dWorld);
			data._game_object[I_Mace].push_back(mace);
			data._animated_object.push_back(mace);
			data._moving_object.push_back(mace);
		}

		if (line.find("Ground") != string::npos)
		{
			readObjectData(line, pos_by_pixel, size_of_pic, pos_in_pic);

			shared_ptr<Ground> ground = make_shared<Ground>(pos_by_pixel, size_of_pic, pos_in_pic);
			data._game_object[I_Ground].push_back(ground);
		}

		if (line.find("Grass") != string::npos)
		{
			readObjectData(line, pos_by_pixel, size_of_pic, pos_in_pic);

			shared_ptr<Environment> environment = make_shared<Environment>(Resource::getInstance().getTexture(TextureID::_T_Grass),pos_by_pixel, size_of_pic, pos_in_pic);
			data._game_object[I_Environment].push_back(environment);
		}

		if (line.find("Trees") != string::npos)
		{
			readObjectData(line, pos_by_pixel, size_of_pic, pos_in_pic);

			shared_ptr<Environment> environment = make_shared<Environment>(Resource::getInstance().getTexture(TextureID::_T_Trees),pos_by_pixel, size_of_pic, pos_in_pic);
			data._game_object[I_Environment].push_back(environment);
		}

		if (line.find("Flowers") != string::npos)
		{
			readObjectData(line, pos_by_pixel, size_of_pic, pos_in_pic);

			shared_ptr<Environment> environment = make_shared<Environment>(Resource::getInstance().getTexture(TextureID::_T_Flowers),pos_by_pixel, size_of_pic, pos_in_pic);
			data._game_object[I_Environment].push_back(environment);
		}

		if (line.find("Water") != string::npos)
		{
			readObjectData(line, pos_by_pixel, size_of_pic, pos_in_pic);

			shared_ptr<Water> water = make_shared<Water>(pos_by_pixel, size_of_pic, pos_in_pic, data._box2dWorld);
			data._game_object[I_Water].push_back(water);
			data._animated_object.push_back(water);
		}

		if (line.find("Coin") != string::npos)
		{
			readObjectData(line, pos_by_pixel, size_of_pic, pos_in_pic);

			shared_ptr<Coin> coin = make_shared<Coin>(pos_by_pixel, size_of_pic, pos_in_pic, data._box2dWorld);
			data._game_object[I_Coin].push_back(coin);
			data._animated_object.push_back(coin);
		}

		if (line.find("Chest") != string::npos)
		{
			readObjectData(line, pos_by_pixel, size_of_pic, pos_in_pic);

			shared_ptr<Chest> chest = make_shared<Chest>(pos_by_pixel, size_of_pic, pos_in_pic, data._box2dWorld);
			data._game_object[I_Chest].push_back(chest);
			data._animated_object.push_back(chest);
		}

		if (line.find("Spike") != string::npos)
		{
			readObjectData(line, pos_by_pixel, size_of_pic, pos_in_pic);

			shared_ptr<Spike> spike = make_shared<Spike>(pos_by_pixel, size_of_pic, pos_in_pic, data._box2dWorld);
			data._game_object[I_Spike].push_back(spike);
		}

		if (line.find("Saw") != string::npos)
		{
			readObjectData(line, pos_by_pixel, size_of_pic, pos_in_pic);

			shared_ptr<Saw> saw = make_shared<Saw>(pos_by_pixel, size_of_pic, pos_in_pic, data._box2dWorld);
			data._game_object[I_Saw].push_back(saw);
			data._animated_object.push_back(saw);
			data._moving_object.push_back(saw);
		}
		if (line.find("Vertex") != string::npos)
		{
			try 
			{
				b2Vec2 * vertex = nullptr;
				size_t num_of_vertex = readChainData(line, vertex);
				shared_ptr<GroundChainShape> gcs = make_shared<GroundChainShape>(vertex, data._box2dWorld, num_of_vertex);
				data._ground_object.emplace_back(gcs);
				delete[] vertex;
			}
			catch (bad_alloc bad_alloc) 
			{
				m_file.close();
				exit(EXIT_FAILURE);
			}
		}

	}
}

//-----------------------------------------------------------------------------

/* This function read tile data from the line */

void MapLoader::readObjectData(std::string & line, Vector2f & pos_by_pixel, Vector2i & size_of_pic, Vector2i & pos_in_pic) const
{
	pos_by_pixel.x = (float)stoi(line.substr(line.find("x=\"") + 3, line.find("\" y") - line.find("x=\"") - 3));
	pos_by_pixel.y = (float)stoi(line.substr(line.find("y=\"") + 3, line.find("\" w") - line.find("y=\"") - 3));
	size_of_pic.x = stoi(line.substr(line.find("w=\"") + 3, line.find("\" h") - line.find("w=\"") - 3));
	size_of_pic.y = stoi(line.substr(line.find("h=\"") + 3, line.find("\" xo") - line.find("h=\"") - 3));
	pos_in_pic.x = stoi(line.substr(line.find("xo=\"") + 4, line.find("\" yo") - line.find("xo=\"") - 3));
	pos_in_pic.y = stoi(line.substr(line.find("yo=\"") + 4, line.find("\" id") - line.find("yo=\"") - 3));
}

//-----------------------------------------------------------------------------

/* This function read vertex chain from line */

size_t MapLoader::readChainData(string & line , b2Vec2 * &vertex) const
{
	b2Vec2 offset;
	offset.x = (float)stoi(line.substr(line.find("x=\"") + 3, line.find("\" y") - line.find("x=\"") - 3));
	offset.y = (float)stoi(line.substr(line.find("y=\"") + 3, line.find("\" w") - line.find("y=\"") - 3));

	std::string temp;
	size_t start = line.find(':');
	temp = line.substr(start + 1, line.size());
	istringstream string(temp);
	size_t num_of_vertex = std::count(temp.begin(), temp.end(), ',');
	b2Vec2 vec;
	vertex = new b2Vec2[num_of_vertex];
	for(int i =0 ; i < num_of_vertex ; i++)
	{
		char c ;
		string >> vec.x >> c >>vec.y;
		vec = b2Vec2{ (offset.x+vec.x -128.f) / RATIO , (offset.y+vec.y-128.f ) / RATIO };
		vertex[i] = vec;
	}
	return num_of_vertex;
}

//-----------------------------------------------------------------------------

/* This function read map size from line */

int MapLoader::readMapSize(string & line) const
{
	return stoi(line.substr(line.find('>') + 1, line.find("</") - line.find('>') - 1));
}
