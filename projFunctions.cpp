#include <hal/debug.h>
#include <hal/xbox.h>

#include "projFunctions.hpp"

void printErrorAndReboot(const char* msg) {
    debugPrint("%s", msg);
    debugPrint("Rebooting in 10 secs...");
    XSleep(10000);
    XReboot();
}