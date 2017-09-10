
#include "TXLib.h"
#include "Ball.h"

int main()
    {
    srand(time(0));
    txCreateWindow (800, 600);
    //BallChar test[10] = {};
    /*test[0].hitnumch = 3;
    test[1].hitnumch = 1;
    test[2].hitnumch = 2;
    test[3].hitnumch = 3;
    test[4].hitnumch = 3;
    test[5].hitnumch = 4;
    test[6].hitnumch = 1;
    test[7].hitnumch = 1;
    test[8].hitnumch = 3;
    test[9].hitnumch = 8;//*/
    /*for (int j = 0; j < 10; j++)
        {
        test[j].hitnumch = rand()%10;
        }           //*/
    //printchars (test, 0, 9);
    //SortBallsCharacteristics (test, 0, 9);
    //printchars (test, 0, 9);
    Ball test (500, 500, 5, 5, 5, TX_WHITE, 1);
    test.draw();
    return 0;
    }
