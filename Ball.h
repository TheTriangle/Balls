#define DEGREEMODIFIER 0.01745
#define PI 3.141593
COLORREF textnamescolor = RGB (255, 255, 255);
COLORREF texttabcolor = RGB (233, 217, 109);
COLORREF vectorcolor = RGB (255, 255, 255);
COLORREF tablecolor = RGB(233, 217, 109);

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
    int idch_;
    int hitnumch_ = 0;
    BallChar (int gid, int ghit):
        idch_(gid),
       hitnumch_(ghit)
        {}

    BallChar():
        idch_(-1)
        {}
    BallChar& operator= (const BallChar& right)
        {
        idch_ = right.idch_;
        hitnumch_ = right.hitnumch_;
        return *this;
        }
    };

class MyVector
    {
    public:
    double x;
    double y;
    MyVector(double getx, double gety):
        x(getx),
        y(gety)
        {}
    MyVector(DoubPair gspeed):
        x(gspeed.x),
        y(gspeed.y)
        {}

    MyVector operator+ (MyVector right)
        {
        return {x + right.x, y + right.y};
        }
    MyVector operator* (double right)
        {
        return {x * right, y * right};
        }
    MyVector operator/ (double right)
        {
        return {x / right, y / right};
        }
    double operator* (MyVector right)
        {
        return (x * (right.x) + y * (right.y));
        }
    MyVector operator- (MyVector right)
        {
        return {x - right.x, y - right.y};
        }

    double length();
    };

double MyVector::length()
    {
    return sqrt (x * x + y * y);
    }

//void initBalls (Ball balls[], int bnum);
class Ball;
class BallGroup;
//void initBalls (Ball balls[], int bnum, HDC helptun);
//void testBalls (Ball balls[], int bnum);
void drawHitTable (BallGroup balls, const int bnum, double x1, double y1, double x2, double y2, int topsnum = 5);
//void drawBalls (Ball balls[], int bnum);
//void moveBalls (Ball balls[], int bnum);
void initChars (BallChar chars[], Ball balls[], int size);
bool myAlphaBlend (HDC dest, double xDest, double yDest, double width1, double height1,
                   HDC src,  double xSrc /*= 0*/, double ySrc /*= 0*/, double width2, double height2, double alpha = 1.0);
double getAccurateAngle (double x, double y);
double ProjVec (double x1, double y1, double x2, double y2);
double ScalMult (double x1, double y1, double x2, double y2);
DoubPair DecartToTDiPol (double dx, double dy);
double LengthOf (double x, double y);
DoubPair DiPolToDecart (double angle_, double length);
SUPERDoubPair getBiPolSpeedAfterCollision (double vx1, double vy1, double vx2, double vy2,
                                        double cx1, double cy1, double cx2, double cy2,
                                        double mass1, double mass2);
double getDistanceBetween(double x1, double y1, double x2, double y2);
void printchars (BallChar chars[], int left, int right);
int SortBallsCharacteristics (BallChar chars[], int left, int right);
bool standsright (BallChar chars[], int tests, int mid);
void makeCollisionsInLauncher (Ball balls[], int bnum);
double getAngleBetweenVecs (double x1, double y1, double x2, double y2);
void change (BallChar chars[], int first, int second);

