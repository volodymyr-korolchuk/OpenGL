#include <GL/glut.h>
#include <string>
#include <iostream>
#include "stb_image.h"

using std::cout;
using std::string;

bool isRotationEnabled = false;
bool isMovementEnabled = false;
bool isFogEnabled = false;
bool isFogLinOrExp = true;
bool lightingSwitchArray[4] = { false, false, false, false };

float angle = 0.0;
float lightXPos = -5.0;
float rotationSpeedFactor = 3000;

float cubeXPos = 0.0;
float cubeYPos = 0.0;
float cubeZPos = 0.0;

float cubeXSpeed = 0.01;
float cubeYSpeed = 0.01;
float cubeZSpeed = 0.01;

GLuint textureID;
GLenum GL_ligthNames[] = { GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3 };

string rotationControls = "Rotation: OFF";
string lighting = "Lighting: ";
string lightNames[] = { "Ambient", "Point", "Spot", "Distant" };
string fog = "Fog: OFF";
string fogMode = "Fog Mode: Linear";