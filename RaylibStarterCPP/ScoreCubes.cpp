#include "ScoreCubes.h"

ScoreCubes::ScoreCubes(int initX)
{
	x = initX;

	for (int i = 0; i < 3; i++)
	{
		cubes[i].x = x;
		cubes[i].y = 60 + (offset * i);
		cubes[i].width = 15;
		cubes[i].height = 15;
	}
}

void ScoreCubes::DrawScore()
{
	for (int i = 0; i < score; i++)
	{
		DrawRectangle(cubes[i].x, cubes[i].y, cubes[i].width, cubes[i].height, RAYWHITE);
	}
}