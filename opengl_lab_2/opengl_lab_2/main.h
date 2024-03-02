#pragma once

#include<windows.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include <string>
#include <iostream>

using std::string;
using std::to_string;

enum Direction {
	FORWARD,
	BACKWARDS
};

const float REFRESH_RATE = 1000.0 / 60.0;

Direction direction = Direction::FORWARD;
float xPos = -1.0f;
float yPos = -1.0f;

float speed = 0.01f;
float a = 1.0f;
float k = 1.0f;
float size = 1.0f;

void init();
void display();
void reshape(int, int);
void transform(int);
void processKeyboardInput(unsigned char, int, int);
void drawStatistics();
void drawGrid();
float mapValue(float, float);