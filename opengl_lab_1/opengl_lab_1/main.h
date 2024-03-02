#include <GL/glut.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <GL/freeglut_ext.h>

using std::rand;
using std::vector;
using std::string;
using std::rand;
using std::srand;
using std::to_string;


const GLfloat PI = 3.14159265359;
const int MAX_POLYGON_COUNT = 10;
const GLfloat WINDOW_WIDTH = 1200;
const GLfloat WINDOW_HEIGHT = 800;

struct Point {
    GLfloat x;
    GLfloat y;
};

struct CustomPolygon {
    vector<Point> vertices;
    string name;
    GLfloat R, G, B;
};
 
void generatePolygons(int maxCount);
void drawPolygon(const CustomPolygon& polygon);
void generateNewState();
void processKeyboardInput(unsigned char key, int x, int y);
void erasePolygons(int value);
void display();
void reshape(GLint width, GLint height);
void init();