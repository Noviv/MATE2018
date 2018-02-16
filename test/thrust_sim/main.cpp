#include <GL/gl.h>
#include <GL/glut.h>

float angle=0.0;

void drawcube(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glutWireCube(20);

	glFlush();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
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
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(drawcube);
	glutIdleFunc(drawcube);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-30.0, 30.0, -30.0, 30.0, -30.0, 30.0);
	glRotatef(30.0, 1.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glutMainLoop();
	return 0;
}
