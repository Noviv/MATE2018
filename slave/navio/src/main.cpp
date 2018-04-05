#include "net.h"
#include "sub.h"

int main() {
	auto& s = Sub::instance();
	XNetRecv net(s);

	while (true) {
		net.poll();
		s.update();
	}

	return 0;
}
