#include "main.h"

float getFactor(float angle) {
    if (angle >= 350) return 360;
    return (360 - angle) / rotationSpeedFactor;
}

void idle() {
    float factor = getFactor(angle);
    angle = angle + factor >= 360 ? 0 : angle + factor;
    lightXPos += 0.01;
    if (lightXPos > 5) {
        lightXPos = -5;
    }

    if (isMovementEnabled) {
        cubeXPos += cubeXSpeed;
        cubeYPos += cubeYSpeed;
        cubeZPos += cubeZSpeed;

        if (cubeXPos <= -5 || cubeXPos >= 5) {
            cubeXSpeed *= -1;
        }
        if (cubeYPos <= -3 || cubeYPos >= 3) {
            cubeYSpeed *= -1;
        }
        if (cubeZPos <= -5 || cubeZPos >= 0) {
            cubeZSpeed *= -1;
        }
    }

    glutPostRedisplay();
}

void loadTexture(const char* filename) {
    int width, height, channels;

    unsigned char* image = stbi_load(filename, &width, &height, &channels, STBI_rgb_alpha);
    if (!image) {
        std::cerr << "Error loading texture: Could not load image." << std::endl;
        return;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    stbi_image_free(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void drawTexturedObject() {
    // Front face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f + cubeXPos, -1.0f + cubeYPos, 1.0f + cubeZPos);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f + cubeXPos, -1.0f + cubeYPos, 1.0f + cubeZPos);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f + cubeXPos, 1.0f + cubeYPos, 1.0f + cubeZPos);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f + cubeXPos, 1.0f + cubeYPos, 1.0f + cubeZPos);
    glEnd();

    // Back face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f + cubeXPos, -1.0f + cubeYPos, -1.0f + cubeZPos);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f + cubeXPos, -1.0f + cubeYPos, -1.0f + cubeZPos);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f + cubeXPos, 1.0f + cubeYPos, -1.0f + cubeZPos);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f + cubeXPos, 1.0f + cubeYPos, -1.0f + cubeZPos);
    glEnd();

    // Left face
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f + cubeXPos, -1.0f + cubeYPos, -1.0f + cubeZPos);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f + cubeXPos, -1.0f + cubeYPos, 1.0f + cubeZPos);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f + cubeXPos, 1.0f + cubeYPos, 1.0f + cubeZPos);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f + cubeXPos, 1.0f + cubeYPos, -1.0f + cubeZPos);
    glEnd();

    // Right face
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f + cubeXPos, -1.0f + cubeYPos, 1.0f + cubeZPos);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f + cubeXPos, -1.0f + cubeYPos, -1.0f + cubeZPos);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f + cubeXPos, 1.0f + cubeYPos, -1.0f + cubeZPos);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f + cubeXPos, 1.0f + cubeYPos, 1.0f + cubeZPos);
    glEnd();

    // Top face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f + cubeXPos, 1.0f + cubeYPos, -1.0f + cubeZPos);
    glVertex3f(1.0f + cubeXPos, 1.0f + cubeYPos, -1.0f + cubeZPos);
    glVertex3f(1.0f + cubeXPos, 1.0f + cubeYPos, 1.0f + cubeZPos);
    glVertex3f(-1.0f + cubeXPos, 1.0f + cubeYPos, 1.0f + cubeZPos);
    glEnd();

    // Bottom face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f + cubeXPos, -1.0f + cubeYPos, -1.0f + cubeZPos);
    glVertex3f(1.0f + cubeXPos, -1.0f + cubeYPos, -1.0f + cubeZPos);
    glVertex3f(1.0f + cubeXPos, -1.0f + cubeYPos, 1.0f + cubeZPos);
    glVertex3f(-1.0f + cubeXPos, -1.0f + cubeYPos, 1.0f + cubeZPos);
    glEnd();
}

void displayControls() {
    glRasterPos3f(-0.35, -0.27, -1.0);
    for (const char& c : fog) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glRasterPos3f(-0.35, -0.30, -1.0);
    for (const char& c : fogMode) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glRasterPos3f(-0.35, -0.33, -1.0);
    for (const char& c : rotationControls) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glRasterPos3f(-0.35, -0.36, -1.0);
    for (const char& c : lighting) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
}

void setupLighting() {
    // Ambient
    GLfloat ambientLight[] = { 0.0f, 0.1f, 0.2f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);

    // Point
    GLfloat pointLight[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    GLfloat lightPosition[] = { lightXPos, 2.0f, -2.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, pointLight);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.02f);

    // Spot light
    GLfloat spotLight[] = { 10.0f, 0.0f, 0.0f, 1.0f };
    GLfloat spotDirection[] = { 0.0f, -2.0f, -2.0f };
    GLfloat spotPosition[] = { lightXPos, 2.0f, 2.0f, 1.0f };
    glLightfv(GL_LIGHT2, GL_DIFFUSE, spotLight);
    glLightfv(GL_LIGHT2, GL_POSITION, spotPosition);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 50.0f);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDirection);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.2f);

    // Distant light
    GLfloat distantLight[] = { 0.0f, 10.0f, 10.0f, 1.0f };
    GLfloat distantDirection[] = { -1.0f, 4.0f, 5.0f, 0.0f };
    glLightfv(GL_LIGHT3, GL_DIFFUSE, distantLight);
    glLightfv(GL_LIGHT3, GL_POSITION, distantDirection);
}

