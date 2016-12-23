#include <iostream>
#include <fstream>
#include "pistache/router.h"
#include "REST/AIHandler.h"

string getTokenFromFile(const char fileName[6]);

using Net::Address;
using std::string;
using std::ifstream;

int main(int argc, char** argv) {
    string ip = "127.0.0.1";
    string port = "9080";
    if (argc > 1) {
        // Ip is given.
        ip = argv[1];
    }
    if (argc > 2) {
        // Port is given.
        port = argv[2];
    }

    Net::Port p((uint16_t) std::stoi(port));
    Address addr(ip.c_str(), p);
    AIHandler ch(addr);

    // Set token from file.
    ch.getBeach().setToken(getTokenFromFile("token"));

    ch.init(3);
    ch.start();
    ch.shutdown();

    return 0;
}

string getTokenFromFile(const char fileName[6]) {
    string token;
    ifstream file;
    file.open(fileName);
    file >> token;
    file.close();

    return token;
}