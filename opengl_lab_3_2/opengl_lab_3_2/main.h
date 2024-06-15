#pragma once
#include <GL/glut.h>
#include <string>
#include <iostream>

using std::string;
using std::cout;

bool isOrtho = false;
bool isWire = false;
bool isAnimationEnabled = false;
bool isGreyscale = true;
bool isInterpolationEnabled = false;

const float NearZ = 1.0;
const float FarZ = 10.0;

float angle = 0.0;

GLUnurbsObj* surfName;

GLfloat ctrlPoints[4][4][3] = {
    {{-1.0, 0.1, -1.0}, {-1.0, 0.1, -0.9}, {-1.0, 0.1, 0.9}, {-1.0, 0.1, 1.0}},
    {{0.0, 0.1, -1.0}, {0.0, 0.5, -0.9}, {0.0, 0.5, 0.9}, {0.0, 0.4, 1.0}},
    {{0.0, 0.7, -1.0}, {0.0, 0.0, -0.9}, {0.0, 0.4, 0.9}, {0.0, 0.1, 1.0}},
    {{1.0, 0.1, -1.0}, {1.0, 0.3, -0.9}, {1.0, 0.1, 0.9}, {1.0, 0.4, 1.0}}
};


GLfloat knots[8] = { 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 };
GLfloat edgePt[5][2] = { {-1.0, -1.0}, {1.0, -1.0}, {1.0, 1.0}, {-1.0, 1.0}, {-1.0, -1.0} };

GLfloat curvePt[4][2] = { {0.25, 0.5}, {0.25, 0.75}, {0.75, 0.75}, {0.75, 0.5} };
GLfloat curveKnots[8] = { 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 };

GLfloat pwlPt[4][2] = { {0.75, 0.5}, {0.5, 0.25}, {0.25, 0.5} };

string projectionMode = isOrtho ? "(o) Projection: Orthographic" : "(o) Projection: Perspective";
string animationEnabled = isAnimationEnabled ? "(a) Animation: ON" : "(a) Animation: OFF";
string interpolation = isInterpolationEnabled ? "(i) Interpolation: ON" : "(i) Interpolation: OFF";