void setupFog() {
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 0.0f);
    glFogf(GL_FOG_END, 10.0f);
    glHint(GL_FOG_HINT, GL_NICEST);

    GLfloat fogColor[4] = { 0.3f, 0.3f, 0.3f, 1.0f }; 

    glFogfv(GL_FOG_COLOR, fogColor);
}

void lightingMenuFunc(GLint menuItemNumber) {
    switch (menuItemNumber) {
    case 1:
        lightingSwitchArray[0] = !lightingSwitchArray[0];
        break;
    case 2:
        lightingSwitchArray[1] = !lightingSwitchArray[1];
        break;
    case 3:
        lightingSwitchArray[2] = !lightingSwitchArray[2];
        break;
    case 4:
        lightingSwitchArray[3] = !lightingSwitchArray[3];
        break;
    default:
        break;
    }

    lighting = lighting.substr(0, 10);

    for (size_t i = 0; i < sizeof(lightingSwitchArray); i++) {
        if (lightingSwitchArray[i]) {
            lighting.append(" " + lightNames[i]);
            glEnable(GL_ligthNames[i]);
        }
        else {
            glDisable(GL_ligthNames[i]);
        }
    }

    glutPostRedisplay();
}

void transformMenuFunc(GLint menuItemNumber) {
    switch (menuItemNumber) {
    case 1:
        isRotationEnabled = !isRotationEnabled;
        rotationControls = isRotationEnabled ? rotationControls.substr(0, 10).append("ON") : rotationControls.substr(0, 10).append("OFF");
        break;
    case 2:
        isMovementEnabled = !isMovementEnabled;
        cubeXPos = 0.0;
        cubeYPos = 0.0;
        cubeZPos = 0.0;
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

void speedMenuFunc(GLint menuItemNumber) {
    switch (menuItemNumber) {
    case 1:
        cubeXSpeed = cubeYSpeed = cubeZSpeed = 0.005;
        break;
    case 2:
        cubeXSpeed = cubeYSpeed = cubeZSpeed = 0.01;
        break;
    case 3:
        cubeXSpeed = cubeYSpeed = cubeZSpeed = 0.05;
        break; 
    case 4:
        rotationSpeedFactor = 5000;
        break;
    case 5:
        rotationSpeedFactor = 1000;
        break;
    case 6:
        rotationSpeedFactor = 200;
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

void fogMenuFunc(GLint menuItemNumber) {
    switch (menuItemNumber) {
    case 1:
        isFogEnabled = !isFogEnabled;
        if (isFogEnabled) {
            glEnable(GL_FOG);
        }
        else {
            glDisable(GL_FOG);
        }
        fog = isFogEnabled ? fog.substr(0, 5).append("ON") : fog.substr(0, 5).append("OFF");
        break;
    case 2:
        isFogLinOrExp = !isFogLinOrExp;
        if (isFogLinOrExp) {
            glFogi(GL_FOG_MODE, GL_LINEAR);
        } else {
            glFogi(GL_FOG_MODE, GL_EXP2);
        }
        break;
    default:
        break;
    }

    fog = fog.substr(0, 5);
    fog.append(isFogEnabled ? "ON" : "OFF");

    fogMode = fogMode.substr(0, 10);
    fogMode.append(isFogLinOrExp ? "Linear" : "Exponential");

    glutPostRedisplay();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);

    setupLighting();
    setupFog();

    loadTexture("D:/checkerboard.jpg");
    setupFog();

    // lighting submenu
    auto lightingSubMenu = glutCreateMenu(lightingMenuFunc);
    glutAddMenuEntry("Ambient", 1);
    glutAddMenuEntry("Point", 2);
    glutAddMenuEntry("Spot", 3);

    // transformation and speed submenu
    auto transformSubMenu = glutCreateMenu(transformMenuFunc);
    glutAddMenuEntry("Rotation ON/OFF", 1);
    glutAddMenuEntry("Movement ON/OFF", 2);
        
    auto speedSubMenu = glutCreateMenu(speedMenuFunc);

    glutAddMenuEntry("Movement Slow", 1);
    glutAddMenuEntry("Movement Medium", 2);
    glutAddMenuEntry("Movement Fast", 3);

    glutAddMenuEntry("Rotation Slow", 4);
    glutAddMenuEntry("Rotation Medium", 5);
    glutAddMenuEntry("Rotation Fast", 6);

    glutSetMenu(transformSubMenu);
    glutAddSubMenu("Speed", speedSubMenu);

    auto fogSubMenu = glutCreateMenu(fogMenuFunc);
    glutAddMenuEntry("ON/OFF", 1);
    glutAddMenuEntry("Linear/Exponential", 2);

    // main menu configuration
    auto mainMenu = glutCreateMenu(nullptr);
    glutSetMenu(mainMenu);
    glutAddSubMenu("Lighting", lightingSubMenu);
    glutAddSubMenu("Transofrm", transformSubMenu);
    glutAddSubMenu("Fog", fogSubMenu);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -8.0f);
    glRotatef(45, 1, -1, -1);

    if (isRotationEnabled) {
        glRotatef(angle, 0.0f, 1.0f, 0.0f);
    }

    glBindTexture(GL_TEXTURE_2D, textureID);
    glEnable(GL_TEXTURE_2D);
    drawTexturedObject();
    glDisable(GL_TEXTURE_2D);

    glLoadIdentity();
    glDisable(GL_LIGHTING);
    displayControls();
    glEnable(GL_LIGHTING);

    setupLighting();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("Lab #4");
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}
