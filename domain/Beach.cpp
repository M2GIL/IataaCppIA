#include "Beach.h"

#include "tools/randomTextGenerator.h"

void Beach::generateNewGameID() {
    m_gameID = randomTextGenerator::getInstance()(10);
}

void Beach::newGameStarted(const Difficulty& difficulty, const Player& player) {
    generateNewGameID();
    toggleState();

    // A compléter si on a besoin de faire quelque chose au démarrage d'une nouvelle partie.
    // difficulty : la difficulté demandée
    // player : le joueur demandé
}

void
Beach::gameEnded(const string &gameID, Player winner, CodeEndGame codeEndGame) {
    if (m_gameID == gameID) {
        m_gameID = "";
        toggleState();

        // A compléter si on a besoin de faire quelque chose à la fin d'une partie.
        // gameID : l'ID de la partie terminée
        // winner : le joueur qui a gagné
        // codeEndGame : le code indiquant le type de fin de partie
    }
}
