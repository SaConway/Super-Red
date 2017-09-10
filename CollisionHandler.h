#pragma once
#include <Box2D\Box2D.h>
#include "WorldObject.h"
#include <SFML/Graphics.hpp>
#include "Ground.h"
#include "Environment.h"
#include "Chest.h"
#include "Coin.h"
#include "Water.h"
#include "Spike.h"
#include "Saw.h"
#include "Mace.h"
#include <memory>
#include <map>

using namespace sf;
using namespace std;
//-----------------------------------------------------------------------------

class Stage;
enum CollisionStatus {_PreSolve , _BeginContact , _EndContact};

struct CollideData  
{
	Stage * _stage;
	b2Contact * _contact;
	CollisionStatus _collide_status;
};

typedef void(*gameFuncCollision)(WorldObject *, CollideData &);
typedef map<pair<string, string>, gameFuncCollision> CollisionFuncMap;

//-----------------------------------------------------------------------------

class CollisionHandler : public b2ContactListener
{
public:
	CollisionHandler(Stage &);

private:
	void PreSolve(b2Contact *, const b2Manifold *) override;
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
	void contactHandler();
	CollideData m_data;
	CollisionFuncMap m_collide_func_map;
};

//-----------------------------------------------------------------------------

/* This function set collision function into collision functions map */

template<class T1, class T2>

void setFunc(CollisionFuncMap & map,gameFuncCollision func)
{
	auto t1 = typeid(T1).name();
	auto t2 = typeid(T2).name();
	map[make_pair(t1, t2)] = func;
}

//-----------------------------------------------------------------------------

gameFuncCollision lookup(const CollisionFuncMap &, const string &, const string &);

//collision functions 
void collisionRedCoin(WorldObject *, CollideData &) ;
void collisionRedChest(WorldObject *, CollideData &);
void collisionRedGroundChain(WorldObject *, CollideData &);
void setGameOver(WorldObject *, CollideData &);
void collisionMace(WorldObject *, CollideData  &);
void collisionSaw(WorldObject *, CollideData &);