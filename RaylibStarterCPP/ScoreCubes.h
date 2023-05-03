#pragma once
#include "raylib.h"
class ScoreCubes
{
public:
	int score = 0;
	int x;
	ScoreCubes(int initX);
	void DrawScore();
private:
	Rectangle cubes[3];

	int offset = 25;
};

