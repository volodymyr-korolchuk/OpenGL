#include "main.h"

vector<CustomPolygon> polygons;

int main(int argc, char** argv) {
    srand((unsigned)time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(150, 10);
    glutCreateWindow("Lab #1");
    init();

    generatePolygons(MAX_POLYGON_COUNT);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(processKeyboardInput);

    glutMainLoop();
    return 0;
}

void reshape(GLint width, GLint height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, width, height, 0);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

int getRandomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

float getRandomFloat(float min, float max) {
    GLfloat randomFraction = (GLfloat)(std::rand()) / RAND_MAX;
    return min + randomFraction * (max - min);
}

void generatePolygons(int maxCount) {
    polygons.clear();

    int polygonCount = getRandomInt(1, maxCount);
    const int width = glutGet(GLUT_WINDOW_WIDTH);
    const int height = glutGet(GLUT_WINDOW_HEIGHT);

    for (int i = 0; i < polygonCount; ++i) {
        int sides = getRandomInt(3, 6);
        CustomPolygon polygon;

        polygon.name = "Polygon " + to_string(i + 1);;
        polygon.R = getRandomFloat(0.0f, 1.0f);
        polygon.B = getRandomFloat(0.0f, 1.0f);
        polygon.G = getRandomFloat(0.0f, 1.0f);

        GLfloat offset = 80.0f;

        GLfloat radius = getRandomFloat(50, 150);
        GLfloat centerX = getRandomFloat(radius, width - radius - offset);
        GLfloat centerY = getRandomFloat(radius, height - radius - offset);

        GLfloat angleIncrement = 360.0f / sides;

        for (int j = 0; j < sides; ++j) {
            Point p;
            p.x = (centerX + radius * cos(angleIncrement * j * PI / 180.0));
            p.y = (centerY + radius * sin(angleIncrement * j * PI / 180.0));

            polygon.vertices.push_back(p);
        }

        polygons.push_back(polygon);
    }
}

void drawPolygon(const CustomPolygon& polygon) {
    glColor3f(polygon.R, polygon.G, polygon.B);

    glBegin(GL_POLYGON);
    for (const Point& p : polygon.vertices) {
        glVertex2i(p.x, p.y);
    }
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2f(polygon.vertices.front().x, polygon.vertices.front().y);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)(polygon.name.c_str()));
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (const auto& poly : polygons) {
        drawPolygon(poly);
    }

    glutSwapBuffers();
}

void erasePolygons(int value) {
    if (polygons.size() >= 1) {
        auto lastElement = polygons.back();

        if (!lastElement.name.empty()) {
            polygons.back().name.clear();
            glutPostRedisplay();
        } else {
            polygons.pop_back();
            glutPostRedisplay();
        }

        glutTimerFunc(500, erasePolygons, 0);
    }
}

void generateNewState() {
    generatePolygons(MAX_POLYGON_COUNT);
    glutPostRedisplay();
}

void processKeyboardInput(unsigned char key, int x, int y) {
    if (key == ' ') {
        erasePolygons(0);
    }
    else if (key == 'n') {
        generateNewState();
    }
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
}