const int maxballsnum = 20;
class Ball
    {
    private:
    double radius_;
    //double speed_.x;     -|
    //double speed_.y;     -|
    MyVector speed_;//<+
    double angle_;
    COLORREF ballcolor_;
    int hitcounter_;
    int id_;
    DoubPair cords_;

    HDC tun_;
    int noCollisionId_ = 0;
    int vectorwidth_ = 5;
    double dt_ = 1;


    public:
    char name_[16];
    BallChar thisChars_; //TODO РїРµСЂРµРЅРµСЃС‚Рё РїРѕРґ СЃРїРµС†.РґРѕСЃС‚.private

    void setSpeed (MyVector get);
    void setName (char newname[]);                            //     -------      -------------  -------------
    void setRadius (double grad);                             //   -----------    -------------  -------------
    void setTun (HDC* gaveim);                                //   ---     ----   --                   --
    void setColor (COLORREF gcol);                            //    ---           --                   --
    void setVectorColor (COLORREF gcol, int gwidth = 5);      //     ---          --                   --
    void setCords (double gx, double gy);                     //      ---         --                   --
    void setBallColor(COLORREF get);                          //       ----       -----------          --
    void setID(int get);                                      //         ---      -----------          --
    void setNoCol (int gid);                                  //          ---     --                   --
    void setvx (double get);                                  //           ---    --                   --
    void setvy (double get);                                  //           ---    --                   --
    void setAngle (double get);                               //         ----     --                   --
    void setChar (BallChar *gchar);                           //    ---------     --------------       --
    void setSpeed (double get);                               //    ------        --------------       --

    //-----------------------------------------------------------------------------

    char* getName();
    int getHitCounter();                                      //     ////////         /////////////     ///////////////
    double getAngleBetweenSpeed(double gx, double gy);        //    //      //        /////////////     ///////////////
    double getAngle();                                        //    //       //       //                      ///
    double getDistanceTo (double xto, double yto);            //    //                //                      ///
    double getvx();                                           //    //                //                      ///
    double getvy();                                           //    //                //                      ///
    double getRadius();                                       //    //                //                      ///
    double getSpeed();                                        //    //                //////////              ///
    double getAngleTo(double xto, double yto);                //    //     ////       //////////              ///
    double getX();                                            //    //    //  //      //                      ///
    double getY();                                            //    //          //    //                      ///
    int getID();                                              //    //          //    //                      ///
    COLORREF getColor();                                      //    //         //     //                      ///
    HDC* getTun();                                            //     //       //      /////////////           ///
    DoubPair getCords();                                      //       ///////        /////////////           ///

    //-----------------------------------------------------------------------------

    void draw ();
    void drawAt (double x, double y);
    int makeDirectCollisionWith (Ball* wball);
    Ball (DoubPair gcords, double rad, double gvx, double gvy, COLORREF fcolor, char gname[], int gid);
    Ball (DoubPair gcords, double rad, double gvx, double gvy, COLORREF fcolor, int number, int gid);
    BallChar* getChar();
    Ball ();
    ~Ball();
    void move();
    int makeCollisions (Ball others[], int bnum);
    void addCollision (int addnum = 1);
    void moveRatio (double rat);
    int makeCollisionWith (Ball* wball);
    bool testWallHit ();
    bool testCollDoubPairs (Ball* tball, double tgx, double tgy, double thx, double thy);

    Ball& operator=(Ball right);

    };



Ball& Ball::operator=(Ball right)
    {
    this->setRadius(right.getRadius());
    this->setvx(right.getvx());
    this->setvy(right.getvy());
    this->setColor(right.getColor());
    this->setChar(right.getChar());
    this->setID(right.getID());
    this->setCords(right.getX(), right.getY());
    this->setTun(right.getTun());
    this->setName(right.getName());
    return *this;
    }

char* Ball::getName()
    {
    return name_;
    }

COLORREF Ball::getColor()
    {
    return ballcolor_;
    }

HDC* Ball::getTun()
    {
    return &tun_;
    }

void Ball::setID(int get)
    {
    id_ = get;
    }

BallChar* Ball::getChar()
    {
    return &thisChars_;
    }

class BallGroup
    {
    private:
    int ballsnum_;
    Ball arr_[maxballsnum];
    public:
    void moveAll();
    void drawAll();
    void testAll();
    void putToEnd (Ball gball);
    void deleteBall (int num);
    void initChars (BallChar chars[]);
    void initBalls (HDC helptun);
    void makeCollisionsInLauncher ();
    BallGroup (int gballs);
    Ball& operator[](int number)
        {
        return arr_[number];
        }
    };

void BallGroup::makeCollisionsInLauncher ()
    {
    for (int i = 0; i < ballsnum_; i++)
        {
        arr_[i].makeCollisions (arr_, ballsnum_);
        }
    }

