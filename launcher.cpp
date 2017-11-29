#include "TXLib.h"
#include "Ball.h"
int main()
    {
    txCreateWindow (GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
    //txDisableAutoPause();
    const int bnum = 10;
    BallGroup balls(bnum);
    HDC helptun = txLoadImage ("Tun.bmp");
    tx_auto_func (txDeleteDC(helptun));
    balls.initBalls (helptun);
    //printf ("хмм.. неплоха\n");
    //getch();
    bool paused = false;
    char help[16];
    sprintf (help, "John");
    //printf ("тааак-с\n");
    //getch();
    balls[0].setName (help);
    sprintf (help, "Bill");
    balls[1].setName (help);
    sprintf (help, "Den");
    balls[2].setName (help);
    sprintf (help, "Ilya");
    balls[3].setName (help);
    sprintf (help, "Ded");
    balls[4].setName (help);
    sprintf (help, "Egor");
    balls[5].setName (help);
    int cyclepoint = 0;
    //printf ("хорошо\n");
    //getch();
    HDC koteuka = txLoadImage("KOTR.bmp");
    tx_auto_func (txDeleteDC(koteuka));
    //printf ("Это уже достижение!\n");
    //getch();
    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        drawHitTable (balls, bnum, txGetExtentX() - 250, 50, txGetExtentX() - 50, txGetExtentY()/2 - 50);
        if (GetAsyncKeyState ('P'))
            {
            txSleep (70);
            if (paused == false) paused = true;
            else paused = false;
            }
        if (!paused) balls.testAll ();
        if (!paused) balls.makeCollisionsInLauncher ();
        if (!paused) balls.moveAll ();
        balls.drawAll ();
        myAlphaBlend(txDC(), txGetExtentX() - 256, txGetExtentY() - 256, 180, 180, koteuka, ((int)(cyclepoint/6) * 128) % 1024, 0, 128, 128, 1);
        //getch();
        //printf ("DoubPaira\n");
        //getch();
        //printf ("DoubPaird\n");
        //getch();
        //printf ("angle == %f\n", ABall.getAngle());
        txSleep(30);//10
        txSetFillColor (RGB(60, 49, 73));
        txClear();        //180 196 196
        //txClearConsole();
        cyclepoint++;
        }


    return 0;
    }






