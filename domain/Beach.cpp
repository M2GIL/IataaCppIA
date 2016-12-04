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
