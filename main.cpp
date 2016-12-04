#include <iostream>
#include "pistache/router.h"
#include "REST/AIHandler.h"

using Net::Address;

int main() {
    Address addr(Net::Ipv4::any(), Net::Port(9080));
    AIHandler ch(addr);
    ch.init();
    ch.start();

    return 0;
}