void BallGroup::initBalls (HDC helptun)
    {
    //printf ("ballsnum == %d\n", ballsnum_);
    for (int i = 0; i < ballsnum_; i++)
        {
        arr_[i] = Ball({(double)(i)/(double)(ballsnum_) * txGetExtentX(), (double)(i)/(double)(ballsnum_) * txGetExtentY()},
                    20 + i, /*rand()%20 - 10*/rand()%20 - 10, /*rand()%20 - 10*/rand()%20 - 10, RGB (rand()%255, rand()%255, rand()%255), i, i);

        //assert (!helptun);
        arr_[i].setTun (&helptun);
        //printf ("i am setting(%d)\n", i);
        //getch();
        }
    }

BallGroup::BallGroup (int gballs):
        ballsnum_(gballs),
        arr_({})
        {
        //for (int i = 0; i < gballs; i++)
        //    {
        //    Ball help;
        //    arr_[i] = help;
        //    }
        }


void BallGroup::putToEnd (Ball gball)
    {
    assert (ballsnum_ + 1 <= maxballsnum);
    arr_[ballsnum_] = gball;
    ballsnum_++;
    }

void BallGroup::deleteBall (int num)
    {
    arr_[num] = arr_[ballsnum_-1];
    arr_[ballsnum_ - 1].~Ball();
    ballsnum_--;
    }

void BallGroup::moveAll()
    {
    for (int i = 0; i < ballsnum_; i++)
        {
        arr_[i].move();
        }
    }

void BallGroup::drawAll()
    {
    for (int i = 0; i < ballsnum_; i++)
        {
        arr_[i].draw();
        }
    }

bool Ball::testWallHit ()
    {
    if (cords_.x + radius_ > txGetExtentX())
        {
        //cords.x = txGetExtentX() - radius_;
        //if (angle >= 0) angle_ = PI - angle_;
        //else angle_ = -PI - angle_;
        //return true;
        //hitcounter++;
        //thisChars.hitnumch_++;
        if (speed_.x > 0) speed_.x = speed_.x * -1;
        return true;
        }
    if (cords_.x - radius_ < 0)
        {
        //cords.x = radius_;
        //if (angle >= 0) angle_ = PI - angle_;
        //else angle_ = -PI - angle_;
        //hitcounter++;
        //thisChars.hitnumch_++;
        if (speed_.x < 0) speed_.x = speed_.x * -1;
        return true;
        }
    if (cords_.y + radius_ > txGetExtentY())
        {
        //cords.y = txGetExtentY() - radius_;
        //angle = -angle;
        //hitcounter++;
        //thisChars.hitnumch_++;
        if (speed_.y > 0) speed_.y = speed_.y * -1;
        return true;
        }
    if (cords_.y - radius_ < 0)
        {
        //cords.y = radius_;
        //angle = -angle;
        //hitcounter++;
        //thisChars.hitnumch_++;
        if (speed_.y< 0) speed_.y = speed_.y * -1;
        return true;
        }
    return false;
    }
void Ball::setName (char newname[])
    {
    for (int i = 0; i < 16; i++)
        {
        name_[i] = newname[i];
        //thisChars.namech[i] = newname[i];
        }
    }
void Ball::setRadius (double grad)
    {
    radius_ = grad;
    }

Ball::~Ball()
    {
    if (!tun_) txDeleteDC(tun_);
    //printf ("ball %s died\n", name_);
    }

void Ball::setTun (HDC* gaveim)
    {
    tun_ = *gaveim;
    }

void Ball::setColor (COLORREF gcol)
    {
    ballcolor_ = gcol;
    }

void Ball::setVectorColor (COLORREF gcol, int gwidth)
    {
    vectorcolor = gcol;
    vectorwidth_ = gwidth;
    }
void Ball::setCords (double gx, double gy)
    {
    cords_.x = gx;
    cords_.y = gy;
    }
int Ball::getID()
    {
    return id_;
    }
double Ball::getAngleTo(double xto, double yto)
    {
    assert (fabs((yto - cords_.y)/getDistanceTo(xto, yto)) <= 1);
    return getAccurateAngle(xto - cords_.x, yto - cords_.y);
    }
void Ball::setSpeed (MyVector get)
    {
    speed_ = get;
    }
double Ball::getX()
    {
    return cords_.x;
    }
double Ball::getY()
    {
    return cords_.y;
    }
DoubPair Ball::getCords()
    {
    return cords_;
    }
