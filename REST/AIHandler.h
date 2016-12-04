#ifndef CHECKERS_REST_IA_C_CHECKERSHANDLER_H
#define CHECKERS_REST_IA_C_CHECKERSHANDLER_H

#include "pistache/router.h"
#include "pistache/endpoint.h"
#include "../include/rapidjson/document.h"
#include "../domain/Beach.h"
#include "../DTO/StatusDTO.h"
#include "../DTO/NewGameDTO.h"

#include <memory>
#include <iostream>

using Net::Http::Endpoint;
using Net::Tcp::Options;
using Net::Rest::Routes::Get;
using Net::Rest::Routes::Post;
using Net::Rest::Request;
using Net::Http::ResponseWriter;
using Net::Http::Code;

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
        Post(m_router, "/ai/status", Net::Rest::Routes::bind(&AIHandler::statusPost, this));
        Post(m_router, "/ai/games/start", Net::Rest::Routes::bind(&AIHandler::gameStartPost, this));
    }

    void statusPost(const Request& request, ResponseWriter response) {
        std::string body = request.body();
        Document doc;
        doc.Parse(body.c_str());

        if (!doc.HasMember("token")) {
            response.send(Code::Bad_Request, "invalid argument");
            return;
        }

        Value& tokenValue = doc["token"];
        if (!m_beach.isGoodToken(tokenValue.GetString())) {
            response.send(Code::Unauthorized, "invalid token");
            return;
        }

        StatusDTO statusDTO(m_beach.getState(), m_beach.getToken());
        response.send(Code::Ok, statusDTO.toJSON());
    }

    void gameStartPost(const Request& request, ResponseWriter response) {
        std::string body = request.body();
        Document doc;
        doc.Parse(body.c_str());

        if (!doc.HasMember("token") || !doc.HasMember("difficulty") || !doc.HasMember("player")) {
            response.send(Code::Bad_Request, "invalid argument");
            return;
        }

        Value& tokenValue = doc["token"];
        if (!m_beach.isGoodToken(tokenValue.GetString())) {
            response.send(Code::Unauthorized, "invalid token");
            return;
        }

        Value& difficultyValue = doc["difficulty"];
        Value& playerValue = doc["player"];
        try {
            Difficulty difficulty = Difficulty::getFromString(difficultyValue.GetString());
            Player player = Player::getFromString(playerValue.GetString());
            m_beach.newGameStarted(difficulty, player);
        } catch (std::string& exc) {
            response.send(Code::Internal_Server_Error, exc);
            return;
        }

        NewGameDTO newGameDTO(m_beach.getState(), m_beach.getToken(), m_beach.getGameID());
        response.send(Code::Ok, newGameDTO.toJSON());
    }

private:
    std::shared_ptr<Endpoint> m_server;
    Net::Rest::Router m_router;

    Beach m_beach;
};

#endif
