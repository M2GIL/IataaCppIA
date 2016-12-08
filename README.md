# IataaCppIA

Greffon pour les IA pour se brancher à un serveur IAtaa.

## Structures de données

Des structures de données sont prévues pour les échanges entre la plateforme
et l'IA. Elles suivent les conventions suivantes :

    PLAYER {
      J1, // PLAYER 1, blanc
      J2, // PLAYER 2, noir
      DRAW // Aucun des joueurs
    }

    BOARD_SQUARE_TYPE {
      EMPTY, // '0'
      BLACK_PAWN, // '1'
      BLACK_DRAUGHT, // '2'
      WHITE_PAWN, // '3'
      WHITE_DRAUGHT // '4'
    }

    DIFFICULTY {
      EASY, // Facile
      MEDIUM, // Moyen
      HARD // Difficile
    }

    CODE_ENDGAME {
      TIMEOUT, // Timeout
      SURRENDER, // Rédition
      CLASSICAL // Classique
    }

    STATUS {
      BUSY, // Occupé
      AVAILABLE // Disponible
    }

    BOARD {
      50 characters array // Plateau de jeu
    }

## Services REST proposés

Le greffon permet de proposer un certain nombre de services REST.

### POST /ai/status  
Permet d'accéder à l'état de l'IA.

    Input : {"token": token}
    Output : {"token": token, "status": STATUS }
    Error :
        200 -> OK
        401 -> "Invalid token."
        400 -> "Invalid arguments."

### POST /ai/games/start/
Indique à l'IA le début d'une partie, récupère un ID de partie.

    Input : {"token":token, "difficulty": DIFFICULTY, "player": PLAYER}
    Output : {"token": token, "status": STATUS, "game_id": token de partie}
    Error :
        200 -> OK
        401 -> "Invalid token."
        400 -> "Invalid arguments."

### POST /ai/games/play/:game_id
Demande à l'IA de jouer un coup et le récupère (dans "board").

    Input : {"token":token, "difficulty": DIFFICULTY, "player": PLAYER, "board": BOARD}
    Output : {"token":token, "difficulty": DIFFICULTY, "player": PLAYER, "board": BOARD}
    Error :
        200 -> OK
        401 -> "Invalid token."
        400 -> "Invalid arguments."

### POST /ai/games/end/:game_id
Indique à l'IA la fin d'une partie.

    Input : {"token": token, "winner": PLAYER, "code": CODE_ENDGAME}
    Output : {"token": token, "status": STATUS }
    Error :
        200 -> OK
        401 -> "Invalid token."
        400 -> "Invalid arguments."

## Installation et personnalisation

### Pistache

Pistache est un framework moderne et élégant HTTP et REST pour C++.

Ses sources se trouvent à https://github.com/oktal/pistache.

Sa documentation se trouve http://pistache.io.

Pour l'installer, il suffit de suivre les étapes situées à http://pistache.io/quickstart#installing-pistache.
Il n'est compatible qu'avec les systèmes Unix, excepté MacOS.

### Rapidjson

Rapidjson est un parser et un generateur JSON pour C++.

Ses source se trouvent à https://github.com/miloyip/rapidjson.

Il ne nécessite pas d'installation puisqu'il est header only et intégré à ce
projet.

### Personnalisation du code

La grande majorité du code doit rester telle quelle.

Vous devez compléter au minimum ```gamePlay``` (de ```Beach.cpp```) et les
méthodes de ```Tool::Converter``` pour que tout soit fonctionnel.

Vous trouverez ci-dessous la liste de toutes les méthodes paramétrables.

Dans ```Beach.cpp``` :
* La méthode ```newGameStarted``` peut être paramétrée à votre guise. Elle est appelée automatiquement au démarrage d'une nouvelle partie.  
Elle reçoit en paramètre la difficulté de la nouvelle partie ainsi que le joueur que votre IA incarnera.
* La méthode ```gamePlay``` doit contenir l'appel à votre IA pour décider du prochain coup.  
Elle est décomposée en 3 étapes :
    * Conversion du format d'entrée vers votre format interne (```Tool::Converter::convertToInternalFormat(board)```)
    * Calcul du prochain coup
    * Conversion du coup calculé de votre format interne vers le format de sortie (```Tool::Converter::convertToExternalFormat(calculatedMove)```)  
Elle reçoit en paramètre l'ID de la partie sur laquelle jouer, la difficulté demandée, le joueur qui doit jouer et l'état du plateau de jeu.
* La méthode ```gameEnded``` est appelée automatiquement lorsqu'une partie se termine.  
Elle reçoit en paramètre l'ID de la partie terminée, le joueur qui a gagné et le code de fin de partie.

Dans ```Converter.h``` et ```Converter.cpp``` :
* La méthode ```convertToInternalFormat``` est utilisée pour convertir un plateau de jeu depuis le format externe (un tableau de 50 cases de ```BoardSquareType```) vers votre format interne, compréhensible pour l'IA.  
Pensez à changer le type de retour de ```void``` vers votre type interne.
* La méthode ```convertToExternalFormat``` permet l'inverse : elle convertit un plateau de jeu depuis votre format interne vers le format externe.  
Pensez donc à prendre en paramètre une référence constante vers votre format interne, pour ensuite la convertir vers un tableau de 50 cases de ```BoardSquareType```.

### CMakeList

Un CMakeList se trouve dans ce projet. Le seul ajout notable est la
dépendance à *net_static* et *pthread*, nécessaires pour Pistache.

Puisque le code de ce projet sera intégré à votre projet, il est
nécessaire de le compiler en même temps que celui de votre IA.
