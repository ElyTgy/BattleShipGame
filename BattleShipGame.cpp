#include <iostream>
#include <cctype>
//#include "Utils.h"

enum Utils
{
    BoardSize = 10,
    NumShips = 5,
    PlayerNameSize = 8,
    MaxShipSize = ShipSize::AirCraftCarrierSize
};

enum ShipSize
{
    AirCraftCarrierSize = 5,
    BattleShipSize = 4,
    CruiserSize = 3,
    DestroyerSize = 3,
    SubmarineSize = 2
};
enum ShipTypes
{
    ST_NONE = 0,
    ST_AIRCRAFT_CARRIER,
    ST_BATTLESHIP,
    ST_CRUISER,
    ST_DESTROYER,
    ST_SUBMARINE
};
struct ShipPosition
{
    int col;
    int row;
};
enum ShipOrientation
{
    Horizontal = 0,
    Vertical
};
struct Ship
{
    ShipTypes type;
    int shipSize;
    ShipPosition shipGridPos;
    ShipOrientation orientation;
};

enum GuessState
{
    GT_NONE = 0,
    GT_MISS,
    GT_HIT
};
struct ShipSlot
{
    ShipTypes shipType;
    bool isHit;
};

struct Player
{
    char PlayerName[PlayerNameSize];
    Ship ships[MaxShipSize];
    GuessState guessBoard[BoardSize][BoardSize];
    ShipSlot shipBoard[BoardSize][BoardSize];
};

const char INPUTERROR[] = "Input error try again";

char GetCharacter(const char* prompt, const char* error)
{
    char input;
    bool inputFailure;

    do {

        inputFailure = false;
        std::cout << prompt;

        std::cin >> input;

        if (std::cin.fail())
        {
            std::cin.ignore(256, '\n');
            std::cin.clear();
            std::cout << error << std::endl;
            inputFailure = true;
        }
        else
        {
            std::cin.ignore(256, '\n');
            if (std::isalpha(input))
            {
                input = std::tolower(input);
            }
            else
            {
                std::cout << error << std::endl;
                inputFailure = true;
            }
        }

    } while (inputFailure);

    return input;
}
char GetCharacter(const char* prompt, const char* error, const char validInput[], int validInputLength)
{
    char input;
    bool inputFailure = false;

    do
    {

        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail())
        {
            std::cin.ignore(256, '\n');
            std::cin.clear();
            std::cout << error << std::endl;
            inputFailure = true;
        }
        else
        {
            std::cin.ignore(256, '\n');

            input = std::tolower(input);

            for (int i = 0; i < validInputLength; ++i)
            {
                if (input == validInput[i])
                {
                    return input;
                }
            }

            std::cout << error << std::endl;
            inputFailure = true;
        }

    } while (inputFailure);

    return ' ';
}
int GetInt(const char* prompt, const char* error, const int validInput[], int validInputLength)
{
    int input;
    bool inputFailure = false;

    do
    {

        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cout << error << std::endl;
            inputFailure = true;
        }
        else
        {
            for (int i = 0; i < validInputLength; ++i)
            {
                if (input == validInput[i])
                {
                    return input;
                }
            }

            std::cout << error << std::endl;
            inputFailure = true;
        }

    } while (inputFailure);

    return ' ';
}

void InitPlayer(Player& player, const char* name)
{
    if (name != nullptr && strlen(name) > 0)
    {
        strcpy(player.PlayerName, name);
    }

    InitShip(player.ships[0], AirCraftCarrierSize, ST_AIRCRAFT_CARRIER);
    InitShip(player.ships[1], BattleShipSize, ST_BATTLESHIP);
    InitShip(player.ships[2], CruiserSize, ST_CRUISER);
    InitShip(player.ships[3], DestroyerSize, ST_DESTROYER);
    InitShip(player.ships[4], SubmarineSize, ST_SUBMARINE);


}
void InitShip(Ship& ship, int shipSize, ShipTypes type)
{
    ship.type = ST_AIRCRAFT_CARRIER;
    ship.shipSize = AirCraftCarrierSize;
    ship.shipGridPos.row = 0;
    ship.shipGridPos.col = 0;
    ship.orientation = Horizontal;
}
const char* GetShipName(ShipTypes type)
{
    if (type == ST_AIRCRAFT_CARRIER)
    {
        return "airecraft carrier";
    }
    else if (type == ST_BATTLESHIP)
    {
        return "battleship";
    }
    else if (type == ST_CRUISER)
    {
        return "cruiser";
    }
    else if (type == ST_DESTROYER)
    {
        return "destroyer";
    }
    else if (type == ST_SUBMARINE)
    {
        return "submarine";
    }

    return "none";
}

