#include "../include/randomize.h"

static unsigned long mwc()
{
        static unsigned long x = 3456789;
        static unsigned long y = 362436069;
        static unsigned long z = 77465321;
        static unsigned long c = 13579;
        unsigned long long t;
        
        t = 6905990LL * x + c;
        x = y;
        y = z;
        c = (t >> 32);
        
        return z = (t & 0xffffffff);
}

unsigned long random_next()
{
        return mwc();
}

unsigned long random_next_range(unsigned long min, unsigned long max)
{
        return random_next() % (max - min + 1) + min;
}