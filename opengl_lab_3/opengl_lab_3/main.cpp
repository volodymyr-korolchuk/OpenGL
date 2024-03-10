#include <GL/glut.h>
#include <string>
#include <vector>

bool isOrtho = false;
bool isWire = false;
bool isAnimationEnabled = false;
bool isGreyscale = true;
bool isInterpolationEnabled = false; // Flag for interpolative coloring

const float NearZ = 1.0;
const float FarZ = 10.0;

float xmax = 2.5;
float xmin = -2.5;
float ymax = 2.5;
float ymin = -2.5;

float angle = 0.0;

std::string projectionMode = isOrtho ? "(o) Projection: Orthographic" : "(o) Projection: Perspective";
std::string animationEnabled = isAnimationEnabled ? "(a) Animation: ON" : "(a) Animation: OFF";
std::string wireMode = isWire ? "(f) Figure: Wire" : "(f) Figure: Solid";
std::string colorMode = isGreyscale ? "(c) Color: OFF" : "(c) Color: ON";
std::string colorModeText = isInterpolationEnabled ? "(i) Color Interpolation: ON" : "(i) Color Interpolation: OFF";

float getFactor(float angle) {
    if (angle >= 350) return 360;
    return (360 - angle) / 2000;
}

void idle() {
    float factor = getFactor(angle);
    angle = angle + factor >= 360 ? 0 : angle + factor;
    glutPostRedisplay();
}

void processKeyboardInput(unsigned char key, int, int) {
    if (key == 'o') {
        isOrtho = !isOrtho;
        projectionMode = isOrtho ? "(o) Projection: Orthographic" : "(o) Projection: Perspective";
        glutPostRedisplay();
    }

    if (key == 'f') {
        isWire = !isWire;
        wireMode = isWire ? "(f) Figure: Wire" : "(f) Figure: Solid";
        glutPostRedisplay();
    }

    if (key == 27) {
        exit(0);
    }

    if (key == 'a') {
        isAnimationEnabled = !isAnimationEnabled;
        animationEnabled = isAnimationEnabled ? "(a) Animation: ON" : "(a) Animation: OFF";
        glutPostRedisplay();
    }

    if (key == 'c') {
        isGreyscale = !isGreyscale;
        colorMode = isGreyscale ? "(c) Color: OFF" : "(c) Color: ON";
        glutPostRedisplay();
    }

    if (key == 'i') {
        isInterpolationEnabled = !isInterpolationEnabled;
        colorModeText = isInterpolationEnabled ? "(i) Color Interpolation: ON" : "(i) Color Interpolation: OFF";
        glutPostRedisplay();
    }
}

void drawTriangle(const GLfloat* v1, const GLfloat* v2, const GLfloat* v3, const GLfloat* c1, const GLfloat* c2, const GLfloat* c3) {
    glBegin(GL_TRIANGLES);
        glColor3fv(c1);
        glVertex3fv(v1);
        glColor3fv(c2);
        glVertex3fv(v2);
        glColor3fv(c3);
        glVertex3fv(v3);
    glEnd();
}

void drawOctahedron() {
    GLfloat vertices[6][3] = {
        {0.0, 1.0, 0.0},
        {1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0},
        {-1.0, 0.0, 0.0},
        {0.0, 0.0, -1.0},
        {0.0, -1.0, 0.0}
    };

    GLfloat colored[6][3] = {
        {1.0, 0.0, 0.0}, 
        {0.0, 1.0, 0.0}, 
        {0.0, 0.0, 1.0}, 
        {1.0, 1.0, 0.0}, 
        {1.0, 0.0, 1.0}, 
        {0.0, 1.0, 1.0}  
    };    
    
    GLfloat greyscale[6][3] = {
        {0.5, 0.5, 0.5}, 
        {0.3, 0.3, 0.3}, 
        {0.7, 0.7, 0.7}, 
        {0.2, 0.2, 0.2}, 
        {0.8, 0.8, 0.8}, 
        {0.4, 0.4, 0.4}  
    };

    GLfloat(*reference)[3] = isGreyscale ? greyscale : colored;
    
    drawTriangle(vertices[0], vertices[1], vertices[2], reference[0], reference[1], reference[2]);
    drawTriangle(vertices[0], vertices[2], vertices[3], reference[0], reference[2], reference[3]);
    drawTriangle(vertices[0], vertices[3], vertices[4], reference[0], reference[3], reference[4]);
    drawTriangle(vertices[0], vertices[4], vertices[1], reference[0], reference[4], reference[1]);
    drawTriangle(vertices[5], vertices[2], vertices[1], reference[5], reference[2], reference[1]);
    drawTriangle(vertices[5], vertices[3], vertices[2], reference[5], reference[3], reference[2]);
    drawTriangle(vertices[5], vertices[4], vertices[3], reference[5], reference[4], reference[3]);
    drawTriangle(vertices[5], vertices[1], vertices[4], reference[5], reference[1], reference[4]);
}

void displayControls() {
    glRasterPos3f(-0.9, -0.9, -1.0);
    for (const char& c : projectionMode) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glRasterPos3f(-0.9, -0.8, -1.0);
    for (const char& c : animationEnabled) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glRasterPos3f(-0.9, -0.7, -1.0);
    for (const char& c : wireMode) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glRasterPos3f(-0.9, -0.6, -1.0);
    for (const char& c : colorMode) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glRasterPos3f(-0.9, -0.5, -1.0);
    for (const char& c : colorModeText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glEnable(GL_LIGHTING);

    if (isOrtho) {
        glOrtho(xmin, xmax, ymin, ymax, NearZ, FarZ);
    }
    else {
        gluPerspective(45, 1.0, NearZ, FarZ);
    }

    gluLookAt(-1.0, 1.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    if (isAnimationEnabled) {
        glRotatef(angle, 0.0, 1.0, 1.0);
    }

    if (isWire) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        drawOctahedron();
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        drawOctahedron();
    }

    if (isInterpolationEnabled) {
        glShadeModel(GL_SMOOTH); 
    }
    else {
        glShadeModel(GL_FLAT); 
    }

    glColor3f(1.0, 1.0, 1.0);
    glDisable(GL_LIGHTING);
    glLoadIdentity();

    displayControls();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    GLfloat light_position0[] = { 0.0, 1.0, -1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Lab #3");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(processKeyboardInput);
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}