void Ball::draw ()
    {
    txSelectFont ("Comic Sans SM", 27);
    txSetFillColor (ballcolor_);
    txSetColor (ballcolor_, 1);
    //txLine(cords.x, cords_.y, rand()%txGetExtentX()/2, 0);
    //txLine(cords.x, cords_.y, txGetExtentX()/2, txGetExtentY());
    txCircle (cords_.x, cords_.y, radius_);
    //txSetColor (ballcolor, 5);
    //txLine (cords.x, cords_.y,  cords_.x - speed_ * cos(angle ) * 10, cords_.y + speed_ * sin(angle ) * 5);
    myAlphaBlend (txDC(), cords_.x - radius_, cords_.y - radius_, radius_ * 2, radius_ * 2, tun_, 0, 0, 169, 169, 1);
    txSetColor (vectorcolor, vectorwidth_);
    txDrawText (cords_.x - radius_ - 65, cords_.y - radius_ - 55, cords_.x + radius_ + 65, cords_.y - radius_ - 15, name_);
    //txLine (cords_.x, cords_.y,  cords_.x + speed_.x * 5, cords_.y + speed_.y * 5);
    }

void Ball::drawAt (double x, double y)
    {
    txSelectFont ("Comic Sans SM", 18);
    txSetFillColor (ballcolor_);
    txSetColor (ballcolor_, 1);
    txCircle (x, y, radius_);
    //txSetColor (ballcolor, 5);
    //txLine (x, y,  x - speed_ * cos(angle ) * 10, y + speed_ * sin(angle ) * 5);
    myAlphaBlend (txDC(), x - radius_, y - radius_, radius_ * 2, radius_ * 2, tun_, 0, 0, 169, 169, 1);
    txSetColor (vectorcolor, vectorwidth_);
    //txDrawText (x - radius_ - 65, y - radius_ - 25, x + radius_ + 65, y - radius_ - 15, name_);
    //txLine (x, y,  x + speed_ * cos(angle ) * 10, y - speed_ * sin(angle ) * 5);
    }

Ball::Ball (DoubPair gcords, double rad, double gvx, double gvy, COLORREF fcolor, char gname[], int gid):
    radius_(rad),
    //speed_.x(gvx),
    //speed_.y(gvy),
    speed_(gvx, gvy),
    angle_(getAccurateAngle(gvx, gvy)),
    ballcolor_(fcolor),
    hitcounter_(0),
    //*(thisChars.namech)(*gname),
    id_(gid),
    cords_(gcords),
    tun_ (NULL),
    noCollisionId_ (0),
    thisChars_(-1, 0)
    {
    *name_ = *gname;
    }
Ball::Ball (DoubPair gcords, double rad, double gvx, double gvy, COLORREF fcolor, int number, int gid):
    radius_(rad),
    //speed_.x(gvx),
    //speed_.y(gvy),
    speed_(gvx, gvy),
    angle_(getAccurateAngle(gvx, gvy)),
    ballcolor_(fcolor),
    hitcounter_(0),
    //sprintf (thisChars.namech, "%d", number)),
    id_(gid),
    cords_(gcords),
    tun_ (NULL),
    noCollisionId_ (0),
    thisChars_(-1, 0)
    {
    sprintf (name_, "%d", number);
    }
Ball::Ball ():
    radius_(10),
    //speed_.x(0),
    //speed_.y(0),
    speed_(0, 0),
    angle_(getAccurateAngle(0, 0)),
    ballcolor_(RGB (0, 204, 204)),
    hitcounter_(0),
    //sprintf (thisChars.namech, "%d", number)),
    id_(-2),
    cords_({-100, -100}),
    tun_ (NULL),
    noCollisionId_ (0),
    thisChars_(-1, 0)
    {
    sprintf (name_, "Unnamed");
    }
void Ball::setChar (BallChar *gchar)
    {
    //*(gchar->namech) = *name;
    gchar->hitnumch_ = hitcounter_;
    }
void Ball::move()
    {
    //if (vx > 20) speed_.x = 20;
    //if (vy > 20) speed_.y = 20;
    //if (vx < -20) speed_.x = -20;
    //if (vy < -20) speed_.y = -20;
    cords_.x += speed_.x;
    cords_.y += speed_.y;
    //speed *= 1.001;
    if (fabs(dt_ - 1) > 0) dt_ = 1;
    }
