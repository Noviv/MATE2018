#include <stdio.h>

#include <GL/glut.h>

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutCreateWindow("red 3d");
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
