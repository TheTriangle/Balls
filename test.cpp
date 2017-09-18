
#include "TXLib.h"
#include "Ball.h"
int main()
    {
    txCreateWindow (800, 600);

    const int bnum = 2;
    Ball balls[bnum];
    initBalls (balls, bnum);
    bool paused = false;
    balls[0].setName ("John");
    balls[1].setName ("Bill");

    balls[0].setCords(100, 300);
    balls[1].setCords(700, 300);

    balls[0].setAngle(0);
    balls[1].setAngle(135);
    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        drawBalls (balls, bnum);
        makeCollisionsInLauncher (balls, bnum);
        testBalls (balls, bnum);
        drawHitTable (balls, bnum, txGetExtentX() - 250, 50, txGetExtentX() - 50, txGetExtentY()/2 - 50, 2);
        if (GetAsyncKeyState ('P'))
            {
            txSleep (70);
            if (paused == false) paused = true;
            else paused = false;
            }
        if (!paused) moveBalls (balls, bnum);
        //getch();
        //printf ("DoubPaira\n");
        //getch();
        //printf ("DoubPaird\n");
        //getch();
        //printf ("angle == %f\n", ABall.getAngle());
        txSleep(10);
        txSetFillColor (TX_BLACK);
        txClear();
        //txClearConsole();
        }

    return 0;
    }
