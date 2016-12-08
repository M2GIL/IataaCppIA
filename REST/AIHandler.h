#ifndef CHECKERS_REST_IA_C_CHECKERSHANDLER_H
#define CHECKERS_REST_IA_C_CHECKERSHANDLER_H

#include "pistache/router.h"
#include "pistache/endpoint.h"
#include "../domain/Beach.h"

#include <memory>

using Domain::Beach;
using Net::Http::Endpoint;
using Net::Tcp::Options;
using Net::Rest::Routes::Get;
using Net::Rest::Routes::Post;
using Net::Rest::Request;
using Net::Http::ResponseWriter;
using std::shared_ptr;
using std::make_shared;

/**
 * Declares REST services and their implementations.
 */
class AIHandler {
public:
    AIHandler(Net::Address addr) : m_server(make_shared<Endpoint>(addr)) {
    }

    /**
     * Initializes the endpoint and setup routes.
     * @param nbThreads the maximum number of threads used by the endpoint
     */
    void init(int nbThreads) {
        auto opts = Endpoint::options()
                .threads(nbThreads)
                .flags(Options::InstallSignalHandler);
        m_server->init(opts);
        setupRoutes();
    }

    /**
     * Starts the server.
     */
    void start() {
        m_server->setHandler(m_router.handler());
        m_server->serve();
    }

    /**
     * Shutdowns the server.
     */
    void shutdown() {
        m_server->shutdown();
    }

private:
    /**
     * Binds the routes to their implementations.
     */
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

    void statusPost(const Request&, ResponseWriter);

    void gameStartPost(const Request&, ResponseWriter);

    void gamePlayPost(const Request&, ResponseWriter);

    void gameEndPost(const Request&, ResponseWriter);

private:
    /**
     * Server.
     */
    shared_ptr<Endpoint> m_server;

    /**
     * Router.
     */
    Net::Rest::Router m_router;

    /**
     * Interface between IA implementation and REST services.
     */
    Beach m_beach;
};

#endif