int Ball::getHitCounter()
    {
    return hitcounter_;
    }
double Ball::getAngle()
    {
    return angle_;
    }
double Ball::getDistanceTo (double xto, double yto)
    {
    return sqrt((xto - cords_.x) * (xto - cords_.x) +
                (yto - cords_.y) * (yto - cords_.y));
    }

int Ball::makeCollisions (Ball others[], int bnum)
    {
    for (int i = 0; i < bnum; i++)
        {
        //printf ("id %d\n", others[i].getID());
        if (others[i].getID() != id_ &&
                    others[i].getDistanceTo (cords_.x, cords_.y) <=
                    others[i].getSpeed() + speed_.length() + others[i].getRadius() + radius_)
            {
            //printf ("OOUCH\n");
            //if (fabs (getAngleBetweenSpeed(others[i].getX(), others[i].getY())) < PI/1.3)
            //    {
            makeCollisionWith (&others[i]);// == 1) others[i].makeCollisionWith(this);
            //    }
            //getch();
            }
        }
    return 0;
    }

double Ball::getRadius()
    {
    return radius_;
    }

double Ball::getSpeed()
    {
    return LengthOf(speed_.x, speed_.y);
    }
void Ball::addCollision (int addnum)
    {
    hitcounter_ += addnum;
    thisChars_.hitnumch_ += addnum;
    }

void Ball::setNoCol (int gid)
    {
    noCollisionId_ = gid;
    }

void Ball::moveRatio (double rat)
    {
    cords_.x += speed_.x*rat;
    cords_.y += speed_.y*rat;
    }

double Ball::getAngleBetweenSpeed(double gx, double gy)
    {
    return getAccurateAngle(speed_.x, speed_.y) - this->getAngleTo(gx, gy);
    }


int Ball::makeCollisionWith (Ball* wball)
    {
    double biggerratio = 0;
    if (LengthOf(wball->getvx(), wball->getvy())/wball->getRadius() > speed_.length()/radius_)
        {
        biggerratio = LengthOf(wball->getvx(), wball->getvy())/wball->getRadius()*10.3;
        //biggerspeed = LengthOf(wball->getvx(), wball->getvy());
        //biggerradius = wball->getRadius();
        }
    else          //TODO
        {         //
        biggerratio = LengthOf(speed_.x, speed_.y)/radius_*10.3;
        //biggerspeed = LengthOf(speed_.x, speed_.y);
        //biggerradius = radius_;
        }
    int retnum = 0;
    for (int i = 0; i < biggerratio; i++)
        {
        if (testCollDoubPairs (wball, wball->getX() + speed_.x * (double)(i)/(double)(biggerratio),
                                    wball->getY() + speed_.y * (double)(i)/(double)(biggerratio),
                                    cords_.x + speed_.x * (double)(i)/(double)(biggerratio),
                                    cords_.y + speed_.y * (double)(i)/(double)(biggerratio)))
            {
            //printf ("OUCH(%s)\n", name_);
            //1 - i/biggerratio;
            this->addCollision();
            wball->addCollision();
            double help = (double)(i - 1)/biggerratio;
            dt_ = 1 - help;
            cords_.x += speed_.x*help;
            cords_.y += speed_.y*help;
            wball->moveRatio (help);
            this->makeDirectCollisionWith (wball);//getBiPolSpeedAfterCollision (dcv1.x, dcv1.y, dcv2.x, dcv2.y,
                                                    //cords_.x, cords_.y, wball->getX(), wball->getY(),
                                                    //radius_, wball->getRadius());
            retnum = 1;
            }
        }
     return retnum;
     }



