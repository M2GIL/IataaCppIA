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
void AIHandler::statusGet(const Request &request, ResponseWriter response) {
    std::cout << "---" << std::endl;
    std::cout << "Status request received." << std::endl;

    auto query = request.query();
    // Check if request has token.
    if (!query.has("token")) {
        response.send(Code::Bad_Request, "Invalid arguments.");
        return;
    }

    // Get and check token.
    auto optionalToken = query.get("token");
    if (optionalToken.isEmpty()) {
        response.send(Code::Bad_Request, "Token is empty.");
        return;
    }
    string token = optionalToken.get();
    std::cout << "Token asked : " << token << std::endl;
    if (!m_beach.isGoodToken(token)) {
        response.send(Code::Unauthorized, "Invalid token.");
        return;
    }
    std::cout << "Token OK." << std::endl;

    // Returns the status.
    StatusDTO statusDTO(m_beach.getState(), m_beach.getToken());
    response.setMime(MIME(Application, Json));
    response.send(Code::Ok, statusDTO.toJSON());
}

/**
 * Indicates a new game to the system.
 */
void AIHandler::gameStartGet(const Request &request, ResponseWriter response) {
    std::cout << "---" << std::endl;
    std::cout << "Game start request received." << std::endl;

    auto query = request.query();
    // Get and check token.
    auto optionalToken = query.get("token");
    if (optionalToken.isEmpty()) {
        response.send(Code::Bad_Request, "Token is empty.");
        return;
    }
    string token = optionalToken.get();
    std::cout << "Token asked : " << token << std::endl;
    if (!m_beach.isGoodToken(token)) {
        response.send(Code::Unauthorized, "Invalid token.");
        return;
    }
    std::cout << "Token OK" << std::endl;

    // Get difficulty and player values.
    auto optionalDifficulty = query.get("difficulty");
    auto optionalPlayer = query.get("player");
    if (optionalDifficulty.isEmpty() || optionalPlayer.isEmpty()) {
        response.send(Code::Bad_Request, "Difficulty or player is empty.");
        return;
    }
    string difficultyStr = optionalDifficulty.get();
    std::cout << "Difficulty : " << difficultyStr << std::endl;
    string playerStr = optionalPlayer.get();
    std::cout << "Player : " << playerStr << std::endl;
    try {
        Difficulty difficulty = Difficulty::getFromString(difficultyStr);
        Player player = Player::getFromString(playerStr);
        // Indicates a new game to the system.
        m_beach.newGameStarted(difficulty, player);
    } catch (string& exc) {
        std::cerr << exc << std::endl;
        response.send(Code::Internal_Server_Error, exc);
        return;
    } catch (const char* exc) {
        std::cerr << exc << std::endl;
        response.send(Code::Internal_Server_Error, exc);
        return;
    }

    // Returns the response : the status, the token and a new gameID.
    NewGameDTO newGameDTO(m_beach.getState(), m_beach.getToken(), m_beach.getGameID());
    response.setMime(MIME(Application, Json));
    response.send(Code::Ok, newGameDTO.toJSON());
}

/**
 * Asks a new move to the system.
 */
