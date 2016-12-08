#include "AIHandler.h"

#include "../DTO/StatusDTO.h"
#include "../DTO/NewGameDTO.h"
#include "../DTO/MoveDTO.h"
#include "../include/rapidjson/document.h"
#include "../domain/enumeration/BoardSquareType.h"

#include <vector>

using Dto::StatusDTO;
using Dto::MoveDTO;
using Dto::NewGameDTO;
using Net::Http::Code;
using std::string;
using std::vector;

using namespace rapidjson;

/**
 * Gets the status of the system.
 */
void AIHandler::statusPost(const Request &request, ResponseWriter response) {
    // Gets and parses the body of the request.
    string body = request.body();
    Document doc;
    doc.Parse(body.c_str());

    // Is token available ?
    if (!doc.HasMember("token")) {
        response.send(Code::Bad_Request, "Invalid arguments.");
        return;
    }

    // Is token the correct one ?
    Value& tokenValue = doc["token"];
    if (!m_beach.isGoodToken(tokenValue.GetString())) {
        response.send(Code::Unauthorized, "Invalid token.");
        return;
    }

    // Returns the status.
    StatusDTO statusDTO(m_beach.getState(), m_beach.getToken());
    response.send(Code::Ok, statusDTO.toJSON());
}

/**
 * Indicates a new game to the system.
 */
void AIHandler::gameStartPost(const Request &request, ResponseWriter response) {
    // Gets and parses the body of the request.
    string body = request.body();
    Document doc;
    doc.Parse(body.c_str());

    // We need a token, a difficulty and a player.
    if (!doc.HasMember("token") || !doc.HasMember("difficulty") || !doc.HasMember("player")) {
        response.send(Code::Bad_Request, "Invalid arguments.");
        return;
    }

    // Is token the correct one ?
    Value& tokenValue = doc["token"];
    if (!m_beach.isGoodToken(tokenValue.GetString())) {
        response.send(Code::Unauthorized, "Invalid token.");
        return;
    }

    // Gets difficulty and player values.
    Value& difficultyValue = doc["difficulty"];
    Value& playerValue = doc["player"];
    try {
        Difficulty difficulty = Difficulty::getFromString(difficultyValue.GetString());
        Player player = Player::getFromString(playerValue.GetString());
        // Indicates a new game to the system.
        m_beach.newGameStarted(difficulty, player);
    } catch (string& exc) {
        response.send(Code::Internal_Server_Error, exc);
        return;
    }

    // Returns the response : the status, the token and a new gameID.
    NewGameDTO newGameDTO(m_beach.getState(), m_beach.getToken(), m_beach.getGameID());
    response.send(Code::Ok, newGameDTO.toJSON());
}

/**
 * Asks a new move to the system.
 */
void AIHandler::gamePlayPost(const Request &request, ResponseWriter response) {
    // Gets and checks the gameID.
    auto gameID = request.param(":gameid").as<string>();
    if (!m_beach.isKnownGameID(gameID)) {
        response.send(Code::Bad_Request, "Invalid gameID.");
        return;
    }

    // Gets and parses the body of the request.
    string body = request.body();
    Document doc;
    doc.Parse(body.c_str());

    // We need a token, a difficulty, a player and a board.
    if (!doc.HasMember("token") || !doc.HasMember("difficulty")
        || !doc.HasMember("player") || !doc.HasMember("board")) {
        response.send(Code::Bad_Request, "Invalid arguments.");
        return;
    }

    // Is token the correct one ?
    Value& tokenValue = doc["token"];
    if (!m_beach.isGoodToken(tokenValue.GetString())) {
        response.send(Code::Unauthorized, "Invalid token.");
        return;
    }

    // Gets difficulty, player and board values.
    Value& difficultyValue = doc["difficulty"];
    Value& playerValue = doc["player"];
    Value& boardValue = doc["board"];
    try {
        Difficulty difficulty = Difficulty::getFromString(difficultyValue.GetString());
        Player player = Player::getFromString(playerValue.GetString());

        auto boardArray = boardValue.GetArray();
        // We will fill an array to represent the board.
        vector<BoardSquareType> board;
        for (auto it = boardArray.Begin(); it != boardArray.End(); ++it) {
            string s = it->GetString();
            board.push_back(BoardSquareType::getFromChar(s[0]));
        }

        // Board is not of good size (50).
        if (board.size() != 50) {
            response.send(Code::Bad_Request, "Board of incorrect size.");
            return;
        }

        // Gets the move from the system.
        vector<BoardSquareType> responseBoard =
                m_beach.gamePlay(gameID, difficulty, player, board);

        // Returns the move.
        MoveDTO moveDTO(m_beach.getToken(), difficulty, player, responseBoard);
        response.send(Code::Ok, moveDTO.toJSON());
    } catch (string& exc) {
        response.send(Code::Internal_Server_Error, exc);
        return;
    }
}

/**
 * Indicates end of a game to the system.
 */
void AIHandler::gameEndPost(const Request &request, ResponseWriter response) {
    // Gets and checks the gameID.
    auto gameID = request.param(":gameid").as<string>();
    if (!m_beach.isKnownGameID(gameID)) {
        response.send(Code::Bad_Request, "Invalid gameID.");
        return;
    }

    // Gets and parses the body of the request.
    string body = request.body();
    Document doc;
    doc.Parse(body.c_str());

    // We need a token, a winner and a end code.
    if (!doc.HasMember("token") || !doc.HasMember("winner")
        || !doc.HasMember("code")) {
        response.send(Code::Bad_Request, "invalid argument");
        return;
    }

    // Is token the correct one ?
    Value& tokenValue = doc["token"];
    if (!m_beach.isGoodToken(tokenValue.GetString())) {
        response.send(Code::Unauthorized, "invalid token");
        return;
    }

    // Gets winner and end code values.
    Value& winnerValue = doc["winner"];
    Value& codeValue = doc["code"];
    try {
        Player winner = Player::getFromString(winnerValue.GetString());
        CodeEndGame codeEndGame = CodeEndGame::getFromString(codeValue.GetString());
        // Indicates to the system that a game ended.
        m_beach.gameEnded(gameID, winner, codeEndGame);
    } catch (string& exc) {
        response.send(Code::Internal_Server_Error, exc);
        return;
    }

    // Returns the new status of the system.
    StatusDTO statusDTO(m_beach.getState(), m_beach.getToken());
    response.send(Code::Ok, statusDTO.toJSON());
}
