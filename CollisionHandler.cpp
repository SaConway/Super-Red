#include "CollisionHandler.h"
#include "Stage.h"
#include "Red.h"
#include "Coin.h"
#include "Chest.h"

//-----------------------------------------------------------------------------

/* C-tor of CollisionHandler */

CollisionHandler::CollisionHandler(Stage & stage)
{
	m_data._stage = &stage;

	setFunc<Coin, Red>(m_collide_func_map, &collisionRedCoin);
	setFunc<Red, Chest>(m_collide_func_map, &collisionRedChest);
	setFunc<Red, Water>(m_collide_func_map, &setGameOver);
	setFunc<Red, Saw>(m_collide_func_map, &setGameOver);
	setFunc<Red, Mace>(m_collide_func_map, &setGameOver);
	setFunc<Red, Spike>(m_collide_func_map, &setGameOver);
	setFunc<Red, GroundChainShape>(m_collide_func_map, &collisionRedGroundChain);
	setFunc<Mace, GroundChainShape>(m_collide_func_map, &collisionMace);
	setFunc<Saw, GroundChainShape>(m_collide_func_map, &collisionSaw);
	setFunc<Mace, Water>(m_collide_func_map, &collisionMace);
}

//-----------------------------------------------------------------------------

/* This function is called after a contact is updated */

void CollisionHandler::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{
	m_data._contact = contact;
	m_data._collide_status = _PreSolve;
	contactHandler();
}

//-----------------------------------------------------------------------------

/* This function is called when the objects begin contact */

void CollisionHandler::BeginContact(b2Contact * contact)
{	
	m_data._contact = contact;
	m_data._collide_status = _BeginContact;
	contactHandler();
}

//-----------------------------------------------------------------------------

/* This function is called when the objects end contact */

void CollisionHandler::EndContact(b2Contact * contact)
{
	m_data._contact = contact;
	m_data._collide_status = _EndContact;
	contactHandler();
}

//-----------------------------------------------------------------------------

/*This function handle each contact search for contact in map and execute operation.*/

void CollisionHandler::contactHandler()
{
	auto obj1 = (WorldObject *)(m_data._contact->GetFixtureA()->GetBody()->GetUserData());
	auto obj2 = (WorldObject *)(m_data._contact->GetFixtureB()->GetBody()->GetUserData());

	if (!obj1 || !obj2) return;

	gameFuncCollision func = nullptr;

	func = lookup(m_collide_func_map, typeid(*obj1).name(), typeid(*obj2).name());

	if (func != nullptr)
		func(obj1, m_data);
	else
	{
		func = lookup(m_collide_func_map, typeid(*obj2).name(), typeid(*obj1).name());
		if (func != nullptr)
			func(obj2, m_data);
	}
}

//-----------------------------------------------------------------------------

/* This function find the string pair in the map and return gameFuncCollision if found */

gameFuncCollision lookup(const CollisionFuncMap & map, const string & class1, const string & class2)
{
	auto it = map.find(make_pair(class1, class2));

	if (it == map.end())
		return nullptr;

	return it->second;
}
//-----------------------------------------------------------------------------

/* This function handle collsion between red and coin */

void collisionRedCoin(WorldObject * go_coin, CollideData & data)
{
	if (data._collide_status == _PreSolve) 
	{
		Coin * coin = nullptr;
		coin = static_cast<Coin*>(go_coin);

		if (coin != nullptr)
		{
			if (coin->isOnMap())								//if on map remove coin
			{
				coin->playSound();

				coin->setOnMap(false);
				data._stage->updateScore();
				data._contact->SetEnabled(false);						//set the coin body in off mode
			}
			else data._contact->SetEnabled(false);
		}
	}
}

//-----------------------------------------------------------------------------

/* This function handle collsion between red and chest */

void collisionRedChest(WorldObject * game_object, CollideData & data)
{
	if (data._collide_status == _PreSolve)
	{
		data._stage->playWinSound();
		data._stage->updateGameStatus(GameStatus::_levelSuccess);
	}
}

//-----------------------------------------------------------------------------

/* This function handle collsion between red and enemy */

void setGameOver(WorldObject * game_object, CollideData & data)
{
	if (data._collide_status == _PreSolve) 
	{
		data._stage->playLoseSound();
		data._stage->updateGameStatus(GameStatus::_GameOver);
	}
}

//-----------------------------------------------------------------------------

/* This function handle collsion between red and ground */

void collisionRedGroundChain(WorldObject * go_red, CollideData & data)
{
	Red * red = nullptr;
 	int add = 1;

	switch(data._collide_status)
	{
	case _EndContact:
		add = -1;

	case _BeginContact:
		//check if foot sensor(red) is on ground
		if (data._contact->GetFixtureA()->IsSensor())
			red = static_cast<Red*>(go_red);

		else if (data._contact->GetFixtureB()->IsSensor())
			red = static_cast<Red*>(go_red);

		if (red != nullptr) 
			red->landingOnGround(red->getNumOfFootContact() + add);

		break;
	}
}
//-----------------------------------------------------------------------------

/* This function handle collsion between mace and ground/water */

void collisionMace(WorldObject * go_mace , CollideData & data)
{
	if (data._collide_status == _BeginContact)
	{
		Mace * mace = nullptr;
		mace = static_cast<Mace*>(go_mace);

		if (mace != nullptr) mace->handleColision();
	}
}

//-----------------------------------------------------------------------------

/* This function handle collsion between saw and ground/water */

void collisionSaw(WorldObject * go_saw, CollideData & data)
{
	if (data._collide_status == _BeginContact)
	{
		Saw * saw = nullptr;
		saw = static_cast<Saw*>(go_saw);

		if (saw != nullptr) saw->handleColision();
	}
}