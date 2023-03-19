#pragma once

#include "constants.h"

class Maze
{
public:
	Maze();
	Maze(int startX, int startY);
	~Maze();
	int m_maze[MAZE_NUM_COLS][MAZE_NUM_ROWS];
	int HasWallAt(float x, float y);
private:
	int m_startX;
	int m_startY;
	class PerlinNoise* m_perlinNoise;
	void GenerateMaze();
	void Dig(int row, int column);
	void PaintWalls();
	void PaintWall(int row, int column);
	void PrintMazeToConsole();
};

