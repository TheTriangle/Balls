#include "TXLib.h"
#include "Ball.h"
int msizearr = 3565;
int keynum = -4;
int ashelpg = 0;
bool TestSortedChars (BallChar arr[], int finish, int start);
int findpair (int arr[], int start, int finish, int forel, int cent);

void TestCharWtf (BallChar getarr[],
                int (*ff)(BallChar arr[], int start, int finish),
                bool (*tf)(BallChar arr[], int finish, int start),
                int sizearr);

POINT quicksort (int arr[], int start, int finish, int* assigh, int* comparh);
POINT sortleast (int arr[], int start, int finish, int* assigh, int* comparh);
bool compare (int c1[], int c2[], int start, int finish);
void ROL (int arr[], int start, int finish, int* assig, int* compar);
void ROR (int arr[], int start, int finish, int* assig, int* compar);
void Test (int getarr[], int exitarr[], void (*f)(int arr[], int finish, int start, int* assig, int* compar), char tn[], int size = keynum);
bool TestSorted (int tarr[], int start, int finish);
void printdata(int data[], int start, int finish);
void swap (int arr[], int ela, int elb, int* assig = &ashelpg);
int findleast (int arr[], int start, int finish, int* assig, int* compar);
void TestWtf (int getarr[], POINT (*ff) (int arr[], int start, int finish, int* assig, int* compar), bool (*tf)(int arr[], int finish, int start), char tn[], int sizearr);


int main()
    {
    txCreateWindow (800, 600);

    /*int t1g[] = {0, 1, 1, 1, 1, 1};
    int t1a[] = {1, 0, 1, 1, 1, 1};
    Test (t1g, t1a, *ROR, "T1", sizeof(t1g)/sizeof(t1g[0])); //1
    int t2g[] = {1, 0, 1, 1, 1, 1};
    int t2a[] = {1, 1, 0, 1, 1, 1};
    Test (t2g, t2a, *ROR, "T2", sizeof(t2g)/sizeof(t2g[0])); //2
    int t3g[] = {1, 1, 0, 1, 1, 1};
    int t3a[] = {1, 1, 1, 0, 1, 1};
    Test (t3g, t3a, *ROR, "T3", sizeof(t3g)/sizeof(t3g[0])); //3
    int t4g[] = {1, 1, 1, 0, 1, 1};
    int t4a[] = {1, 1, 1, 1, 0, 1};
    Test (t4g, t4a, *ROR, "T4", sizeof(t4g)/sizeof(t4g[0])); //4
    int t5g[] = {1, 1, 1, 1, 0, 1};
    int t5a[] = {1, 1, 1, 1, 1, 0};
    Test (t5g, t5a, *ROR, "T5", sizeof(t5g)/sizeof(t5g[0])); //5
    int t6g[] = {1, 1, 1, 1, 1, 0};
    int t6a[] = {0, 1, 1, 1, 1, 1};
    Test (t6g, t6a, *ROR, "T6", sizeof(t6g)/sizeof(t6g[0])); //6
    */
    int *sortinganswers = new int [msizearr];
    tx_auto_func (delete [] sortinganswers);
    const int testingsize = 10;
    BallChar testingdata[testingsize];

    for (int i = 0; i < 10; i++)
        {
        //printf ("EEEEEEEEE%d\n", 1);
        for (int j = 0; j < testingsize; j++)
                {
                testingdata[j].hitnumch = rand()%10;
                }
        //printdata (testingdata, 0, testingsize);
        TestCharWtf (testingdata, *SortBallsCharacteristics, *TestSortedChars,  testingsize);
        //printf ("DDDDDDD\n");
        }
   // printf ("i've finished cycle\n");

    /*for (int i = 0; i < 99; i++)
        {
        //printf ("A%d", i);
        for (int j = 0; j < testingsize; j++)
            {
            sortinganswers[j] = rand()%100;
            }

        TestWtf (sortinganswers, *quicksort, *TestSorted, "quick", i);

        }
    //*/

    //printf ("AA");
    return 0;
    }


void Test (int getarr[], int exitarr[], void (*f)(int arr[], int start, int finish, int* assig, int* compar), char tn[], int size)
    {
    if (size == keynum) size = sizeof (getarr)/sizeof (getarr[0]);
    //printf ("size == %d (%s)", size, tn);
    int as = 0;
    int co = 0;
    f(getarr, 0, size, &as, &co);
    if (!compare (getarr, exitarr, 0, size))
        {
        $E;
        printf ("\nERROR ");
        printdata (getarr, 0, size);
        printf ("size == %d", size);
        }
    }