int Ball::makeDirectCollisionWith (Ball* wball)
    {
    if (getAngleBetweenVecs (wball->getX() - cords_.x, wball->getY() - cords_.y,
                             -(wball->getvx() - speed_.x),     -(wball->getvy() - speed_.y))     > PI/2) return 0;
    MyVector thisImp = speed_ * radius_;

    MyVector thatSpeed (wball->getvx(), wball->getvy());
    MyVector thatImp = thatSpeed * wball->getRadius();

    double distance = LengthOf (wball->getX() - cords_.x, wball->getY() - cords_.y);

    MyVector systemn ((wball->getX() - cords_.x)/distance, (wball->getY() - cords_.y)/distance);
    MyVector systemm (-systemn.y, systemn.x);

    MyVector thisPn = systemn * (thisImp * systemn);
    MyVector thisPm = thisImp - thisPn;

    MyVector thatPn = systemn * (thatImp * systemn);
    MyVector thatPm = thatImp - thatPn;

    speed_ = ((thatPn + thisPm)/radius_);
    wball->setSpeed ((thisPn + thatPm)/wball->getRadius());
    return 1;
    }
                    //http://storage.ded32.net.ru/Lib/Doc/AnalyticApproach2010.pdf


double Ball::getvx()
    {
    return speed_.x;
    }

double Ball::getvy()
    {
    return speed_.y;
    }

void Ball::setvx (double get)
    {
    speed_.x = get;
    }

void Ball::setvy (double get)
    {
    speed_.y = get;
    }

void Ball::setAngle (double get)
    {
    angle_ = get;
    }


bool Ball::testCollDoubPairs (Ball* tball, double tgx, double tgy, double thx, double thy)
    {
    if (getDistanceBetween (tgx, tgy, thx, thy) <= tball->getRadius() + radius_) return true;
    return false;
    }


/*SUPERDoubPair getBiPolSpeedAfterCollision (double vx1, double vy1, double vx2, double vy2,
                                        double cx1, double cy1, double cx2, double cy2,
                                        double mass1, double mass2)
    {
    //DoubPair deltac = {cx2 - cx1, cy2 - cy1};
    double v1ProjX = ProjVec (vx1, vy1, cx2 - cx1, cy2 - cy1);
    double v1ProjY = ProjVec (vx1, vy1, cy1 - cy2, cx2 - cx1);

    double v2ProjX = ProjVec (vx2, vy2, cx2 - cx1, cy2 - cy1);
    double v2ProjY = ProjVec (vx2, vy2, cy1 - cy2, cx2 - cx1);

    //printf ("hitted\n");
    DoubPair v1NC = {((mass1 - mass2)*(v1ProjX)+2*mass2*v2ProjX)/(mass1+mass2), v1ProjY};
    DoubPair v2NC = {((mass2 - mass1)*(v2ProjX)+2*mass1*v1ProjX)/(mass1+mass2), v2ProjY};


    DoubPair v1OC = {};
    DoubPair v2OC = {};

    v1OC.x = ProjVec (v1NC.x, v1NC.y, 1, 0);
    v1OC.y = ProjVec (v1NC.x, v1NC.y, 0, 1);

    v2OC.x = ProjVec (v2NC.x, v2NC.y, 1, 0);
    v2OC.y = ProjVec (v2NC.x, v2NC.y, 0, 1);

    //printf ("v2given == %f, %f\nreturned == %f, %f\n", speed_.x2, speed_.y2, v2OC.x, v2OC.y);
    //printf ("v1given == %f, %f\nreturned == %f, %f\n", speed_.x1, speed_.y1, v1OC.x, v1OC.y);
    //printf ("DeltaVX1 OldCords == %f, speed_.y - %f\n, DeltaVX2 OldCords == %f, speed_.y - %f\n ", speed_.x1 - v1OC.x, speed_.y1 - v1OC.y, speed_.x2 - v2OC.x, speed_.y2 - v2OC.y);

    SUPERDoubPair answer = {};
    answer.f.x = v1OC.x;
    answer.f.y = v1OC.y;
    answer.s.x = v2OC.x;
    answer.s.y = v2OC.y;
    return answer;
    }*/

