#define DEGREEMODIFIER 0.0175

class BallChar
    {
    public:
    char namech [16] = {};
    int hitnumch = 0;
    };
void SortBallsCharacteristics (BallChar chars[], int left, int right);
bool standsright (BallChar chars[], int tests, int mid);
void change (BallChar chars[], int first, int second);
class Ball
    {
    private:
    COLORREF ballcolor;
    POINT cords;
    double radius;
    double angle;
    char name[];
    double speed;
    int hitcounter;
    public:
    bool testWallHit ()
        {
        if (cords.x + radius > txGetExtentX())
            {
            cords.x = txGetExtentX() - radius;
            if (angle >= 0) angle = 180 - angle;
            else angle = -180 - angle;
            return true;
            hitcounter++;
            }
        if (cords.x - radius < 0)
            {
            cords.x = radius;
            if (angle >= 0) angle = 180 - angle;
            else angle = -180 - angle;
            hitcounter++;
            return true;
            }
        if (cords.y + radius > txGetExtentY())
            {
            cords.y = txGetExtentY() - radius;
            angle = -angle;
            hitcounter++;
            return true;
            }
        if (cords.y - radius < 0)
            {
            cords.y = radius;
            angle = -angle;
            hitcounter++;
            return true;
            }
        return false;
        }
    void draw ()
        {
        txSelectFont ("Times New Roman", 30);
        txSetFillColor (ballcolor);
        txCircle (cords.x, cords.y, radius);
        txDrawText (cords.x - radius - 15, cords.y - radius - 25, cords.x + radius + 15, cords.y - radius - 15, name);
        txSetColor (RGB (200, 200, 200), 5);
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

    };


void SortBallsCharacteristics (BallChar chars[], int left, int right)
    {
    int help;
    int midel = right - left/2;
    int midnum;
    while (left <= right)
        {
        printf ("%d <= %d\n", left, right);
        midnum = chars [midel].hitnumch;
        if (!standsright (chars, left, midel))
            {
            while (standsright (chars, right, midel))
                {
                printf ("right stands right\n", left, right);
                right--;
                }
            change (chars, left, right);
            if (midel == right)
                {
                midel = left;
                }
            }
        left++;
        }
    SortBallsCharacteristics (chars, left, midel);
    SortBallsCharacteristics (chars, midel + 1, right);
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
