#define DEGREEMODIFIER 0.01745
#define PI 3.141593

class DoubPair
    {
    public:
    double x;
    double y;
    };

struct SUPERDoubPair
    {
    DoubPair f;
    DoubPair s;
    };

class BallChar
    {
    public:
    int id;
    int hitnumch = 0;
    };

//void initBalls (Ball balls[], int bnum);
bool myAlphaBlend (HDC dest, double xDest, double yDest, double width1, double height1,
                   HDC src,  double xSrc /*= 0*/, double ySrc /*= 0*/, double width2, double height2, double alpha = 1.0);
double getAccurateAngle (double x, double y);
double ProjVec (double x1, double y1, double x2, double y2);
double ScalMult (double x1, double y1, double x2, double y2);
DoubPair DecartToTDiPol (double dx, double dy);
double LengthOf (double x, double y);
DoubPair DiPolToDecart (double angle, double length);
SUPERDoubPair getBiPolSpeedAfterCollision (double vx1, double vy1, double vx2, double vy2,
                                        double cx1, double cy1, double cx2, double cy2,
                                        double mass1, double mass2);
double getDistanceBetween(double x1, double y1, double x2, double y2);
void printchars (BallChar chars[], int left, int right);
int SortBallsCharacteristics (BallChar chars[], int left, int right);
bool standsright (BallChar chars[], int tests, int mid);
void change (BallChar chars[], int first, int second);


