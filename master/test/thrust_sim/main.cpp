#include <iostream>
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

double d_x = 0;
double d_y = 0;
double d_z = 0;

double ftl = 1;
double fbl = 1;
double ftr = 1;
double fbr = 1;

double rtl = 1;
double rbl = 1;
double rtr = 1;
double rbr = 1;

bool keys[GLFW_KEY_LAST];

class XNetRecv {
private:
	boost::array<char, 1024> recv_buf;

	boost::asio::io_service io_serv;
	boost::asio::ip::udp::socket sock{ io_serv };
	boost::asio::ip::udp::endpoint endp;

	void async_bind() {
		auto recv_bind = boost::bind(
			&XNetRecv::recv,
			this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred);

		sock.async_receive_from(
			boost::asio::buffer(recv_buf),
			endp,
			recv_bind);
	}

public:
	XNetRecv() {
		sock.open(boost::asio::ip::udp::v4());
		sock.bind(boost::asio::ip::udp::endpoint(
			boost::asio::ip::address::from_string("127.0.0.1"),
			512));

		async_bind();
	}

	~XNetRecv() {
		sock.close();
	}

	void poll() {
		io_serv.poll();
	}

	void recv(const boost::system::error_code& error, size_t bytes) {
		if (error) {
			std::cout << "UDP error" << std::endl;
			return;
		}

		auto str = std::string(recv_buf.begin(), recv_buf.begin() + bytes);
		str = str.substr(1, str.length() - 2);

		std::vector<std::string> comps;
		boost::split(comps, str, boost::is_any_of(","));

		auto cvt = ::atof(comps[0].c_str());
		if (cvt == cvt) {
			d_x = cvt;
		}

		cvt = ::atof(comps[1].c_str());
		if (cvt == cvt) {
			d_y = cvt;
		}

		cvt = ::atof(comps[2].c_str());
		if (cvt == cvt) {
			d_z = cvt;
		}

		cvt = ::atof(comps[3].c_str());
		if (cvt == cvt) {
			ftl = cvt;
		}

		cvt = ::atof(comps[4].c_str());
		if (cvt == cvt) {
			fbl = cvt;
		}

		cvt = ::atof(comps[5].c_str());
		if (cvt == cvt) {
			ftr = cvt;
		}

		cvt = ::atof(comps[6].c_str());
		if (cvt == cvt) {
			fbr = cvt;
		}

		cvt = ::atof(comps[7].c_str());
		if (cvt == cvt) {
			rtl = cvt;
		}

		cvt = ::atof(comps[8].c_str());
		if (cvt == cvt) {
			rbl = cvt;
		}

		cvt = ::atof(comps[9].c_str());
		if (cvt == cvt) {
			rtr = cvt;
		}

		cvt = ::atof(comps[10].c_str());
		if (cvt == cvt) {
			rbr = cvt;
		}

		std::cout << str << std::endl;

		async_bind();
	}
};


#define line(x, y, z, a, b, c) glVertex3f(x, y, z);glVertex3f(x + a, y + b, z + c);

void drawCube() {
	static float xang = 45;
	static float yang = -180;
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

	glLineWidth(10);
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	line(1, 1, 1, -rtr, -rtr, rtr);
	line(-1, 1, 1, rtl, -rtl, rtl);
	line(-1, -1, 1, rbl, rbl, rbl);
	line(1, -1, 1, -rbr, rbr, rbr);
	glEnd();

	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	line(1, 1, -1, -ftr, -ftr, -ftr);
	line(-1, 1, -1, ftl, -ftl, -ftl);
	line(-1, -1, -1, fbl, fbl, -fbl);
	line(1, -1, -1, -fbr, fbr, -fbr);
	glEnd();

	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	line(0, 0, 0, 2 * d_x, 2 * d_y, 2 * d_z);
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
	XNetRecv net;

	if (!glfwInit()) {
		std::cout << "no glfw" << std::endl;
		return 1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWwindow* window = glfwCreateWindow(1024, 768, "thing", NULL, NULL);

	if (!window) {
		std::cout << "no window" << std::endl;
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
		net.poll();
		display(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
