#include <GL/glut.h>
#include <string>
#include <iostream>
#include "stb_image.h"

using std::cout;
using std::string;

bool isRotationEnabled = false;
bool isFogEnabled = false;
bool isFogLinOrExp = true;
bool lightingSwitchArray[4] = { false, false, false, false };

float angle = 0.0;
float lightXPos = -5.0;

GLuint textureID;
GLenum GL_ligthNames[] = { GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3 };

string rotationControls = "(a) Rotation: OFF";
string lighting = "(1, 2, 3, 4) Lighting: ";
string lightNames[] = { "Ambient", "Point", "Spot", "Distant" };
string fog = "(f) Fog: OFF";
string fogMode = "(g) Fog Mode: Linear";
