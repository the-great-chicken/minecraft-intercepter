
#include <iostream>
#include <error/error.h>
#include <socket/server.h>

using namespace std;
using namespace MinecraftIntercepter;

int main () {
    Socket::ServerSocket serverSocket(25565);

    while (true) {
        serverSocket.listen();
        serverSocket.refuse();
    }
}
