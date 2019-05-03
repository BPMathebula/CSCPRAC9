#include "libSmoke.h"
#include <windows.h>

char SYMBOLS[] = {'*', 'o', 'f', 'f', 'P'};
namespace SmokeSpace
{


    void init(Game& arGame, int intRows, int intCols, int intPRow, int intPCol)
    {

        assert(intRows * intCols > 0);
        assert(intPCol * intPRow < intRows * intCols);
        //initialize the world
        arGame.rows = intRows;
        arGame.cols = intCols;

        arGame.grid = new t_1DArray[intRows];

        for(int r =0; r < arGame.rows; ++r)
        {
            arGame.grid[r] = new int[intCols];
            for(int c = 0; c < arGame.cols; ++c)
            {
                arGame.grid[r][c] = VALUES::SMOKE;
            }
        }

        //place the player
        assert(isInWorld(arGame, intPRow, intPCol));
        arGame.grid[intPRow][intPCol] = VALUES::PLAYER;

        //place the frags
        for(int n = 0; n < arGame.intFragments; ++n)
        {
            placeObject(arGame, VALUES::FRAGMENT);

        }

        //checks the players surrounding
        checkSurrounding(arGame);

    }

    void placeObject(Game& arGame, int intObject)
    {
        int row = - 1;
        int col = -1;

        do
        {
            row = genRandom(0, arGame.rows - 1);
            col = genRandom(0, arGame.cols - 1);
        } while(arGame.grid[row][col] != VALUES::SMOKE);

        arGame.grid[row][col] = intObject;
    }


    void playerHealth(Game& arGame)
    {
        //deduct a random value from the health between 1 and 5 inclusive
        arGame.pHealth -= genRandom(1, 5);
    }

    void printWorld(const Game& arGame)
    {
        //color coding
        HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);

        //clear the screen
        system("cls");
        int intSpacing = 0;
        for(int r =0; r < arGame.rows; ++r)
        {
            for(int c = 0; c < arGame.cols; ++c)
            {
                SetConsoleTextAttribute(screen, 15);
                switch(arGame.grid[r][c])
                {
                case VALUES::SPACE:
                    cout << setw(intSpacing) << SYMBOLS[VALUES::SPACE];
                    break;

                case VALUES::SMOKE:
                case VALUES::FRAGMENT:
                    cout << setw(intSpacing) << SYMBOLS[VALUES::SMOKE];
                    break;

                case VALUES::FRAGMENT_REVEALED:
                    SetConsoleTextAttribute(screen, 14);
                    cout << setw(intSpacing) << SYMBOLS[VALUES::FRAGMENT_REVEALED];
                    break;

                case VALUES::PLAYER:
                    SetConsoleTextAttribute(screen, 12);
                    cout << setw(intSpacing) << SYMBOLS[VALUES::PLAYER];
                    break;

                }

            }
            cout << endl;
        }

        SetConsoleTextAttribute(screen, 10);
        //print player health
        cout << "\n-------------------------------" << endl;
        cout << "PLAYER HEALTH: " << arGame.pHealth << endl
                << "FRAGMENTS LEFT: " << arGame.intFragments << endl << "-------------------------------" << endl;
        //print menu
        cout << "Movement: " << endl
                << "W) UP" << endl << "S) DOWN" << endl
                << "A) LEFT" << endl << "D) RIGHT" << endl
                << "Q) TOP-LEFT" << endl << "E) TOP-RIGHT" << endl
                << "Z) BOTTOM-LEFT" << endl << "C) BOTTOM-RIGHT" << endl
                << "Enter Char: ";