void AIHandler::gamePlayGet(const Request &request, ResponseWriter response) {
    std::cout << "---" << std::endl;
    std::cout << "Game play request received." << std::endl;
    // Gets and checks the gameID.
    auto gameID = request.param(":gameid").as<string>();
    std::cout << "GameID : " << gameID << std::endl;
    if (!m_beach.isKnownGameID(gameID)) {
        response.send(Code::Bad_Request, "Invalid gameID.");
        return;
    }
    std::cout << "Known gameID." << std::endl;

    auto query = request.query();
    // Get and check token.
    auto optionalToken = query.get("token");
    if (optionalToken.isEmpty()) {
        response.send(Code::Bad_Request, "Token is empty.");
        return;
    }
    string token = optionalToken.get();
    std::cout << "Token asked : " << token << std::endl;
    if (!m_beach.isGoodToken(token)) {
        response.send(Code::Unauthorized, "Invalid token.");
        return;
    }
    std::cout << "Token OK" << std::endl;

    // Get difficulty, board and player values.
    auto optionalDifficulty = query.get("difficulty");
    auto optionalPlayer = query.get("player");
    auto optionalBoard = query.get("board");
    if (optionalDifficulty.isEmpty() || optionalPlayer.isEmpty() || optionalBoard.isEmpty()) {
        response.send(Code::Bad_Request, "Difficulty, board or player is empty.");
        return;
    }
    string difficultyStr = optionalDifficulty.get();
    std::cout << "Difficulty : " << difficultyStr << std::endl;
    string playerStr = optionalPlayer.get();
    std::cout << "Player : " << playerStr << std::endl;
    string boardStr = optionalBoard.get();
    // Check board size.
    if (boardStr.size() != 50) {
        response.send(Code::Bad_Request, "Board isn't 50 char long.");
        return;
    }

    try {
        Difficulty difficulty = Difficulty::getFromString(difficultyStr);
        Player player = Player::getFromString(playerStr);

        // We will fill an array to represent the board.
        vector<BoardSquareType> board;
        for (char& c : boardStr) {
            board.push_back(BoardSquareType::getFromChar(c));
        }

        // Gets the move from the system.
        vector<BoardSquareType> responseBoard =
                m_beach.gamePlay(gameID, difficulty, player, board);

        // Returns the move.
        MoveDTO moveDTO(m_beach.getToken(), difficulty, player, responseBoard);
        response.setMime(MIME(Application, Json));
        response.send(Code::Ok, moveDTO.toJSON());
    } catch (string& exc) {
        std::cerr << exc << std::endl;
        response.send(Code::Internal_Server_Error, exc);
        return;
    } catch (const char* exc) {
        std::cerr << exc << std::endl;
        response.send(Code::Internal_Server_Error, exc);
        return;
    }
}

/**
 * Indicates end of a game to the system.
 */
void AIHandler::gameEndGet(const Request &request, ResponseWriter response) {
    std::cout << "---" << std::endl;
    std::cout << "Game end request received." << std::endl;
    // Gets and checks the gameID.
    auto gameID = request.param(":gameid").as<string>();
    std::cout << "GameID : " << gameID << std::endl;
    if (!m_beach.isKnownGameID(gameID)) {
        response.send(Code::Bad_Request, "Invalid gameID.");
        return;
    }
    std::cout << "Known gameID." << std::endl;

    auto query = request.query();
    // Get and check token.
    auto optionalToken = query.get("token");
    if (optionalToken.isEmpty()) {
        response.send(Code::Bad_Request, "Token is empty.");
        return;
    }
    string token = optionalToken.get();
    std::cout << "Token asked : " << token << std::endl;
    if (!m_beach.isGoodToken(token)) {
        response.send(Code::Unauthorized, "Invalid token.");
        return;
    }
    std::cout << "Token OK" << std::endl;

    // Get winner and code values.
    auto optionalWinner = query.get("winner");
    auto optionalCode = query.get("code");
    if (optionalWinner.isEmpty() || optionalCode.isEmpty()) {
        response.send(Code::Bad_Request, "Winner or code is empty.");
        return;
    }
    string winnerStr = optionalWinner.get();
    std::cout << "Winner : " << winnerStr << std::endl;
    string codeStr = optionalCode.get();
    std::cout << "Code : " << codeStr << std::endl;
    try {
        Player winner = Player::getFromString(winnerStr);
        CodeEndGame codeEndGame = CodeEndGame::getFromString(codeStr);
        // Indicates to the system that a game ended.
        m_beach.gameEnded(gameID, winner, codeEndGame);
    } catch (string& exc) {
        std::cerr << exc << std::endl;
        response.send(Code::Internal_Server_Error, exc);
        return;
    } catch (const char* exc) {
        std::cerr << exc << std::endl;
        response.send(Code::Internal_Server_Error, exc);
        return;
    }

    // Returns the new status of the system.
    StatusDTO statusDTO(m_beach.getState(), m_beach.getToken());
    response.setMime(MIME(Application, Json));
    response.send(Code::Ok, statusDTO.toJSON());
}
