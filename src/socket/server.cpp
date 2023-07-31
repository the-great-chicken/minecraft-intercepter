
#include <socket/server.h>

#include <error/error.h>

using namespace MinecraftIntercepter;
using namespace MinecraftIntercepter::Socket;

/**
 * Socket STD
 */
void __close (int sockfd) {
    close(sockfd);
}
void __shutdown (int sockfd, int opt) {
    shutdown(sockfd, opt);
}
int __listen (int sockfd, int backlog) {
    return listen(sockfd, backlog);
}
int __accept (int __fd, sockaddr *__restrict__ __addr, socklen_t *__restrict__ __addr_len) {
    return accept(__fd, __addr, __addr_len);
}


ServerSocket::ServerSocket (int port) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
        Error::show_critical( Error::CREATE_SOCKET_ERROR );
    
    if (
        setsockopt(
            sockfd, SOL_SOCKET, 
            SO_REUSEADDR | SO_REUSEPORT,
            &opt, sizeof(opt)
        )
    ) Error::show_critical( Error::OPT_SOCKET_ERROR );

    address.sin_family      = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port        = htons(port);

    if (bind(sockfd, (struct sockaddr*)&address,
             sizeof(address))
        < 0)
        Error::show_critical( Error::BIND_SOCKET_ERROR );
}

bool ServerSocket::closed () {
    return sockfd < 0;
}
void ServerSocket::close () {
    if (new_socket != -1) {
        Error::show_warning( Error::PENDING_SOCKET_ERROR );

        __close(new_socket);
        new_socket = -1;
    }

    if (closed()) return ;

    __shutdown(sockfd, SHUT_RDWR);
    sockfd = -1;
}

ServerSocket::~ServerSocket () {
    close();
}

bool ServerSocket::listen () {
    if (new_socket != -1) return true;
    if (closed()) return false;

    if (__listen( sockfd, 3 ) < 0)
        Error::show_critical ( Error::LISTEN_SOCKET_ERROR );

    new_socket = __accept(sockfd, 
                  (struct sockaddr*)&address,
                  (socklen_t*)&addrlen);
    return new_socket >= 0;
}

int ServerSocket::accept () {
    if (new_socket == -1) return -1;

    int clientfd = new_socket;
    new_socket = -1;

    return clientfd; 
}
void ServerSocket::refuse () {
    if (new_socket == -1) return ;

    __close(new_socket);
    new_socket = -1;
}