class Ball
    {
    private:
    HDC tun;
    int noCollisionId;
    COLORREF ballcolor;
    COLORREF vectorcolor = RGB (200, 200, 200);
    DoubPair cords;
    int vectorwidth = 5;
    double radius;
    double angle;
    int id;
    double dt = 1;
    double speed;
    int hitcounter;
    public:
    char name[16];
    BallChar thisChars; //TODO РїРµСЂРµРЅРµСЃС‚Рё РїРѕРґ СЃРїРµС†.РґРѕСЃС‚.private
    bool testWallHit ()
        {
        if (cords.x + radius > txGetExtentX())
            {
            cords.x = txGetExtentX() - radius;
            if (angle >= 0) angle = PI - angle;
            else angle = -PI - angle;
            return true;
            hitcounter++;
            thisChars.hitnumch++;
            }
        if (cords.x - radius < 0)
            {
            cords.x = radius;
            if (angle >= 0) angle = PI - angle;
            else angle = -PI - angle;
            hitcounter++;
            thisChars.hitnumch++;
            return true;
            }
        if (cords.y + radius > txGetExtentY())
            {
            cords.y = txGetExtentY() - radius;
            angle = -angle;
            hitcounter++;
            thisChars.hitnumch++;
            return true;
            }
        if (cords.y - radius < 0)
            {
            cords.y = radius;
            angle = -angle;
            hitcounter++;
            thisChars.hitnumch++;
            return true;
            }
        return false;
        }
    void setName (char newname[])
        {
        for (int i = 0; i < 16; i++)
            {
            name[i] = newname[i];
            //thisChars.namech[i] = newname[i];
            }
        }
    void setRadius (double grad)
        {
        radius = grad;
        }
    //~Ball()
    //    {
    //    txDeleteDC(tun);
    //   }
    void setTun (HDC gaveim)
        {
        tun = gaveim;
        }
    void setColor (COLORREF gcol)
        {
        ballcolor = gcol;
        }
    void setVectorColor (COLORREF gcol, int gwidth = 5)
        {
        vectorcolor = gcol;
        vectorwidth = gwidth;
        }
    void setCords (double gx, double gy)
        {
        cords.x = gx;
        cords.y = gy;
        }
    int getID()
        {
        return id;
        }
    double getAngleTo(double xto, double yto)
        {
        assert (fabs((yto - cords.y)/getDistanceTo(xto, yto)) <= 1);
        return asin((yto - cords.y)/getDistanceTo(xto, yto));
        }

    double getX()
        {
        return cords.x;
        }
    double getY()
        {
        return cords.y;
        }
    DoubPair getCords()
        {
        return cords;
        }
    void draw ()
        {
        txSelectFont ("Times New Roman", 18);
        txSetFillColor (ballcolor);
        txSetColor (ballcolor, 1);
        txCircle (cords.x, cords.y, radius);
        //txSetColor (ballcolor, 5);
        //txLine (cords.x, cords.y,  cords.x - speed * cos(angle ) * 10, cords.y + speed * sin(angle ) * 5);
        myAlphaBlend (txDC(), cords.x - radius, cords.y - radius, radius * 2, radius * 2, tun, 0, 0, 169, 169, 1);
        txSetColor (vectorcolor, vectorwidth);
        txDrawText (cords.x - radius - 65, cords.y - radius - 25, cords.x + radius + 65, cords.y - radius - 15, name);
        txLine (cords.x, cords.y,  cords.x + speed * cos(angle ) * 10, cords.y - speed * sin(angle ) * 5);
        }

    void drawAt (double x, double y)
        {
        txSelectFont ("Times New Roman", 18);
        txSetFillColor (ballcolor);
        txSetColor (ballcolor, 1);
        txCircle (x, y, radius);
        //txSetColor (ballcolor, 5);
        //txLine (x, y,  x - speed * cos(angle ) * 10, y + speed * sin(angle ) * 5);
        myAlphaBlend (txDC(), x - radius, y - radius, radius * 2, radius * 2, tun, 0, 0, 169, 169, 1);
        txSetColor (vectorcolor, vectorwidth);
        //txDrawText (x - radius - 65, y - radius - 25, x + radius + 65, y - radius - 15, name);
        //txLine (x, y,  x + speed * cos(angle ) * 10, y - speed * sin(angle ) * 5);
        }

    Ball (double xc, double yc, double rad, double ang, double spd, COLORREF fcolor, char gname[], int gid)
        {
        cords.x = xc;
        cords.y = yc;
        radius = rad;
        angle = ang ;
        speed = spd;
        ballcolor = fcolor;
        *name = *gname;
        hitcounter = 0;
        //*(thisChars.namech) = *gname;
        id = gid;
        }
    Ball (double xc, double yc, double rad, double ang, double spd, COLORREF fcolor, int number, int gid)
        {
        cords.x = xc;
        cords.y = yc;
        radius = rad;
        angle = ang ;
        speed = spd;
        ballcolor = fcolor;
        sprintf (name, "%d", number);
        hitcounter = 0;
        //sprintf (thisChars.namech, "%d", number);
        id = gid;
        }
    Ball ()
        {}
    void makeChar (BallChar *gchar)
        {
        //*(gchar->namech) = *name;
        gchar->hitnumch = hitcounter;
        }
    void move()
        {
        cords.x += speed * cos(angle ) * dt;
        cords.y -= speed * sin(angle ) * dt;
        //speed *= 1.001;
        if (dt != 1) dt = 1;
        }
    int GetHitCounter()
        {
        return hitcounter;
        }
    double getAngle()
        {
        return angle;
        }
    double getDistanceTo (double xto, double yto)
        {
        return sqrt((xto - cords.x) * (xto - cords.x) +
                    (yto - cords.y) * (yto - cords.y));
        }

    void makeCollisions (Ball others[], int bnum)
        {
        for (int i = 0; i < bnum; i++)
            {
            //printf ("id %d\n", others[i].getID());
            if (others[i].getID() != id &&
                        others[i].getDistanceTo (cords.x, cords.y) <=
                        others[i].getSpeed() + speed + others[i].getRadius() + radius)
                {
                //printf ("OOUCH\n");
                makeCollisionWith (others[i]);
                //getch();
                }
            }
        }
    double getRadius()
        {
        return radius;
        }
    double getSpeed()
        {
        return speed;
        }
    void addCollision (int addnum = 1)
        {
        hitcounter += addnum;
        thisChars.hitnumch += addnum;
        }

    void setNoCol (int gid)
        {
        noCollisionId = gid;
        }

    void moveRatio (double rat)
        {
        cords.x += speed*cos(angle)*rat;
        cords.y -= speed*sin(angle)*rat;
        }


    int makeCollisionWith (Ball wball)
        {
        if (noCollisionId == wball.getID())
            {
            noCollisionId = -1;
            printf ("i've Already had collision with this guy\n");
            return 0;
            }

        double biggerratio;
        double biggerspeed;
        double biggerradius;
        if (wball.getSpeed()/wball.getRadius() > speed/radius)
            {
            biggerratio = wball.getSpeed()/wball.getRadius() * 2;
            biggerspeed = wball.getSpeed();
            biggerradius = wball.getRadius();
            }
        else          //TODO
            {         //
            biggerratio = speed/radius * 2;
            biggerspeed = speed;
            biggerradius = radius;
            }

        for (int i = 0; i < biggerratio; i++)
            {
            if (testCollDoubPairs (wball, wball.getX() + cos (wball.getAngle()) * i/biggerratio,
                                       wball.getY() - cos (wball.getAngle()) * i/biggerratio,
                                       cords.x + cos (angle) * i/biggerratio,
                                       cords.y - cos (angle) * i/biggerratio))
                {
              //printf ("OUCH(%s)\n", name);
                //1 - i/biggerratio;
                this->addCollision();
                //angle = (getAngleTo(wball.getX(), wball.getY()) + 180) + angle;
                DoubPair dcv1 = DiPolToDecart (angle, speed);
                DoubPair dcv2 = DiPolToDecart (wball.getAngle(), wball.getSpeed());
              //printf ("dcv1 == %f && %f", dcv1.x, dcv1.y);
                //getch();
                double help = (double)(i - 1)/biggerratio;
                dt = 1 - help;
                cords.x += speed*cos(angle)*help;
                cords.y -= speed*sin(angle)*help;
                wball.moveRatio (help);
                SUPERDoubPair colresults;
                colresults = getBiPolSpeedAfterCollision (dcv1.x, dcv1.y, dcv2.x, dcv2.y,
                                        cords.x, cords.y, wball.getX(), wball.getY(),
                                        radius, wball.getRadius());
                angle = colresults.f.x;
                speed = colresults.f.y;
                wball.setAngle (colresults.s.x);
                wball.setSpeed (colresults.s.y);

                if (angle > 0) angle = (int)(angle)%360;
                else angle = -((int)(fabs(angle))%360);
                //getch();

                }
            return 0;

            }
        wball.setNoCol(id);
        }

    void setAngle (double get)
        {
        angle = get;
        }

    void setSpeed (double get)
        {
        speed = get;
        }

    bool testCollDoubPairs (Ball tball, double tgx, double tgy, double thx, double thy)
        {
        if (getDistanceBetween (tgx, tgy, thx, thy) <= tball.getRadius() + radius) return true;
        return false;
        }
    };