double getAccurateAngle (double x, double y)
    {
    if (LengthOf (x, y) <= 0.0015) x+= 0.00015;
    assert (fabs(LengthOf (x, y)) > 0.0);
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
        if (chars[left].hitnumch_ > chars[right].hitnumch_)
            {
            change (chars, left, right);
            }
        return 0;
        }
    //printchars (chars, left, right);
    //int help;
    int midel = left + (right - left)/2;
    //int midnum;

    while (left <= right)
        {
    // //printf ("\nleft(%d) <= right(%d)\n", left, right);
        //midnum = chars [midel].hitnumch_;
    //  //printf ("mid(%d) == %d\n", midel, midnum);
        if (!standsright (chars, left, midel)/* && right != left*/)
            {
    //      //printf ("\nleft(%d) == %d stays wrong\nrights ", left, chars[left].hitnumch_);
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
    //              //printf ("(%d) == %d ", right, chars[right].hitnumch_);
                    right--;
                    }
    //          //printf ("stay right\n");
    //          //printf ("and right(%d) == %d stays wrong\n", right, chars[right].hitnumch_);
                change (chars, left, right);
    //          //printf ("changing left(%d) == %d and it\n", left, chars[left].hitnumch_);
                if (midel == right)
                    {
                    midel = left;
    //              //printf ("midel is now %d == %d\n", midel, chars[midel].hitnumch_);
                    }
                else
                    {
                    if (midel == left)
                        {
                        midel = right;
    //                  //printf ("midel is now %d == %d\n", midel, chars[midel].hitnumch_);
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
        printf ("%d ", chars[i].hitnumch_);
        }
    printf ("\n");
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

void BallGroup::initChars (BallChar chars[])
    {
    for (int i = 0; i < ballsnum_; i++)
        {
        chars[i] = arr_[i].thisChars_;
        chars[i].idch_ = i;
        }
    }

double getAngleBetweenVecs (double x1, double y1, double x2, double y2)
    {
    return acos((x1*x2 + y1*y2)/LengthOf(x1, y1)/LengthOf(x2, y2));
    }

void drawHitTable (BallGroup balls, const int bnum, double x1, double y1, double x2, double y2, int topsnum)
    {
    txSetColor (tablecolor, 5);
    //double xsize = x2 - x1;
    double ysize = y2 - y1;
    double liney = ysize/(topsnum + 1);

    txLine (x1 + 20, y1, x1 + 20, y2);

    txSetColor (vectorcolor, 5);
    txSelectFont ("Comic Sans SM", 25);
    txDrawText (x1 + 20, y1 + 8, x2, y1 + liney + 8, "Они навсегда в\n наших сердцах.");

    BallChar chars[bnum];
    balls.initChars (chars);

    SortBallsCharacteristics (chars, 0, bnum - 1);

    if (bnum < topsnum) topsnum = bnum;
    char help[16] = {};

    for (int i = 0; i < topsnum; i++)
        {
        txSetColor (tablecolor, 5);
        txLine (x1, y1 + liney * (i + 1), x2, y1 + liney * (i + 1));

        txSetColor (vectorcolor, 5);
        sprintf (help, "%d", i + 1);

        txSelectFont ("Comic Sans SM", 25);
        txDrawText (x1 - 3, y1 + liney * (i + 1), x1 + 17, y1 + liney * (i + 2), help);
        txDrawText (x1 + 20, y1 + liney * (i + 1), x2, y1 + liney * (i + 2), balls[chars[bnum - i - 1].idch_].name_);

        balls[chars[bnum - i - 1].idch_].drawAt(x2 - 10, y1  + liney * (i + 1.5));
        }

    txSetColor (tablecolor, 5);
    txLine (x1, y2, x2, y2);
    }

void BallGroup::testAll ()
    {
    for (int i = 0; i < ballsnum_; i++)
        {
        arr_[i].testWallHit();
        }
    }

bool standsright (BallChar chars[], int tests, int mid)
    {
    if (tests < mid)
        {
        if (chars[tests].hitnumch_ < chars[mid].hitnumch_) return true;
        }
    else
        {
        if (chars[tests].hitnumch_ > chars[mid].hitnumch_) return true;
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


bool myAlphaBlend (HDC dest, double xDest, double yDest, double width1, double height1,
                   HDC src,  double xSrc /*= 0*/, double ySrc /*= 0*/, double width2, double height2, double alpha /*= 1.0*/)
    {
    //_TX_IF_TXWINDOW_FAILED        return false;
    //_TX_IF_ARGUMENT_FAILED (dest) return false;
    //_TX_IF_ARGUMENT_FAILED (src)  return false;

    if (alpha < 0) alpha = 0;
    if (alpha > 1) alpha = 1;

    BLENDFUNCTION blend = { AC_SRC_OVER, 0, (BYTE) ROUND (alpha * 255), AC_SRC_ALPHA };
    //return (Win32::AlphaBlend)?
        Win32::AlphaBlend (dest, ROUND (xDest), ROUND (yDest), ROUND (width1), ROUND (height1),
                                     src,  ROUND (xSrc),  ROUND (ySrc),  ROUND (width2), ROUND (height2), blend);
    //:
    //    txGDI (!!(Win32::BitBlt     (dest, ROUND (xDest), ROUND (yDest), ROUND (width1), ROUND (height1),
    //                                 src,  ROUND (xSrc),  ROUND (ySrc),  SRCCOPY))), false;
    return true;
    }



//-----------------------------------------------------------------------------


/*//if (fabs(getAccurateAngle(velxdif, velydif) - getAccurateAngle (corxdif, corydif)) > 90)
    //    {
    //    return 0;
    //    }
    double biggerratio = 1;
    //double biggerspeed;
    //double biggerradius;
    if (LengthOf(wball->getvx(), wball->getvy())/wball->getRadius() > speed_/radius_)
        {
        biggerratio = LengthOf(wball->getvx(), wball->getvy())/wball->getRadius()*10.3;
        //biggerspeed = LengthOf(wball->getvx(), wball->getvy());
        //biggerradius = wball->getRadius();
        }
    else          //TODO
        {         //
        biggerratio = LengthOf(speed_.x, speed_.y)/radius_*10.3;
        //biggerspeed = LengthOf(speed_.x, speed_.y);
        //biggerradius = radius_;
        }
    int retnum = 0;
    for (int i = 0; i < biggerratio; i++)
        {
        if (testCollDoubPairs (wball, wball->getX() + speed_.x * (double)(i)/(double)(biggerratio),
                                    wball->getY() + speed_.y * (double)(i)/(double)(biggerratio),
                                    cords_.x + speed_.x * (double)(i)/(double)(biggerratio),
                                    cords_.y + speed_.y * (double)(i)/(double)(biggerratio)))
            {
            //printf ("OUCH(%s)\n", name_);
            //1 - i/biggerratio;
            this->addCollision();
            //angle = (getAngleTo(wball->getX(), wball->getY()) + 180) + angle_;
            DoubPair dcv1 = {speed_.x, speed_.y};
            DoubPair dcv2 = {wball->getvx(), wball->getvy()};
            //printf ("dcv1 == %f && %f", dcv1.x, dcv1.y);
            //getch();
            double help = (double)(i - 1)/biggerratio;
            dt_ = 1 - help;
            cords_.x += speed_.x*help;
            cords_.y += speed_.y*help;
            wball->moveRatio (help);
            SUPERDoubPair colresults;
            colresults = getBiPolSpeedAfterCollision (dcv1.x, dcv1.y, dcv2.x, dcv2.y,
                                    cords_.x, cords_.y, wball->getX(), wball->getY(),
                                    radius_, wball->getRadius());
            //printf ("v2given == %f, %f\nreturned == %f, %f\n", dcv2.x, dcv2.y, colresults.s.x, colresults.s.y);
            //printf ("v1given == %f, %f\nreturned == %f, %f\n", dcv1.x, dcv1.y, colresults.f.x, colresults.f.y);
            //printf ("i am first(%s)\n", name_);
            //txSetColor (TX_WHITE, 10);
            //txLine (txGetExtentX()/2, txGetExtentY()/2, txGetExtentX()/2 + dcv2.x * 10, txGetExtentY()/2 + dcv2.y * 10);
            //txSetColor (TX_GREEN, 10);
            //txLine (txGetExtentX()/2, txGetExtentY()/2, txGetExtentX()/2 + colresults.s.x * 10, txGetExtentY()/2 + colresults.s.y * 10);
            //getch();
            speed_.x = colresults.f.x;
            speed_.y = colresults.f.y;
            wball->speed_.x = colresults.s.x;
            wball->speed_.y = colresults.s.y;
        //getch();
            retnum = 1;
            }
        }
    return retnum;*/

