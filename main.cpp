#include <iostream>
#include <sstream>
#include <ctime>
#include "libSmoke.h"

using namespace SmokeSpace;
using namespace std;


//convert arg
int conversion(string stringvalue)
{
    int intValue;
    stringstream ssValue;
    ssValue << stringvalue;
    ssValue >> intValue;

    if(ssValue.fail())
    {
        cerr << "could not convert the string '" << stringvalue << "' to integer!" <<endl;
        exit(EXIT_FAILURE);
    }
    return intValue;
}

int main(int argc, char** argv)
{
    //seed the random value function
    srand(time(nullptr));

    if(argc != 5)
    {
        cerr << "USAGE: <progName> <rows> <cols> <playerRow> <playerCol>" << endl;
        exit(EXIT_FAILURE);
    }

    int intRows = conversion(argv[1]);
    int intCols = conversion(argv[2]);
    int intPRow = conversion(argv[3]);
    int intPCol = conversion(argv[4]);

    //create the game variable and generate random fragments
    Game arGame;
    arGame.intFragments = genRandom(3, 7);

    //initialize the game
    init(arGame, intRows, intCols, intPRow, intPCol);

    char chChoice = '\0';

    do
    {
        printWorld(arGame);
        cin >> chChoice;
        movePlayer(arGame,chChoice);

    } while (true);
    return 0;
}