SUPERDoubPair getBiPolSpeedAfterCollision (double vx1, double vy1, double vx2, double vy2,
                                        double cx1, double cy1, double cx2, double cy2,
                                        double mass1, double mass2)
    {
    DoubPair deltac = {cx2 - cx1, cy2 - cy1};
    double v1ProjX = ProjVec (vx1, vy1, cx2 - cx1, cy2 - cy1);
    double v1ProjY = ProjVec (vx1, vy1, cy1 - cy2, cx2 - cx1);

    double v2ProjX = ProjVec (vx2, vy2, cx2 - cx1, cy2 - cy1);
    double v2ProjY = ProjVec (vx2, vy2, cy1 - cy2, cx2 - cx1);

    DoubPair v1NC = {((mass1 - mass2)*(v1ProjX)+2*mass2*v2ProjX)/(mass1+mass2), v1ProjY};
    DoubPair v2NC = {(2*mass2*v2ProjX+2*mass1*v1ProjX)/(mass1+mass2), v2ProjY};

    //printf ("v1ProjX == %f, v2ProjX == %f\n", v1ProjX, v2ProjX);

    DoubPair v1OC;
    DoubPair v2OC;

    v1OC.x = ProjVec (v1NC.x, v1NC.y, 1, 0);
    v1OC.y = ProjVec (v1NC.x, v1NC.y, 0, 1);

    v2OC.x = ProjVec (v2NC.x, v2NC.y, 1, 0);
    v2OC.y = ProjVec (v2NC.x, v2NC.y, 0, 1);

    printf ("DeltaVX1 OldCords == %f, VY - %f\n, DeltaVX2 OldCords == %f, VY - %f\n ", vx1 - v1OC.x, vy1 - v1OC.y, vx2 - v2OC.x, vy2 - v2OC.y);

    SUPERDoubPair answer;
    answer.f.y = LengthOf (v1OC.x, v1OC.y);
    answer.s.y = LengthOf (v2OC.x, v2OC.y);
    answer.f.x = (getAccurateAngle(v1OC.x, v1OC.y) +
                    getAccurateAngle(deltac.x, deltac.y));
    answer.s.x = (getAccurateAngle(v2OC.x, v2OC.y) +
                    getAccurateAngle(deltac.x, deltac.y));
    return answer;
    }

