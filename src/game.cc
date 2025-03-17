#include <cmath>
#include <ctime>
#include <cstdlib>
#include "game.h"
#include "maze.h"
#include "node.h"
#include "path_finder.h"
#include "player.h"
#include "raycaster.h"
#include "surfaces.h"

Game::~Game()
{
    delete m_surfaces;
    delete m_raycaster;
    delete m_player;
    delete m_maze;
}

void Game::Setup()
{
    srand(time(0));

    Maze::GetRandomTile(m_startX, m_startY);

    m_maze = new Maze(m_startX, m_startY);

    m_player = new Player;
    m_player->m_x = m_startY * TILE_SIZE + TILE_SIZE * 0.5;
    m_player->m_y = m_startX * TILE_SIZE + TILE_SIZE * 0.5;
    m_player->m_width = 1;
    m_player->m_height = 1;
    m_player->m_turnDirection = 0;
    m_player->m_walkDirection = 0;
    m_player->m_rotationAngle = PI / 2;
    m_player->m_walkSpeed = PLAYER_WALK_SPEED;
    m_player->m_turnSpeed = PLAYER_TURN_SPEED * (PI / 180);

    m_raycaster = new Raycaster();
    m_surfaces = new Surfaces();
    
    m_isGameRunning = true;
}

void Game::Update()
{
    const auto deltaTime = (SDL_GetTicks() - m_ticksLastFrame) / 1000.0f;
    m_ticksLastFrame = SDL_GetTicks();
   
    MovePlayer(deltaTime);
    
    m_raycaster->CastRays(m_player, m_maze, m_rays);
}

void Game::MovePlayer(float deltaTime)
{
    if (currentNode == nullptr)
    {
        float x, y;
        m_maze->GetRandomOpenLocation(x,y);

        int targetTileX, targetTileY;
        m_maze->TileFromPosition(x, y, targetTileX, targetTileY);

        int playerTileX, playerTileY;
        m_maze->TileFromPosition(m_player->m_x, m_player->m_y, playerTileX, playerTileY);
    
        currentNode = PathFinder::FindPath(m_maze, playerTileX, playerTileY, targetTileX, targetTileY);
        currentNode = PathFinder::SimplifyPath(currentNode);
    }

    std::shared_ptr<Node> nextNode = currentNode->parent;
    if (nextNode == nullptr)
        return;
    
    float targetX = nextNode->x * TILE_SIZE + TILE_SIZE * 0.5f;
    float targetY = nextNode->y * TILE_SIZE + TILE_SIZE * 0.5f;
    float dx = targetX - m_player->m_x;
    float dy = targetY - m_player->m_y;

    float desiredAngle = std::atan2(dy, dx);

    float angleDiff = desiredAngle - m_player->m_rotationAngle;
    angleDiff = std::atan2(std::sin(angleDiff), std::cos(angleDiff));

    float turnFactor = 5.0f * deltaTime;  
    if (turnFactor > 1.0f)
        turnFactor = 1.0f;

    float newAngle = m_player->m_rotationAngle + angleDiff * turnFactor;
    newAngle = std::atan2(std::sin(newAngle), std::cos(newAngle));

    m_player->m_rotationAngle = newAngle;

    constexpr float angleThreshold = 0.004f;
    if (std::fabs(angleDiff) < angleThreshold)
    {
        float distance = std::sqrt(dx * dx + dy * dy);
        if (distance > 2.0f) 
        {
            float moveStep = m_player->m_walkSpeed * deltaTime;
            if (moveStep > distance)
                moveStep = distance;

            m_player->m_x += std::cos(m_player->m_rotationAngle) * moveStep;
            m_player->m_y += std::sin(m_player->m_rotationAngle) * moveStep;
        }
        else
        {
            currentNode = nextNode;
        }
    }
}

void Game::Delay(float time)
{
    SDL_Delay(time);
}
