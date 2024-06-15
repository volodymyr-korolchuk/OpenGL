#include "main.h"

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
    }

    if (key == 27) {
        exit(0);
    }

    if (key == 'c') {
        isGreyscale = !isGreyscale;
    }

    if (key == 'w') {
        isWire = !isWire;
    }

    if (key == 'i') {
        isInterpolationEnabled = !isInterpolationEnabled;
        if (isInterpolationEnabled) {
            glShadeModel(GL_FLAT);
        } else {
            glShadeModel(GL_SMOOTH);
        }
        interpolation = isInterpolationEnabled ? "(i) Interpolation: ON" : "(i) Interpolation: OFF";
    }

    if (key == 'a') {
        isAnimationEnabled = !isAnimationEnabled;
        animationEnabled = isAnimationEnabled ? "(a) Animation: ON" : "(a) Animation: OFF";
    }
    glutPostRedisplay();
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
    for (const char& c : interpolation) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (isOrtho) {
        glOrtho(-2, 2, -2, 2, NearZ, FarZ); 
    }
    else {
        gluPerspective(60.0, 1.0, NearZ, FarZ);
    }

    gluLookAt(3, 3, 3, 0, 0, 0, 0, 1, 0);

    if (isAnimationEnabled) {
        glRotatef(angle, 0.0, 1.0, 0.0);
    }

    if (isWire) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    glColor3f(0, 1, 0);
    gluBeginSurface(surfName);
        gluNurbsSurface(surfName, 8, knots, 8, knots, 4 * 3, 3, &ctrlPoints[0][0][0], 4, 4, GL_MAP2_VERTEX_3);

        gluBeginTrim(surfName);
            gluPwlCurve(surfName, 5, &edgePt[0][0], 2, GLU_MAP1_TRIM_2);
        gluEndTrim(surfName);

        gluBeginTrim(surfName);
            gluNurbsCurve(surfName, 8, curveKnots, 2, &curvePt[0][0], 4, GLU_MAP1_TRIM_2);
            gluPwlCurve(surfName, 3, &pwlPt[0][0], 2, GLU_MAP1_TRIM_2);
        gluEndTrim(surfName);
    gluEndSurface(surfName);

    glColor3f(1.0, 1.0, 1.0);
    glLoadIdentity();
    glDisable(GL_LIGHTING);
    displayControls();
    glEnable(GL_LIGHTING);

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); 
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

   
    // Point
    GLfloat pointLight[] = { 0.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightPosition[] = { 0.0f, -5.0f, 0.0f, 1.0f };
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, pointLight);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.02f);

    surfName = gluNewNurbsRenderer();
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