bool WantToPlayAgain()
{
    char input;
    const char validInput[] = { 'y', 'n' };

    input = GetCharacter("Would you like to play again? (y/n)", INPUTERROR, validInput, 2);

    return input == 'y';
}

void ClearBoards(Player& player)
{
    for (int r = 0; r < BoardSize; ++r)
    {
        for (int c = 0; c < BoardSize; ++c)
        {
            player.guessBoard[r][c] = GT_NONE;
            player.shipBoard[r][c].shipType = ST_NONE;
            player.shipBoard[r][c].isHit = false;
        }
    }
}
void DrawSeperatorLine()
{
    std::cout << " ";

    for (int c = 0; c < BoardSize; ++c)
    {
        std::cout << "+---";
    }
};
void DrawColumnsRow()
{
    std::cout << " ";
    for (int c = 0; c < BoardSize; ++c)
    {
        int columnName = c + 1;

        std::cout << " " << columnName << "  ";
    }
}
char GetShipRepresentationAt(const Player& player, int row, int col)
{
    if (player.shipBoard[row][col].isHit)
    {
        return '*';
    }

    if (player.shipBoard[row][col].shipType == ST_AIRCRAFT_CARRIER)
    {
        return 'a';
    }
    else if (player.shipBoard[row][col].shipType == ST_BATTLESHIP)
    {
        return 'b';
    }
    else if (player.shipBoard[row][col].shipType == ST_CRUISER)
    {
        return 'c';
    }
    else if (player.shipBoard[row][col].shipType == ST_DESTROYER)
    {
        return 'd';
    }
    else if (player.shipBoard[row][col].shipType == ST_SUBMARINE)
    {
        return 's';
    }
    else
    {
        return ' ';
    }
}
char GetGuessRepresentationAt(const Player& player, int row, int col)
{
    if (player.guessBoard[row][col] == GT_HIT)
    {
        return '*';
    }
    else if (player.guessBoard[row][col] == GT_MISS)
    {
        return 'o';
    }
    else
    {
        return ' ';
    }
}
void DrawShipBoardRow(const Player& player, int row)
{
    char rowName = row + 'A';
    std::cout << rowName << " ";

    for (int c = 0; c < BoardSize; ++c)
    {
        std::cout << " " << GetShipRepresentationAt(player, row, c) << " |";
    }
}
void DrawGuessBoardRow(const Player& player, int row)
{
    char rowName = row + 'A';
    std::cout << rowName << "|";

    for (int c = 0; c < BoardSize; ++c)
    {
        std::cout << " " << GetGuessRepresentationAt(player, row, c) << " |";
    }
}
void DrawBoards(Player& player)
{
    ClearBoards(player);

    DrawColumnsRow();

    DrawColumnsRow();

    std::cout << "\n";

    for (int r = 0; r < BoardSize; ++r)
    {
        DrawSeperatorLine();

        std::cout << " ";

        DrawSeperatorLine();

        std::cout << "\n";

        DrawShipBoardRow(player, r);

        std::cout << " ";

        DrawGuessBoardRow(player, r);

        std::cout << "\n";
    }

    DrawSeperatorLine();
    std::cout << " ";
    DrawSeperatorLine();
    std::cout << "\n";
}

