#ifndef CHECKERS_REST_IA_C_CHECKERSHANDLER_H
#define CHECKERS_REST_IA_C_CHECKERSHANDLER_H

#include "pistache/router.h"
#include "pistache/endpoint.h"
#include "../include/rapidjson/document.h"
#include "../domain/Beach.h"
#include "../DTO/StatusDTO.h"
#include "../DTO/NewGameDTO.h"
#include "../DTO/MoveDTO.h"

#include <memory>
#include <iostream>
#include <array>

using Net::Http::Endpoint;
using Net::Tcp::Options;
using Net::Rest::Routes::Get;
using Net::Rest::Routes::Post;
using Net::Rest::Request;
using Net::Http::ResponseWriter;
using Net::Http::Code;

using std::string;
using std::array;

using namespace rapidjson;

class AIHandler {
public:

    AIHandler(Net::Address addr) : m_server(std::make_shared<Endpoint>(addr)) {
    }

    void init() {
        auto opts = Endpoint::options()
                .threads(1)
                .flags(Options::InstallSignalHandler);
        m_server->init(opts);
        setupRoutes();
    }

    void start() {
        m_server->setHandler(m_router.handler());
        m_server->serve();
    }

    void shutdown() {
        m_server->shutdown();
    }

private:
    void setupRoutes() {
        Post(m_router, "/ai/status",
             Net::Rest::Routes::bind(&AIHandler::statusPost, this));
        Post(m_router, "/ai/games/start",
             Net::Rest::Routes::bind(&AIHandler::gameStartPost, this));
        Post(m_router, "/ai/games/play/:gameid",
             Net::Rest::Routes::bind(&AIHandler::gamePlayPost, this));
        Post(m_router, "/ai/games/end/:gameid",
             Net::Rest::Routes::bind(&AIHandler::gameEndPost, this));
    }

    void statusPost(const Request& request, ResponseWriter response);

    void gameStartPost(const Request& request, ResponseWriter response);

    void gamePlayPost(const Request& request, ResponseWriter response);

    void gameEndPost(const Request& request, ResponseWriter response);

private:
    std::shared_ptr<Endpoint> m_server;
    Net::Rest::Router m_router;

    Beach m_beach;
};

#endif
