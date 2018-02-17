#include <GL/gl.h>
#include <GL/glut.h>

float angle = 0;

float ftl = 10;
float fbl = 10;
float ftr = 10;
float fbr = 10;

float rtl = 10;
float rbl = 10;
float rtr = 10;
float rbr = 10;

void line(float a, float b, float c, float x, float y, float z) {
	glBegin(GL_LINES);
	glVertex3f(a, b, c);
	glVertex3f(a + x, b + y, c + z);
	glEnd();
}

void drawcube(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glRotatef(angle, 0, 1, 0);
	glutWireCube(20);

	glColor3f(1, 0, 0);
	glLineWidth(2.5);
	line(-10, 10, 10, ftl, -ftl, ftl);
	line(-10, -10, 10, fbl, fbl, fbl);
	line(10, 10, 10, -ftr, -ftr, ftr);
	line(10, -10, 10, -fbr, fbr, fbr);

	glColor3f(0, 0, 1);
	line(-10, 10, -10, rtl, -rtl, -rtl);
	line(-10, -10, -10, rbl, rbl, -rbl);
	line(10, 10, -10, -rtr, -rtr, -rtr);
	line(10, -10, -10, -rbr, rbr, -rbr);

	glFlush();
	glutSwapBuffers();
}

void mouse(int btn, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		if (btn == GLUT_LEFT_BUTTON) {
			angle = 1;
		} else if (btn == GLUT_RIGHT_BUTTON) {
			angle = -1;
		}
	} else {
		angle = 0;
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Glut rotate");
	glutMouseFunc(mouse);
	glutDisplayFunc(drawcube);
	glutIdleFunc(drawcube);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-30.0, 30.0, -30.0, 30.0, -30.0, 30.0);
	glRotatef(30.0, 1.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glRotatef(30, 0, 1, 0);
	glutMainLoop();
	return 0;
}
