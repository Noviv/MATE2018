#ifndef XNET_H
#define XNET_H

#include <iostream>
#include <string>

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

class XNet {
   private:
    boost::system::error_code error;
    boost::asio::io_service io_serv;
    boost::asio::ip::udp::socket sock;
    boost::asio::ip::udp::endpoint endp;

   public:
    XNet(std::string ip, unsigned port)
        : sock(io_serv), endp(boost::asio::ip::address::from_string(ip), port) {
        sock.open(boost::asio::ip::udp::v4());
    }

    ~XNet() { sock.close(); }

    void send(std::string data) {
        sock.send_to(boost::asio::buffer(data, data.size()), endp);
    }
};

class XNetRecv {
   private:
    std::function<void(std::string)> callback;
    boost::array<char, 1024> recv_buf;
    boost::asio::io_service io_serv;
    boost::asio::ip::udp::socket sock{io_serv};
    boost::asio::ip::udp::endpoint endp;

    void async_bind() {
        auto recv_bind =
            boost::bind(&XNetRecv::recv, this, boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred);

        sock.async_receive_from(boost::asio::buffer(recv_buf), endp, recv_bind);
    }

    void recv(const boost::system::error_code& error, size_t sz) {
        if (error) {
            std::cout << "UDP error" << std::endl;
            return;
        }
        auto str = std::string(recv_buf.begin(), recv_buf.begin() + sz);
        callback(str);
        async_bind();
    }

   public:
    XNetRecv(std::string ip,
             int port,
             std::function<void(const std::string&)> cb)
        : callback(cb) {
        sock.open(boost::asio::ip::udp::v4());
        sock.bind(boost::asio::ip::udp::endpoint(
            boost::asio::ip::address::from_string(ip), port));

        async_bind();
    }

    ~XNetRecv() { sock.close(); }

    void poll() { io_serv.poll(); }
};

#endif
