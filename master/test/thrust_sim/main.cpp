#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <boost/asio.hpp>

float ftl = 10;
float fbl = 10;
float ftr = 10;
float fbr = 10;

float rtl = 10;
float rbl = 10;
float rtr = 10;
float rbr = 10;

bool keys[GLFW_KEY_LAST];

#define line(x, y, z, a, b, c) glVertex3f(x, y, z);glVertex3f(x + a, y + b, z + c);

void drawCube() {
	static float xang = 45;
	static float yang = 45;
	if (keys[GLFW_KEY_A]) {
		yang--;
	} else if (keys[GLFW_KEY_D]) {
		yang++;
	}
	if (keys[GLFW_KEY_W]) {
		xang--;
	} else if (keys[GLFW_KEY_S]) {
		xang++;
	}
	glRotatef(xang, 1, 0, 0);
	glRotatef(yang, 0, 1, 0);

	glLineWidth(1);

	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(2, 0, 0);
	glEnd();

	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 2, 0);
	glEnd();

	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 2);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_LINES);

	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, -1);

	glVertex3f(1, 1, 1);
	glVertex3f(1, -1, 1);

	glVertex3f(1, 1, 1);
	glVertex3f(-1, 1, 1);

	glVertex3f(-1, -1, -1);
	glVertex3f(-1, -1, 1);

	glVertex3f(-1, -1, -1);
	glVertex3f(-1, 1, -1);

	glVertex3f(-1, -1, -1);
	glVertex3f(1, -1, -1);
	
	glVertex3f(1, -1, -1);
	glVertex3f(1, 1, -1);

	glVertex3f(1, -1, -1);
	glVertex3f(1, -1, 1);

	glVertex3f(-1, 1, -1);
	glVertex3f(1, 1, -1);

	glVertex3f(-1, -1, 1);
	glVertex3f(-1, 1, 1);

	glVertex3f(-1, 1, 1);
	glVertex3f(-1, 1, -1);

	glVertex3f(-1, -1, 1);
	glVertex3f(1, -1, 1);
 
	glEnd();

	glLineWidth(5);
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	line(1, 1, 1, -1, -1, 1);
	line(-1, 1, 1, 1, -1, 1);
	line(-1, -1, 1, 1, 1, 1);
	line(1, -1, 1, -1, 1, 1);
	glEnd();

	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	line(1, 1, -1, -1, -1, -1);
	line(-1, 1, -1, 1, -1, -1);
	line(-1, -1, -1, 1, 1, -1);
	line(1, -1, -1, -1, 1, -1);
	glEnd();
}

void display(GLFWwindow* window) {
	GLint width, height;
	glfwGetWindowSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION_MATRIX);
	glLoadIdentity();
	gluPerspective(60, (double) width / height, .1, 100);

	glMatrixMode(GL_MODELVIEW_MATRIX);
	glTranslatef(0, 0, -5);

	drawCube();

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
	keys[key] = action == GLFW_PRESS || action == GLFW_REPEAT;
}

int main(int argc, char **argv) {
	if (!glfwInit()) {
		printf("no glfw\n");
		return 1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWwindow* window = glfwCreateWindow(1024, 768, "thing", NULL, NULL);

	if (!window) {
		printf("no window\n");
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, keyboard);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	while (!glfwWindowShouldClose(window)) {
		display(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
