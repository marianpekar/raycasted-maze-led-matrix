#pragma once

#include <memory>

#include "constants.h"
#include "ray.h"

struct Node;

class Game
{
public:
	~Game();
	void Setup();
	void Update();
	void Delay(float time);
	
	float m_startX;
	float m_startY;
	
	class Player* m_player;
	class Maze* m_maze;
	class Surfaces* m_surfaces;
	class Raycaster* m_raycaster;
	Ray m_rays[NUM_RAYS];

	std::shared_ptr<Node> currentNode = nullptr;
	
	bool m_isGameRunning;
	int m_ticksLastFrame;
private:
	void MovePlayer(float deltaTime);
};

