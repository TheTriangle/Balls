#include "TXLib.h"
#include "Ball.h"
void drawHitTable (Ball balls[], const int bnum, double x1, double y1, double x2, double y2, int topsnum = 5);
void moveBalls (Ball balls[], int bnum);
void drawBalls (Ball balls[], int bnum);
void testBalls (Ball balls[], int bnum);
void initBalls (Ball balls[], int bnum);
int main()
    {
    txCreateWindow (800, 600);
    txDisableAutoPause();
    const int bnum = 6;
    Ball balls[bnum];
    initBalls (balls, bnum);
    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        moveBalls (balls, bnum);
        drawBalls (balls, bnum);
        testBalls (balls, bnum);
        drawHitTable (balls, bnum, txGetExtentX() - 250, 50, txGetExtentX() - 200, txGetExtentY()/2 - 50);
        //printf ("angle == %f\n", ABall.getAngle());
        txSleep(10);
        txSetFillColor (TX_BLACK);
        txClear();
        //txClearConsole();
        }


    return 0;
    }

void drawHitTable (Ball balls[], const int bnum, double x1, double y1, double x2, double y2, int topsnum)
    {
    txSelectFont ("Times New Roman", 30);
    txSetColor (TX_WHITE, 1);
    double ysize = (y2 - y1) / topsnum;
    BallChar ballschars [] = {};
    for (int i = 0; i < bnum; i++)
        {
        balls[i].makeChar(&ballschars[bnum]);
        }
    SortBallsCharacteristics (ballschars, 0, bnum);
    txLine (x1 + 20, y1, x1 + 20, y2);
    txDrawText (x1, y1, x1 + 20, y1 + ysize, "¹");
    //for (int i = 0; i < topsnum; i++)
    }



void initBalls (Ball balls[], int bnum)
    {
    for (int i = 0; i < bnum; i++)
        {
        Ball hball ((double)(i)/(double)(bnum) * txGetExtentX(), (double)(i)/(double)(bnum) * txGetExtentY(),
                    10, (i - bnum/2) * 15, 5, RGB ((double)(i)/(double)(bnum)*255, (double)(i)/(double)(bnum)*255, (double)(i)/(double)(bnum)*255), i);
        balls[i] = hball;
        }
    }

void drawBalls (Ball balls[], int bnum)
    {
    for (int i = 0; i < bnum; i++)
        {
        balls[i].draw();
        }
    }

void testBalls (Ball balls[], int bnum)
    {
    for (int i = 0; i < bnum; i++)
        {
        balls[i].testWallHit();
        }
    }

void moveBalls (Ball balls[], int bnum)
    {
    for (int i = 0; i < bnum; i++)
        {
        balls[i].move(1);
        }
    }