double getAccurateAngle (double x, double y)
    {
    if (LengthOf (x, y) == 0) x+= 0.00015;
    assert (LengthOf (x, y) != 0);
    assert (fabs(x/LengthOf(x, y)) <= 1);
    assert (fabs(y/LengthOf(x, y)) <= 1);
    if (x > 0 && y > 0) return -acos (x/LengthOf(x, y));
    if (x > 0 && y < 0) return  acos (x/LengthOf(x, y));
    if (x < 0 && y > 0) return -PI + asin (y/LengthOf(x, y));
    return PI + asin (y/LengthOf(x, y));
    }

double getDistanceBetween(double x1, double y1, double x2, double y2)
    {
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
    }


int SortBallsCharacteristics (BallChar chars[], int left, int right)
    {
    //printf ("AAAAAAAAAA");
    //txSleep (1000);
    int hleft = left;
    int hright = right;
    if (right <= left) return 0;
    if (right == left + 1)
        {
        if (chars[left].hitnumch > chars[right].hitnumch)
            {
            change (chars, left, right);
            }
        return 0;
        }
    //printchars (chars, left, right);
    int help;
    int midel = left + (right - left)/2;
    int midnum;

    while (left <= right)
        {
    // //printf ("\nleft(%d) <= right(%d)\n", left, right);
        midnum = chars [midel].hitnumch;
    //  //printf ("mid(%d) == %d\n", midel, midnum);
        if (!standsright (chars, left, midel)/* && right != left*/)
            {
    //      //printf ("\nleft(%d) == %d stays wrong\nrights ", left, chars[left].hitnumch);
            if (left > midel && right > midel)
                {
    //          //printf ("left and right both > mid => changing left and mid - 1 el\n");
                if (left == midel + 1)
                    {
                    change (chars, left, midel);
                    midel++;
                    }
                else
                    {
                    change (chars, midel, midel + 1);
                    midel++;
                    change (chars, left, midel - 1);
                    }
                }
            else
                {
                while (standsright (chars, right, midel)/* || (right == left && right != midel)*/)
                    {
    //              //printf ("(%d) == %d ", right, chars[right].hitnumch);
                    right--;
                    }
    //          //printf ("stay right\n");
    //          //printf ("and right(%d) == %d stays wrong\n", right, chars[right].hitnumch);
                change (chars, left, right);
    //          //printf ("changing left(%d) == %d and it\n", left, chars[left].hitnumch);
                if (midel == right)
                    {
                    midel = left;
    //              //printf ("midel is now %d == %d\n", midel, chars[midel].hitnumch);
                    }
                else
                    {
                    if (midel == left)
                        {
                        midel = right;
    //                  //printf ("midel is now %d == %d\n", midel, chars[midel].hitnumch);
                        }
                    }
                }
            }
        left++;
        }
    //printchars (chars, hleft, hright);
    //printf ("end---------------------------------------------------------\n");
    //getch();

    if (midel == hright) SortBallsCharacteristics (chars, hleft, midel - 1);
    else SortBallsCharacteristics (chars, hleft, midel);

    SortBallsCharacteristics (chars, midel + 1, hright);
    return 0;
    }

void printchars (BallChar chars[], int left, int right)
    {
    for (int i = left; i <= right; i++)
        {
      //printf ("%d ", chars[i].hitnumch);
        }
  //printf ("\n");
    }

DoubPair DiPolToDecart (double angle, double length)
    {
    //printf ("returning(ditodec) %f & %f", cos(angle) * length, -sin(angle) * length);
    return {cos(angle) * length, -sin(angle) * length};
    }

double LengthOf (double x, double y)
    {
    return sqrt(x*x + y*y);
    }


DoubPair DecartToTDiPol (double dx, double dy)
    {
    return {atan(dy/dx)*(dx/fabs(dx)), getDistanceBetween(0, 0, dx, dy)};
    }

double ScalMult (double x1, double y1, double x2, double y2)
    {
    return x1*x2 + y1*y2;
    }

double ProjVec (double x1, double y1, double x2, double y2)
    {
    //DoubPair answer;
    double answer;
    double dp = ScalMult (x1, y1, x2, y2);
  //printf ("gettingveloc == %f & %f, dp == %f\n", x1, y1, dp);
    //answer.x = (dp/(x2*x2+y2*y2))*x2;
    //answer.y = (dp/(x2*x2+y2*y2))*y2;
  //printf ("returningproj == %f & %f\n", answer.x, answer.y);
    answer = dp/LengthOf(x2, y2);
    return answer;
    }