bool TestSortedChars (BallChar arr[], int finish, int start)
    {
    int old = start;
    for (int i = start + 1; i < finish; i++)
        {
        if (arr[i].hitnumch < arr[old].hitnumch) return false;
        old = i;
        }
    return true;
    }

void TestWtf (int getarr[], POINT (*ff)(int arr[], int start, int finish, int* assig, int* compar), bool (*tf)(int arr[], int finish, int start), char tn[], int sizearr)
    {
    //int sizearr = sizeof (getarr)/sizeof (getarr[0]);
    int as = 0;
    int co = 0;
    //int *harr = new int [msizearr];
    ff(getarr, 0, sizearr, &as, &co);

    if (!tf(getarr, sizearr, 0))
        {
        $E;
        printf ("\nERROR");
        printdata (getarr, 0, sizearr);
        }
    }



void TestCharWtf (BallChar getarr[], int (*ff)(BallChar arr[], int start, int finish), bool (*tf)(BallChar arr[], int finish, int start),  int sizearr)
    {
    //int sizearr = sizeof (getarr)/sizeof (getarr[0]);
    //printf ("AAAAAAAAAAAAAAAA\n");
    int as = 0;
    int co = 0;
    //int *harr = new int [msizearr];
    ff(getarr, 0, sizearr);

    bool help = tf(getarr, sizearr, 0);
    //printf ("CCCCCCCCCCCCC\n");
    if (!help)
        {
        //printf ("BBBBBBBBBBBBBBBB\n");
        $E;
        printf ("\nERROR");
        //printdata (getarr, 0, sizearr);
        }
    }







bool TestSorted (int arr[], int start, int finish)
    {
    int old = start;
    for (int i = start + 1; i < finish; i++)
        {
        if (arr[i] < arr[old]) return false;
        old = i;
        }
    return true;
    }



bool compare (int c1[], int c2[], int start, int finish)
    {
    for (int i = start; i < finish; i++)
        {
        if (c1[i] != c2[i]) return false;
        }
    return true;
    }



void ROR (int arr[], int start, int finish, int* assig, int* compar)
    {
    int last = arr [finish - 1];
    int help = 0;
    //eqcount++;

    for (int i = finish - 1; i > start; i--)
        {
        arr[i] = help;
        arr[i] = arr [i - 1];
        //eqcount++;
         *assig++;
        *compar++;
        }
    arr [start] = last;
    }






void ROL (int arr[], int start, int finish, int* assig, int* compar)
    {
    int first = arr [start];
    int help = 0;

    for (int i = start; i < finish - 1; i++)
        {
        arr[i] = help;
        arr[i] = arr [i + 1];
        //eqcount++;
         *assig++;
        *compar++;
        }
    arr [finish - 1] = first;
    }







int findpair (int arr[], int start, int finish, int forel, int cent)
    {
    int flg = 0;
    if (cent == forel) flg = 1;
    else flg = ((cent - forel)/fabs(cent - forel) + 1)/2;      //1 if cent > forel; 0 if cent < forel
    //printf ("\n(flg == %d)", flg);
    /*for (int i = start * f  lg  + (finish - 1) * fabs(flg - 1); i <= start * fabs(flg - 1) + (finish - 1) * flg; i += flg * 2 - 1)
        {      //1 or -1
        if ((flg * 2 - 1) * arr[i] < (flg * 2 - 1) * arr[forel]) return i;
        }*/

    if (flg)
        {
        for (int i = finish - 1; i >= start; i--)
            {
            if (arr[i] < arr[cent]) return i;
            }
        }
    else
        {
        for (int i = 0; i < finish; i++)
            {
            if (arr[i] > arr[cent]) return i;
            }
        }
    return keynum;

    }



POINT sortleast (int arr[], int start, int finish, int* assigh, int* comparh)
    {
    //printf ("\nass = %d, com = %d\n", *assig, *compar);
    int assig = *assigh;
    int compar = *comparh;
    int least = keynum;
    for (int i = start; i < finish; i++)
        {

        least = findleast (arr, start + i, finish, &assig, &compar);
        if (least != keynum)
            {
            swap (arr, least, i, &assig);
            //printf ("\n2 ass = %d, com = %d 2\n", assig, compar);
            assig++;
            compar++;
            }
        //printf ("\n1 ass = %d, com = %d 1\n", assig, compar);
        //*assig++;

        }
    //printf ("\nass = %d, com = %d\n", assig, compar);
    return {assig, compar};
    }




