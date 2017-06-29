#include "../include/randomize.h"

static long long RANDOMIZE_STEP = 65535;

long long random_next()
{
        CODE
        return RANDOMIZE_STEP++;
}

long long random_range(long long min, long long max)
{
        CODE
        return random_next;
}