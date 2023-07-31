
#include <iostream>
#include <error/error.h>

using namespace std;

using namespace MinecraftIntercepter;

void Error::show_critical (Error error) {
        cout << error << "\n";
        exit(-1);
    }
void Error::show_warning (Error error) {
    cout << "WARNING: " << error << "\n";
}
