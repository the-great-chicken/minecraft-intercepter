#pragma once

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

namespace MinecraftIntercepter::Socket {
    struct ServerSocket {
    private:
        int sockfd = -1;

        struct sockaddr_in address;
        int addrlen = sizeof(address);
        int opt     = 1;

        int new_socket = -1;
    public:
        ServerSocket (int port);

        bool closed ();

        bool listen();
        int accept();
        void refuse ();

        void close ();
        ~ServerSocket ();
    };
};