void initChars (BallChar chars[], Ball balls[], int size)
    {
    for (int i = 0; i < size; i++)
        {
        chars[i] = balls[i].thisChars;
        chars[i].id = i;
        }
    }



void drawBalls (Ball balls[], int bnum)
    {
    for (int i = 0; i < bnum; i++)
        {
        balls[i].draw();
        }
    }

void moveBalls (Ball balls[], int bnum)
    {
    for (int i = 0; i < bnum; i++)
        {
        balls[i].move();
        }
    }

void drawHitTable (Ball balls[], const int bnum, double x1, double y1, double x2, double y2, int topsnum)
    {
    txSetColor (TX_WHITE, 1);
    double xsize = x2 - x1;
    double ysize = y2 - y1;
    double liney = ysize/(topsnum + 1);
    txLine (x1 + 20, y1, x1 + 20, y2);
    txDrawText (x1 + 20, y1, x2, y1 + liney, "Таблица Рекордов по Отскакиваниям");
    BallChar chars[bnum];
    initChars (chars, balls, bnum);
    SortBallsCharacteristics (chars, 0, bnum - 1);
    if (bnum < topsnum) topsnum = bnum;
    char help[16] = {};
    for (int i = 0; i < topsnum; i++)
        {
        txLine (x1, y1 + liney * (i + 1), x2, y1 + liney * (i + 1));
        sprintf (help, "%d", i + 1);
        txDrawText (x1, y1 + liney * (i + 1), x1 + 20, y1 + liney * (i + 2), help);
        txDrawText (x1 + 20, y1 + liney * (i + 1), x2, y1 + liney * (i + 2), balls[chars[bnum - i - 1].id].name);
        balls[chars[bnum - i - 1].id].drawAt(x2 - 10, y1  + liney * (i + 1.5));
        }
    txLine (x1, y2, x2, y2);
    }

void testBalls (Ball balls[], int bnum)
    {
    for (int i = 0; i < bnum; i++)
        {
        balls[i].testWallHit();
        }
    }

void makeCollisionsInLauncher (Ball balls[], int bnum)
    {
    for (int i = 0; i < bnum; i++)
        {
        balls [i].makeCollisions (balls, bnum);
        }
    }

bool standsright (BallChar chars[], int tests, int mid)
    {
    if (tests < mid)
        {
        if (chars[tests].hitnumch < chars[mid].hitnumch) return true;
        }
    else
        {
        if (chars[tests].hitnumch > chars[mid].hitnumch) return true;
        }
    return false;
    }


void initBalls (Ball balls[], int bnum, HDC helptun)
    {
    for (int i = 0; i < bnum; i++)
        {
        Ball hball ((double)(i)/(double)(bnum) * txGetExtentX(), (double)(i)/(double)(bnum) * txGetExtentY(),
                    20 + i, (i - bnum/2) * 15, 5, RGB (rand()%255, rand()%255, rand()%255), i, i);

        balls[i] = hball;
        balls[i].setTun (helptun);
        }
    }

void change (BallChar chars[], int first, int second)
    {
    BallChar helpchar = {};
    helpchar = chars[first];
    chars[first] = chars[second];
    chars[second] = helpchar;
    }


bool myAlphaBlend (HDC dest, double xDest, double yDest, double width1, double height1,
                   HDC src,  double xSrc /*= 0*/, double ySrc /*= 0*/, double width2, double height2, double alpha /*= 1.0*/)
    {
    _TX_IF_TXWINDOW_FAILED        return false;
    _TX_IF_ARGUMENT_FAILED (dest) return false;
    _TX_IF_ARGUMENT_FAILED (src)  return false;

    if (alpha < 0) alpha = 0;
    if (alpha > 1) alpha = 1;

    BLENDFUNCTION blend = { AC_SRC_OVER, 0, (BYTE) ROUND (alpha * 255), AC_SRC_ALPHA };
    return (Win32::AlphaBlend)?
        txGDI (!!(Win32::AlphaBlend (dest, ROUND (xDest), ROUND (yDest), ROUND (width1), ROUND (height1),
                                     src,  ROUND (xSrc),  ROUND (ySrc),  ROUND (width2), ROUND (height2), blend)))
    :
        txGDI (!!(Win32::BitBlt     (dest, ROUND (xDest), ROUND (yDest), ROUND (width1), ROUND (height1),
                                     src,  ROUND (xSrc),  ROUND (ySrc),  SRCCOPY))), false;
    }
