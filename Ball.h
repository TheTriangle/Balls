#define DEGREEMODIFIER 0.0175

class BallChar
    {
    public:
    char namech [16] = {};
    int hitnumch = 0;
    };

void printchars (BallChar chars[], int left, int right);
int SortBallsCharacteristics (BallChar chars[], int left, int right);
bool standsright (BallChar chars[], int tests, int mid);
void change (BallChar chars[], int first, int second);
class Ball
    {
    private:
    COLORREF ballcolor;
    COLORREF vectorcolor = RGB (200, 200, 200);
    POINT cords;
    int vectorwidth = 5;
    double radius;
    double angle;
    char name[16];
    double speed;
    int hitcounter;
    public:
    BallChar thisChars; //TODO ��������� ��� ����.����.private
    bool testWallHit ()
        {
        if (cords.x + radius > txGetExtentX())
            {
            cords.x = txGetExtentX() - radius;
            if (angle >= 0) angle = 180 - angle;
            else angle = -180 - angle;
            return true;
            hitcounter++;
            thisChars.hitnumch++;
            }
        if (cords.x - radius < 0)
            {
            cords.x = radius;
            if (angle >= 0) angle = 180 - angle;
            else angle = -180 - angle;
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
            thisChars.namech[i] = newname[i];
            }
        }
    void setRadius (double grad)
        {
        radius = grad;
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

    double getX()
        {
        return cords.x;
        }
    double getY()
        {
        return cords.y;
        }
    POINT getCords()
        {
        return cords;
        }
    void draw ()
        {
        txSelectFont ("Times New Roman", 18);
        txSetFillColor (ballcolor);
        txSetColor (ballcolor, 1);
        txCircle (cords.x, cords.y, radius);
        txSetColor (vectorcolor, vectorwidth);
        txDrawText (cords.x - radius - 65, cords.y - radius - 25, cords.x + radius + 65, cords.y - radius - 15, name);
        txLine (cords.x, cords.y,  cords.x + speed * cos(angle * DEGREEMODIFIER) * 10, cords.y - speed * sin(angle * DEGREEMODIFIER) * 5);
        }
    Ball (double xc, double yc, double rad, double ang, double spd, COLORREF fcolor, char gname[])
        {
        cords.x = xc;
        cords.y = yc;
        radius = rad;
        angle = ang;
        speed = spd;
        ballcolor = fcolor;
        *name = *gname;
        hitcounter = 0;
        *(thisChars.namech) = *gname;
        }
    Ball (double xc, double yc, double rad, double ang, double spd, COLORREF fcolor, int number)
        {
        cords.x = xc;
        cords.y = yc;
        radius = rad;
        angle = ang;
        speed = spd;
        ballcolor = fcolor;
        sprintf (name, "%d", number);
        hitcounter = 0;
        sprintf (thisChars.namech, "%d", number);
        }
    Ball ()
        {}
    void makeChar (BallChar *gchar)
        {
        *(gchar->namech) = *name;
        gchar->hitnumch = hitcounter;
        }
    void move(double dt)
        {
        cords.x += speed * cos(angle * DEGREEMODIFIER) * dt;
        cords.y -= speed * sin(angle * DEGREEMODIFIER) * dt;
        }
    int GetHitCounter()
        {
        return hitcounter;
        }
    double getAngle()
        {
        return angle;
        }
    double getDistanceTo (Ball target)
        {
        return sqrt((target.getX() - cords.x) * (target.getX() - cords.x) +
                    (target.getY() - cords.y) * (target.getY() - cords.y));
        }
    //void testCollisions (Ball balls[], int bnum)
    //    {
    //    for (int i = 0; i < bnum; i++)
    //        {
    //        if
    };


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
     //   printf ("\nleft(%d) <= right(%d)\n", left, right);
        midnum = chars [midel].hitnumch;
     //   printf ("mid(%d) == %d\n", midel, midnum);
        if (!standsright (chars, left, midel)/* && right != left*/)
            {
     //       printf ("\nleft(%d) == %d stays wrong\nrights ", left, chars[left].hitnumch);
            while (standsright (chars, right, midel)/* || (right == left && right != midel)*/)
                {
     //           printf ("(%d) == %d ", right, chars[right].hitnumch);
                right--;
                }
            if (left > midel && right > midel)
                {
     //           printf ("left and right both < mid => changing left and mid + 1 el\n");
                change (chars, midel, midel + 1);
                midel++;
                change (chars, left, midel - 1);
                }
            else
                {
     //           printf ("stay right\n");
     //           printf ("and right(%d) == %d stays wrong\n", right, chars[right].hitnumch);
                change (chars, left, right);
     //           printf ("changing left(%d) == %d and it\n", left, chars[left].hitnumch);
                if (midel == right)
                    {
                    midel = left;
     //               printf ("midel is now %d == %d\n", midel, chars[midel].hitnumch);
                    }
                else
                    {
                    if (midel == left)
                        {
                        midel = right;
     //                   printf ("midel is now %d == %d\n", midel, chars[midel].hitnumch);
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
        printf ("%d ", chars[i].hitnumch);
        }
    printf ("\n");
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


void change (BallChar chars[], int first, int second)
    {
    BallChar helpchar = {};
    helpchar = chars[first];
    chars[first] = chars[second];
    chars[second] = helpchar;
    }
