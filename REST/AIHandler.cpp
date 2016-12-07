#include "AIHandler.h"

void AIHandler::statusPost(const Request &request, ResponseWriter response) {
    string body = request.body();
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

void AIHandler::gameStartPost(const Request &request, ResponseWriter response) {
    string body = request.body();
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
    } catch (string& exc) {
        response.send(Code::Internal_Server_Error, exc);
        return;
    }

    NewGameDTO newGameDTO(m_beach.getState(), m_beach.getToken(), m_beach.getGameID());
    response.send(Code::Ok, newGameDTO.toJSON());
}

void AIHandler::gamePlayPost(const Request &request, ResponseWriter response) {
    auto gameID = request.param(":gameid").as<string>();
    if (!m_beach.isKnownGameID(gameID)) {
        response.send(Code::Bad_Request, "Invalid gameID.");
        return;
    }

    string body = request.body();
    Document doc;
    doc.Parse(body.c_str());

    if (!doc.HasMember("token") || !doc.HasMember("difficulty")
        || !doc.HasMember("player") || !doc.HasMember("board")) {
        response.send(Code::Bad_Request, "Invalid argument.");
        return;
    }

    Value& tokenValue = doc["token"];
    if (!m_beach.isGoodToken(tokenValue.GetString())) {
        response.send(Code::Unauthorized, "Invalid token.");
        return;
    }

    Value& difficultyValue = doc["difficulty"];
    Value& playerValue = doc["player"];
    Value& boardValue = doc["board"];
    try {
        Difficulty difficulty = Difficulty::getFromString(difficultyValue.GetString());
        Player player = Player::getFromString(playerValue.GetString());

        auto boardArray = boardValue.GetArray();
        int counter = 0;
        array<char, 50> board;
        for (auto it = boardArray.Begin();
             it != boardArray.End() && counter < 50;
             ++it, ++counter) {
            string s = it->GetString();
            board[counter] = s[0];
        }

        if (counter < 50) {
            response.send(Code::Bad_Request, "Board isn't a 50-char array.");
            return;
        }

        array<char, 50> responseBoard =
                m_beach.gamePlay(gameID, difficulty, player, board);

        MoveDTO moveDTO(m_beach.getToken(), difficulty, player, responseBoard);
        response.send(Code::Ok, moveDTO.toJSON());
    } catch (string& exc) {
        response.send(Code::Internal_Server_Error, exc);
        return;
    }
}

void AIHandler::gameEndPost(const Request &request, ResponseWriter response) {
    auto gameID = request.param(":gameid").as<string>();
    if (!m_beach.isKnownGameID(gameID)) {
        response.send(Code::Bad_Request, "Invalid gameID.");
        return;
    }

    string body = request.body();
    Document doc;
    doc.Parse(body.c_str());

    if (!doc.HasMember("token") || !doc.HasMember("winner")
        || !doc.HasMember("code")) {
        response.send(Code::Bad_Request, "invalid argument");
        return;
    }

    Value& tokenValue = doc["token"];
    if (!m_beach.isGoodToken(tokenValue.GetString())) {
        response.send(Code::Unauthorized, "invalid token");
        return;
    }

    Value& winnerValue = doc["winner"];
    Value& codeValue = doc["code"];
    try {
        Player winner = Player::getFromString(winnerValue.GetString());
        CodeEndGame codeEndGame = CodeEndGame::getFromString(codeValue.GetString());
        m_beach.gameEnded(gameID, winner, codeEndGame);
    } catch (string& exc) {
        response.send(Code::Internal_Server_Error, exc);
        return;
    }

    StatusDTO statusDTO(m_beach.getState(), m_beach.getToken());
    response.send(Code::Ok, statusDTO.toJSON());
}
