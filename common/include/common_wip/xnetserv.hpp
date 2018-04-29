#ifndef XNETSERV_HPP
#define XNETSERV_HPP

class XNetServ {
private:
	int lSock;
	int rSock;
	int port;

	struct sockaddr_in lAddr;
	struct sockaddr_in rAddr;

public:
	XNetServ(int p = 4123) : port(p) {

	}

	~XNetServ() {

	}
};

#endif