        continueGame(arGame);

    }

    void continueGame(const Game& arGame)
    {
        if(arGame.intFragments == 0)
        {
            cout << "\n\nCONGRATULATIONS!!! YOU WIN!!!" << endl;
            exit(EXIT_SUCCESS);
        } else if(arGame.pHealth <= 0)
        {
            cout << "\n\nOUT OF HEALTH!!! YOU LOSE!!" << endl;
            exit(EXIT_SUCCESS);
        }
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


    //function used to check the player's surroundings
    void checkSurrounding(Game& arGame)
    {
        //get the player location
        strucPlayer pLoc = findPlayer(arGame);

        //top-left
        if(isInWorld(arGame, pLoc.row - 1, pLoc.col - 1))
        {
            if(arGame.grid[pLoc.row - 1][pLoc.col - 1] == VALUES::FRAGMENT || arGame.grid[pLoc.row - 1][pLoc.col - 1] == VALUES::FRAGMENT_REVEALED)
            {
                arGame.grid[pLoc.row - 1][pLoc.col - 1] = VALUES::FRAGMENT_REVEALED;
            } else
            {
                arGame.grid[pLoc.row - 1][pLoc.col - 1] = VALUES::SPACE;
            }
        }

        //top
        if(isInWorld(arGame, pLoc.row - 1, pLoc.col))
        {
            if(arGame.grid[pLoc.row - 1][pLoc.col] == VALUES::FRAGMENT || arGame.grid[pLoc.row - 1][pLoc.col] == VALUES::FRAGMENT_REVEALED)
            {
                arGame.grid[pLoc.row - 1][pLoc.col] = VALUES::FRAGMENT_REVEALED;
            } else
            {
                arGame.grid[pLoc.row - 1][pLoc.col] = VALUES::SPACE;
            }
        }

        //top-right
        if(isInWorld(arGame, pLoc.row - 1, pLoc.col + 1))
        {
            if(arGame.grid[pLoc.row - 1][pLoc.col + 1] == VALUES::FRAGMENT || arGame.grid[pLoc.row - 1][pLoc.col + 1] == VALUES::FRAGMENT_REVEALED)
            {
                arGame.grid[pLoc.row - 1][pLoc.col + 1] = VALUES::FRAGMENT_REVEALED;
            } else
            {
                arGame.grid[pLoc.row - 1][pLoc.col + 1] = VALUES::SPACE;
            }
        }

        //left
        if(isInWorld(arGame, pLoc.row, pLoc.col - 1))
        {
            if(arGame.grid[pLoc.row][pLoc.col - 1] == VALUES::FRAGMENT || arGame.grid[pLoc.row][pLoc.col - 1] == VALUES::FRAGMENT_REVEALED)
            {
                arGame.grid[pLoc.row][pLoc.col - 1] = VALUES::FRAGMENT_REVEALED;
            } else
            {
                arGame.grid[pLoc.row][pLoc.col - 1] = VALUES::SPACE;
            }
        }

        //right
        if(isInWorld(arGame, pLoc.row, pLoc.col + 1))
        {
            if(arGame.grid[pLoc.row][pLoc.col + 1] == VALUES::FRAGMENT ||arGame.grid[pLoc.row][pLoc.col + 1] == VALUES::FRAGMENT_REVEALED)
            {
                arGame.grid[pLoc.row][pLoc.col + 1] = VALUES::FRAGMENT_REVEALED;
            } else
            {
                arGame.grid[pLoc.row][pLoc.col + 1] = VALUES::SPACE;
            }
        }

        //bottom-left
        if(isInWorld(arGame, pLoc.row + 1, pLoc.col - 1))
        {
            if(arGame.grid[pLoc.row + 1][pLoc.col - 1] == VALUES::FRAGMENT || arGame.grid[pLoc.row + 1][pLoc.col - 1] == VALUES::FRAGMENT_REVEALED)
            {
                arGame.grid[pLoc.row + 1][pLoc.col - 1] = VALUES::FRAGMENT_REVEALED;
            } else
            {
                arGame.grid[pLoc.row + 1][pLoc.col - 1] = VALUES::SPACE;
            }
        }

        //bottom
        if(isInWorld(arGame, pLoc.row + 1, pLoc.col))
        {
            if(arGame.grid[pLoc.row + 1][pLoc.col] == VALUES::FRAGMENT || arGame.grid[pLoc.row + 1][pLoc.col] == VALUES::FRAGMENT_REVEALED)
            {
                arGame.grid[pLoc.row + 1][pLoc.col] = VALUES::FRAGMENT_REVEALED;
            } else
            {
                arGame.grid[pLoc.row + 1][pLoc.col] = VALUES::SPACE;
            }
        }

        //bottom-right
        if(isInWorld(arGame, pLoc.row + 1, pLoc.col + 1))
        {
            if(arGame.grid[pLoc.row + 1][pLoc.col + 1] == VALUES::FRAGMENT || arGame.grid[pLoc.row + 1][pLoc.col + 1] == VALUES::FRAGMENT_REVEALED)
            {
                arGame.grid[pLoc.row + 1][pLoc.col + 1] = VALUES::FRAGMENT_REVEALED;
            } else
            {
                arGame.grid[pLoc.row + 1][pLoc.col + 1] = VALUES::SPACE;
            }
        }

    }
    void movePlayer(Game& arGame, char chDir)
    {
        //get the player location
        strucPlayer pLoc = findPlayer(arGame);

        //store the location temporarily
        int intTempRow = pLoc.row;
        int intTempCol = pLoc.col;

        switch(toupper(chDir))
        {
        case 'W':
            //up
            pLoc.row--;
            break;

        case 'S':
            //down
            pLoc.row++;
            break;

        case 'E':
            //top-right
            pLoc.row--;
            pLoc.col++;
            break;


        case 'Q':
            //top-left
            pLoc.row--;
            pLoc.col--;
            break;

        case 'A':
            //left
            pLoc.col--;
            break;

        case 'D':
            //right
            pLoc.col++;
            break;

        case 'C':
            //bottom-right
            pLoc.row++;
            pLoc.col++;
            break;

        case 'Z':
            //bottom-left
            pLoc.row++;
            pLoc.col--;
            break;

        default:
            cerr << "The direction is invalid" << endl;

        }

        //make the movement
        if(isInWorld(arGame, pLoc.row, pLoc.col))
        {
            //store space for now
            arGame.grid[intTempRow][intTempCol] = VALUES::SPACE;

            if(arGame.grid[pLoc.row][pLoc.col] == VALUES::FRAGMENT_REVEALED)
                --arGame.intFragments;


            arGame.grid[pLoc.row][pLoc.col] = VALUES::PLAYER;

            //update player health
            playerHealth(arGame);
            //check the surroundings
            checkSurrounding(arGame);

            //check neighbours
            fillSmoke(arGame);

        }

    }


    //function used to make a copy of the game world for smoking
    void arCopy(const Game& arGame, t_2DArray& arSmoke)
    {
        arSmoke = new t_1DArray[arGame.rows];
        for(int r = 0; r < arGame.rows; ++r)
        {
            arSmoke[r] = new int[arGame.cols];
            for(int c = 0; c < arGame.cols; ++c)
            {
                arSmoke[r][c] = arGame.grid[r][c];
            }

        }
    }


    //filling the smoke using a cloned gameWorld
    void fillSmoke(Game& arGame)
    {

        //create a duplicate array
        t_2DArray arSmoke;
        arCopy(arGame, arSmoke);
        for(int r = 0; r < arGame.rows; ++r)
        {
            for(int c = 0; c < arGame.cols; ++c)
            {
                if(arSmoke[r][c] == VALUES::SPACE)
                {
                    //top-left
                    if(isInWorld(arGame, r - 1, c - 1))
                    {
                        if(arSmoke[r - 1][c - 1] == VALUES::SMOKE)
                        {
                            if(genRandom(1, 100) <= 10)
                            {
                                arGame.grid[r][c] = VALUES::SMOKE;
                                return;
                            }

                        }
                    }

                    //top
                    if(isInWorld(arGame, r - 1, c))
                    {
                        if(arSmoke[r - 1][c] == VALUES::SMOKE)
                        {
                            if(genRandom(1, 100) <= 10)
                            {
                                arGame.grid[r][c] = VALUES::SMOKE;
                                return;
                            }
                        }
                    }

                    //top-right
                    if(isInWorld(arGame, r - 1, c + 1))
                    {
                        if(arSmoke[r - 1][c + 1] == VALUES::SMOKE)
                        {
                            if(genRandom(1, 100) <= 10)
                            {
                                arGame.grid[r][c] = VALUES::SMOKE;
                                return;
                            }
                        }
                    }

                    //left
                    if(isInWorld(arGame, r, c - 1))
                    {
                        if(arSmoke[r][c - 1] == VALUES::SMOKE)
                        {
                            if(genRandom(1, 100) <= 10)
                            {
                                arGame.grid[r][c] = VALUES::SMOKE;
                                return;
                            }
                        }
                    }

                    //right
                    if(isInWorld(arGame, r, c + 1))
                    {
                        if(arSmoke[r][c + 1] == VALUES::SMOKE)
                        {
                            if(genRandom(1, 100) <= 10)
                            {
                                arGame.grid[r][c] = VALUES::SMOKE;
                                return;
                            }
                        }
                    }

                    //bottom-left
                    if(isInWorld(arGame, r + 1, c - 1))
                    {
                        if(arSmoke[r + 1][c - 1] == VALUES::SMOKE)
                        {
                            if(genRandom(1, 100) <= 10)
                            {
                                arGame.grid[r][c] = VALUES::SMOKE;
                                return;
                            }
                        }
                    }

                    //bottom
                    if(isInWorld(arGame, r + 1, c))
                    {
                        if(arSmoke[r + 1][c] == VALUES::SMOKE)
                        {
                            if(genRandom(1, 100) <= 10)
                            {
                                arGame.grid[r][c] = VALUES::SMOKE;
                                return;
                            }
                        }
                    }

                    //bottom-right
                    if(isInWorld(arGame, r + 1, c + 1))
                    {
                        if(arSmoke[r + 1][c + 1] == VALUES::SMOKE)
                        {
                            if(genRandom(1, 100) <= 10)
                            {
                                arGame.grid[r][c] = VALUES::SMOKE;
                                return;
                            }
                        }
                    }

                }
            }
        }

        //destroy the smoke array
        destroyWorld(arSmoke, arGame.rows);
    }

     //deallocate the smoke array
    void destroyWorld(t_2DArray& arSmoke, int intRows)
    {
        for(int r = 0; r < intRows; ++r)
        {
            delete [] arSmoke[r];
        }

        delete [] arSmoke;
        arSmoke = nullptr;
    }
}