ShipPosition MapBoardPos(int row, char col)
{
    int realRow = row - 'A';
    int realCol = col - 1;

    ShipPosition boardPos;
    boardPos.row = realRow;
    boardPos.col = realCol;

    return boardPos;
}
ShipPosition GetBoardPosition()
{
    char rowInput;
    int columnInput;

    const char validRowsInput[] = { 'A','B','C','D','E','F','G','H','I','J' };
    const int validColIpnuts[] = { 1,2,3,4,5,6,7,8,9,10 };

    rowInput = GetCharacter("Please Input a row(A-J): ", INPUTERROR, validRowsInput, BoardSize);
    columnInput = GetInt("Please input a column(1-10): ", INPUTERROR, validColIpnuts, BoardSize);

    return MapBoardPos(rowInput, columnInput);
}
ShipOrientation GetShipOrientation()
{
    ShipOrientation orientation;
    const char validInput[2] = { 'H', 'V' };

    char Input = GetCharacter("Do you want to place the ship vertically or horizontally?(H,V)", INPUTERROR, validInput, 2);

    switch (Input)
    {
    case 'H':
        return Horizontal;
    case 'V':
        return Vertical;
    }

    std::cout << "switch in GetShipOrientation not working";
}
bool isValidPlacement(const Player& player, const Ship& ship, const ShipOrientation& orientation, const ShipPosition& position)
{
    if (orientation == Horizontal)
    {
        for (int c = position.col; c < (position.col + ship.shipSize); ++c)
        {
            if (player.shipBoard[position.row][c].shipType != ST_NONE || c >= BoardSize)
            {
                return false;
            }
        }
    }
    else
    {
        for (int r = position.row; r < (position.row + ship.shipSize); ++r)
        {
            if (player.shipBoard[r][position.col].shipType != ST_NONE || r >= BoardSize)
            {
                return false;
            }
        }
    }
    return true;
    std::cout << "isValidPlacement func not working";
}
void PlaceShipOnBoard(Player& player, Ship& ship, const ShipOrientation& orientation, const ShipPosition& position)
{
    ship.shipGridPos = position;
    ship.orientation = orientation;

    if (orientation == Horizontal)
    {
        for (int c = position.col; c < (position.col + ship.shipSize); ++c)
        {
            player.shipBoard[position.row][position.col].shipType = ship.type;
            player.shipBoard[position.row][position.col].isHit = false;
        }
    }
    else
    {
        for (int r = position.row; r < (position.row + ship.shipSize); ++r)
        {
            player.shipBoard[position.row][position.col].shipType = ship.type;
            player.shipBoard[position.row][position.col].isHit = false;
        }
    }
}
void SetUpBoards(Player& player)
{
    ClearBoards(player);
    for (int i = 0;i < NumShips; ++i)
    {
        DrawBoards(player);

        Ship& currentShip = player.ships[i];

        ShipPosition shipPosition;
        ShipOrientation shipOrientation;

        bool isValidPlacementb = false;

        do
        {
            std::cout << player.PlayerName << " please set the position and orientation for your " << GetShipName(currentShip.type);
            shipPosition = GetBoardPosition();
            shipOrientation = GetShipOrientation();

            isValidPlacementb = isValidPlacement(player, currentShip, shipOrientation, shipPosition);

            if (isValidPlacement)
            {
                std::cout << "\nThat was not a vaild placement. plaese try again\n";
            }

        } while (!isValidPlacement);

        PlaceShipOnBoard(player, currentShip, shipOrientation, shipPosition);
    }

    DrawBoards(player);
}

void PlayGame(Player& player1, Player& player2)
{
    SetUpBoards(player1);
    SetUpBoards(player2);

    Player* currentPlayer = &player1;
    Player* otherPlayer = &player2;

    ShipPosition guess;

    do
    {
        DrawBoards(*currentPlayer);
        bool isValidGuess;

        do
        {
            std::cout << currentPlayer->PlayerName << "What is your guess?\n";
            guess = GetBoardPosition();

            isValidGuess = currentPlayer->guessBoard[guess.row][guess.col] = GT_NONE;

            if (!isValidGuess)
            {
                std::cout << "\nThat was not a valid guess. Please try again.\n";
            }

        } while (isValidGuess);

        ShipTypes type = Upd

    } while (!GameOver());
}


int main()
{
    Player player1;
    Player player2;
    InitPlayer(player1, "player1");
    InitPlayer(player2, "player2");

    do
    {
        PlayGame(player1, player2);
    } while (WantToPlayAgain());
}

