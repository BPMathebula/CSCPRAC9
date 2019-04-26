#include "libSmoke.h"

namespace SmokeSpace
{

    void init(Game& arGame)
    {
        //initialize the world
    }

    int genRandom(int intMin, int intMax)
    {
        assert(intMax > intMin);
        return intMin + (rand() % (intMax - intMin + 1));
    }

    strucPlayer findPlayer(const Game& arGame)
    {
        strucPlayer playa;

        for(int r =0; r < arGame.rows; ++r)
        {
            for(int c = 0; c < arGame.cols; ++c)
            {
                if(arGame.grid[r][c] == VALUES::PLAYER)
                {
                    playa.col = c;
                    playa.row = r;
                    return playa;
                }
            }
        }

        return playa;
    }


    bool isInWorld(const Game& arGame, int intTRow, int intTCol)
    {
        return ((intTRow < 0 || intTRow >= arGame.rows) || (intTCol < 0 || intTCol >= arGame.cols)) ? false : true;
    }


    void destroyWorld(Game& arGame)
    {

        for(int r =0; r < arGame.rows; ++r)
        {
            delete [] arGame.grid[r];
        }

        delete [] arGame.grid;
        arGame.grid = nullptr;
    }

    void movePlayer(Game& arGame, char chDir)
    {
        strucPlayer pLoc = findPlayer(arGame);

        switch(toupper(chDir))
        {
        case 'W':
            pLoc.row--;
            break;

        case 'S':
            pLoc.row++;
            break;

        case 'E':
            pLoc.row--;
            pLoc.col++;
            break;

        case 'Q':
            pLoc.row--;
            pLoc.col--;
            break;

        case 'A':
            pLoc.col--;
            break;

        case 'D':
            pLoc.col++;
            break;

        case 'C':
            pLoc.row++;
            pLoc.col++;
            break;

        case 'Z':
            pLoc.row++;
            pLoc.col--;
            break;

        default:
            cerr << "The direction is invalid" << endl;
            exit(EXIT_FAILURE);

        }
    }
}
