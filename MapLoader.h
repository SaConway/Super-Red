#pragma once
#include <fstream>
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include "Red.h"
#include "Box2D\Box2D.h"
#include "GameObject.h"
#include "GroundChainShape.h"

//-----------------------------------------------------------------------------

struct MapData;
struct texture;

//-----------------------------------------------------------------------------

class MapLoader
{
public:
	MapLoader(string);
	~MapLoader() { m_file.close(); };
	void readFile(MapData &);

private:
	//functions
	void readObjectData(string &, Vector2f &, Vector2i &, Vector2i &) const;
	size_t readChainData(string &, b2Vec2 *&) const;
	int readMapSize(string &) const;
	//variables
	ifstream m_file;
};