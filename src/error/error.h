#pragma once

#include <string>

using namespace std;

namespace MinecraftIntercepter::Error {
    using Error = string;

    const Error UNKNOWN_ERROR = " > Unexpected error";

    const Error CREATE_SOCKET_ERROR = " > Could not create socket";
    const Error OPT_SOCKET_ERROR    = " > Could not set options for socket";
    const Error BIND_SOCKET_ERROR   = " > Could not bind socket to address";
    const Error LISTEN_SOCKET_ERROR = " > Could not listen for incoming connection";

    const Error PENDING_SOCKET_ERROR = "Closed pending socket";

    void show_critical (Error error);
    void show_warning  (Error error);
};
