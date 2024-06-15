#include "main.h"

float getFactor(float angle) {
    if (angle >= 350) return 360;
    return (360 - angle) / 5000;
}

void idle() {
    float factor = getFactor(angle);
    angle = angle + factor >= 360 ? 0 : angle + factor;
    lightXPos += 0.01;
    if (lightXPos > 5) {
        lightXPos = -5;
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
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glEnd();

    // Back face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, -1.0f); 
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glEnd();

    // Left face
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f); 
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glEnd();

    // Right face
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f); 
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glEnd();

    // Top face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f); 
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glEnd();

    // Bottom face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f); 
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
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

void processKeyboardInput(unsigned char key, int, int) {
    switch (key)
    {
    case '1':
        lightingSwitchArray[0] = !lightingSwitchArray[0];
        break;
    case '2':
        lightingSwitchArray[1] = !lightingSwitchArray[1];
        break;
    case '3':
        lightingSwitchArray[2] = !lightingSwitchArray[2];
        break;
    case '4':
        lightingSwitchArray[3] = !lightingSwitchArray[3];
        break; 
    case 27:
        exit(0);
        break;
    case 'a':
        isRotationEnabled = !isRotationEnabled;
        rotationControls = isRotationEnabled ? "(a) Rotation: ON" : "(a) Rotation: OFF";
        break;
    case 'f':
        isFogEnabled = !isFogEnabled;
        fog = std::to_string(lightXPos);
        if (isFogEnabled) {
            glEnable(GL_FOG);
        } else {
            glDisable(GL_FOG);
        }
        break;
    case 'g':
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

    fogMode = fogMode.substr(0, 14);
    fogMode.append(isFogLinOrExp ? "Linear" : "Exponential");

    lighting = lighting.substr(0, 22); 
    
    for (size_t i = 0; i < sizeof(lightingSwitchArray); i++) {
        if (lightingSwitchArray[i]) {
            lighting.append(" " + lightNames[i]);
            glEnable(GL_ligthNames[i]);
        } else {
            glDisable(GL_ligthNames[i]);
        }
    }
    glutPostRedisplay();
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

void setupFog() {
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 0.0f);
    glFogf(GL_FOG_END, 10.0f);
    glHint(GL_FOG_HINT, GL_NICEST);

    GLfloat fogColor[4] = { 0.3f, 0.3f, 0.3f, 1.0f }; // Fog color
    glFogfv(GL_FOG_COLOR, fogColor);
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
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Lab #4");
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(processKeyboardInput);
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}