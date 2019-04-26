#ifndef LIBSMOKE_H_INCLUDED
#define LIBSMOKE_H_INCLUDED
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

namespace SmokeSpace
{
    typedef int** t_2DArray;
    typedef int* t_1DArray;


    enum VALUES
    {
        SPACE,
        SMOKE,
        FRAGMENT,
        PLAYER
    };

    struct strucPlayer
    {
        int row;
        int col;
    };

    struct Game
    {
        t_2DArray grid;
        strucPlayer plyrLoc;
        int rows;
        int cols;
    };


    void init(Game&);
    int genRandom(int, int);
    strucPlayer findPlayer(const Game&);
    bool isInWorld(const Game&);
    void destroyWorld(Game&);

    //player movement
    void movePlayer(Game&, char);

}


#endif // LIBSMOKE_H_INCLUDED
