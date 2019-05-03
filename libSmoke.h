#ifndef LIBSMOKE_H_INCLUDED
#define LIBSMOKE_H_INCLUDED
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cassert>
#include <iomanip>

using namespace std;


namespace SmokeSpace
{
    typedef int** t_2DArray;
    typedef int* t_1DArray;

    //player health
    const int INIT_HEALTH = 1000;

    enum VALUES
    {
        SPACE,
        SMOKE,
        FRAGMENT,
        FRAGMENT_REVEALED,
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
        int pHealth = INIT_HEALTH;
        int intFragments;
        int rows;
        int cols;
    };


    //game initi
    void init(Game&, int,  int, int, int);
    void playerHealth(Game&);
    void placeObject(Game&, int);
    void printWorld(const Game&);
    int genRandom(int, int);
    strucPlayer findPlayer(const Game&);
    bool isInWorld(const Game&, int, int);
    void destroyWorld(Game&);
    void destroyWorld(t_2DArray&, int);

    //player movement
    void movePlayer(Game&, char);
    void checkSurrounding(Game&);
    void continueGame(const Game&);

    //smoke detection
    void fillSmoke(Game&);
    void arCopy(const t_2DArray&, t_2DArray&);

}


#endif // LIBSMOKE_H_INCLUDED
