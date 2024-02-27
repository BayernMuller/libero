#include "TCPServer.h"
#include <exception>

namespace libero
{
    TCPServer::TCPServer(const char* ip, int port)
        : mIPAdress(ip), mPort(port)
    {
#ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 0), &wsaData))
        {
            char buf[100];
            strerror_s(buf, WSAGetLastError());
            throw std::runtime_error(buf);
        }
#endif // _WIN32

        ADDR server;
        mServerSock = socket(AF_INET, SOCK_STREAM, 0);
        server.sin_family = AF_INET;
        server.sin_port = htons(port);
        inet_pton(AF_INET, mIPAdress.c_str(), &server.sin_addr);

        if (bind(mServerSock, (struct sockaddr*)&server, sizeof(server)) == -1)
            throw std::runtime_error("bind error");

        if (listen(mServerSock, 5) == -1)
            throw std::runtime_error("listen error");
    }

    TCPServer::~TCPServer()
    {
#ifdef _WIN32
        close(mServerSock);
        WSACleanup();
#endif // _WIN32
    }

    std::pair<SOCKET, TCPServer::ADDR> TCPServer::Accept()
    {
        ADDR client;
        int nlen = sizeof(ADDR);
#ifdef _WIN32
        SOCKET sock = accept(mServerSock, (struct sockaddr*)&client, &nlen);
#else
        SOCKET sock = accept(mServerSock, (struct sockaddr*)&client, (socklen_t*)&nlen);
#endif
        if (sock == -1)
            throw std::runtime_error("accept error");
        return std::make_pair(sock, client);
    }

    void TCPServer::close(SOCKET sock)
    {
#ifdef _WIN32
        closesocket(sock);
#else
        ::close(sock);
#endif
    }
}