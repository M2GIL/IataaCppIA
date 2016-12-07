#include "Beach.h"

#include "tools/RandomTextGenerator.h"
#include "tools/Converter.h"

void Beach::generateNewGameID() {
    m_gameID = RandomTextGenerator::getInstance()(10);
}

void Beach::newGameStarted(const Difficulty& difficulty, const Player& player) {
    generateNewGameID();
    toggleState();

    // A compléter si on a besoin de faire quelque chose au démarrage d'une nouvelle partie.
    // difficulty : la difficulté demandée
    // player : le joueur demandé
}

array<char, 50>
Beach::gamePlay(const string& gameID, const Difficulty& difficulty,
                const Player& player, const array<char, 50>& board) {
    if (m_gameID == gameID) {
        // Conversion vers le format interne.
        /* InternalFormat iF = */Converter::convertToInternalFormat(board);

        // Reflexion de l'IA.
        // difficulty : la difficulté demandée
        // player : le joueur demandé
        // board : l'état du jeu
        /* InternalFormat iaBoard = iF.think(player, difficulty);*/

        // Conversion vers le format externe.
        return Converter::convertToExternalFormat(/*iaBoard*/);
    } else {
        // Partie inconnue, exception.
        throw "Unknown gameID : " + gameID;
    }
}

void
Beach::gameEnded(const string &gameID, const Player& winner,
                 const CodeEndGame& codeEndGame) {
    if (m_gameID == gameID) {
        m_gameID = "";
        toggleState();

        // A compléter si on a besoin de faire quelque chose à la fin d'une partie.
        // gameID : l'ID de la partie terminée
        // winner : le joueur qui a gagné
        // codeEndGame : le code indiquant le type de fin de partie
    } else {
        // Partie inconnue, exception.
        throw "Unknown gameID : " + gameID;
    }
}
