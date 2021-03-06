#include "TXLib.h"
#include "Ball.h"
void makeCollisionsInLauncher (Ball balls[], int bnum);
void initChars (BallChar chars[], Ball balls[], int size);
void drawHitTable (Ball balls[], const int bnum, double x1, double y1, double x2, double y2, int topsnum = 5);
void moveBalls (Ball balls[], int bnum);
void drawBalls (Ball balls[], int bnum);
void testBalls (Ball balls[], int bnum);
void initBalls (Ball balls[], int bnum);
int main()
    {
    txCreateWindow (800, 600);
    //txDisableAutoPause();
    const int bnum = 10;
    Ball balls[bnum];
    initBalls (balls, bnum);
    bool paused = false;
    balls[0].setName ("John");
    balls[1].setName ("Bill");
    balls[2].setName ("Alex");
    balls[3].setName ("Ilya");
    balls[4].setName ("Ded");
    balls[5].setName ("Egor");

    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        drawBalls (balls, bnum);
        makeCollisionsInLauncher (balls, bnum);
        testBalls (balls, bnum);
        drawHitTable (balls, bnum, txGetExtentX() - 250, 50, txGetExtentX() - 50, txGetExtentY()/2 - 50);
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






