#include <iostream>

#include "net.h"

int main() {
	XNetRecv net;

	while (1) {
		net.poll();
		cv::Mat mat = net.get_mat();
		imshow("img_recv", mat);
	}
}
