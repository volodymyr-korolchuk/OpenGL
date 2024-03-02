#include "main.h"

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	glutInitWindowPosition(400, 50);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Lab #2");
	init();

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	glutKeyboardFunc(processKeyboardInput);
	glutTimerFunc(REFRESH_RATE, transform, 0);

	glutMainLoop();

	return 0;
}

void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-1.0 * a, 1.0 * a, -1.0 * a, 1.0 * a);
}

void reshape(int w, int h) {
	glViewport(-1.0, 1.0, -1.0, 1.0);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawTrajectory(int coeff) {
	glBegin(GL_LINE_STRIP); 
		glColor3f(255.0f, 180.0f, 180.0f);
		for (float x = -1.0; x <= 1.0; x += 0.01) {
			float y = coeff * x * x;
			glVertex2f(x, y); 
		}
	glEnd(); 
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	gluOrtho2D(-1.0 * a, 1.0 * a, -1.0 * a, 1.0 * a);

	drawStatistics();
	drawGrid();
	drawTrajectory(a);

	glTranslatef(xPos, yPos, 0.0f);
	glScalef(size, size, 0.0f);

	glBegin(GL_QUADS);
		glColor3f(0.0f, 120.0f, 255.0f);
		glVertex3f(-0.05f, -0.05f, 0.0f);

		glColor3f(255.0f, 0.0f, 255.0f);
		glVertex3f(0.05f, -0.05f, 0.0f);

		glVertex3f(0.05f, 0.05f, 0.0f);

		glColor3f(0.0f, 0.0f, 255.0f);
		glVertex3f(-0.05f, 0.05f, 0.0f);
	glEnd();

	glutSwapBuffers();
}

void processKeyboardInput(unsigned char key, int, int) {
	switch (key) {
	case 'w':
		k += k < 10.0 ? 1.0 : 0.0;
		break;
	case 'q':
		k -= k > 1.0 ? 1.0 : 0.0;
		break;
	case 's':
		a += a < 5.0 ? 1.0 : 0.0;
		break;
	case 'a':
		a -= a > 1.0 ? 1.0 : 0.0;
		break;
	case 'x':
		speed += speed < 0.07 ? 0.01 : 0.0;
		break;
	case 'z':
		speed -= speed > 0.01 ? 0.01 : 0.0;
		break;
	default:
		break;
	}
}

float mapValue(float value, float n) {
	return ((value + 1) * (n - 1) / 2) + 1;
}

void transform(int) {
	glutTimerFunc(REFRESH_RATE, transform, 0);

	switch (direction) {
	case Direction::FORWARD:
		if (xPos < 1.0f) {
			xPos += speed;
			yPos = a * pow(xPos, 2);
		} else {
			direction = Direction::BACKWARDS;
		}
		break;
	case Direction::BACKWARDS:
		if (xPos > -1.0f) {
			xPos -= speed;
			yPos = a * pow(xPos, 2);
		} else {
			direction = Direction::FORWARD;
		}
		break;
	default:
		break;
	}

	size = mapValue(xPos, k);

	glutPostRedisplay();
}

void drawStatistics() {
	glColor3f(255.0f, 255.0f, 255.0f);

	glRasterPos2f(0.6 * a, -0.60 * a);
	for (char c : "y: " + to_string(yPos).substr(0, 4)) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}

	glRasterPos2f(0.6 * a, -0.65 * a);
	for (char c : "x: " + to_string(xPos).substr(0, 4)) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}

	glRasterPos2f(0.6 * a, -0.70 * a);
	for (char c : "size: " + to_string(size).substr(0, 4)) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}

	glRasterPos2f(0.6 * a, -0.80 * a);
	for (char c : "(q, w) k: " + to_string(k).substr(0,4)) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}

	glRasterPos2f(0.6 * a, -0.85 * a);
	for (char c : "(a, s) a: " + to_string(a).substr(0, 4)) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}

	glRasterPos2f(0.6 * a, -0.90 * a);
	for (char c : "(z, x) speed: " + to_string(speed * 100).substr(0, 1)) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}
}

void drawGrid() {
	glBegin(GL_LINES);
		glColor3f(0, 255, 0);
		glVertex3f(0.0, -1.0 * a, 0.0);
		glVertex3f(0.0, 1.0 * a, 0.0);
	glEnd();

	glBegin(GL_LINES);
		glColor3f(0, 255, 0);
		glVertex3f(-1.0 * a, 0.0, 0.0);
		glVertex3f(1.0 * a, 0.0, 0.0);
	glEnd();
}