POINT quicksort (int arr[], int start, int finish, int* assigh, int* comparh)
    {
    //$g;
    //printdata (arr, start, finish);
    //$w;
    int assig = *assigh;
    int compar = *comparh;

    //printf ("\nstart == %d, finish == %d, mid == %d", start, finish, cenpos);
    //int elfromst = 0;
    //int elfromfi = 0;

    int cenpos = (finish - start)/2 + start;
    int centel = arr[cenpos];
    if (finish - 1 <= 0 || start < 0) return {assig, compar};
    if (finish - 1 <= start) return {assig, compar};
    if (finish - 1 == start + 1)
        {
        if (arr[start] > arr[finish - 1]) swap (arr, start, finish - 1, &assig);
        return {assig, compar};
        }
    //printf ("\nstart == %d(%d), finish == %d(%d), mid == %d(%d)", start, arr[start], finish - 1, arr[finish - 1 ], cenpos, arr[cenpos]);
    //getch();
    //int ansarr [] = {};

    //printf ("AAAAAAAAAAAAAAAAAAAAAA");

    //int *exeprions = new int [msizearr] = 0;

    int exeptionsnum = 0;

    int pairn = 0;
    for (int i = start; i < cenpos; i++)
        {
        if (arr[i] > centel)
            {
            pairn = findpair (arr, start, finish, i, cenpos);
            //printf ("\npair for %ds(r = %d) el is %d", i, arr[i], pairn);
            if (pairn == keynum)
                {
                swap (arr, cenpos, start, &assig);
                //quicksort (arr,  start, cenpos, &assig, &compar);
                //printf ("swapping %d and %d", cenpos, start);
                cenpos = start + 1;
                quicksort (arr, cenpos, finish, &assig, &compar);
                return {assig, compar};
                }
            if (pairn < cenpos)
                {
                ROL (arr, i, cenpos + 1, &assig, &compar);
                //printf ("cr");
                cenpos = cenpos - 1;
                i--;
                }
            else
                {
                swap (arr, i, pairn, &assig);
                }
            //printdata (arr, start, finish);
            //printf ("cenpos == %d", cenpos);
            }
        compar++;
        }
    for (int i = cenpos + 1; i < finish; i++)
        {
        if (arr[i] <= centel)
            {
            pairn = findpair (arr, start, finish, i, cenpos);
            //printf ("\npair for %ds(%d) el is %d", i, arr[i], pairn);
            if (pairn == keynum)
                {
                swap (arr, cenpos, finish - 1, &assig);
                //printf ("\nswapping mid - %d(%d) and finish - 1 - %d(%d)", cenpos, arr[cenpos], finish - 1, arr[finish - 1]);
                cenpos = finish - 1;
                quicksort (arr,  start, cenpos, &assig, &compar);
                //quicksort (arr, cenpos, finish, &assig, &compar);
                return {assig, compar};
                }
            if (pairn > cenpos)
                {
                ROR (arr, cenpos, i + 1, &assig, &compar);
                cenpos = cenpos + 1;
                i++;
                }
            else
                {
                swap (arr, i, pairn, &assig);
                }
            //printdata (arr, start, finish);
            //printf ("cenpos == %d", cenpos);
            }
        compar++;
        }

    //printf ("\nFINISHINGCYCLE\n");
    //$E;
    //printdata (arr,  start, cenpos);
    //printdata (arr, cenpos, finish);
    //$W;
    quicksort (arr,  start, cenpos, &assig, &compar);
    quicksort (arr, cenpos, finish, &assig, &compar);
    return {assig, compar};
    }


int findleast (int arr[], int start, int finish, int* assig, int* compar)
    {
    int leastel  = arr[start] + 1;
    int leastpos = keynum;

    for (int i = start + 1; i < finish; i++)
        {
        if (arr[i] < leastel)
            {
            leastel = arr[i];
            leastpos = i;
            *assig  += 2;
            }
        *compar += 1;
        }
    return leastpos;
    }






void swap (int arr[], int ela, int elb, int* assig)
    {
    int help = arr[ela];
    arr[ela] = arr[elb];
    arr[elb] = help;
    *assig += 3;
    }







void printdata(int data[], int start, int finish)
    {
    printf ("\n");
    for (int i = start; i < finish; i++)
        {
        printf ("%d ", data[i]);
        }
    printf ("\n");
    }
