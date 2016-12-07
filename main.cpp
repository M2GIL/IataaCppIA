#include <iostream>
#include "pistache/router.h"
#include "REST/AIHandler.h"

using Net::Address;

int main() {
    Address addr("127.0.0.1", Net::Port(9080));
    AIHandler ch(addr);
    ch.init();
    ch.start();
    ch.shutdown();

    return 0;
}