#include <stdio.h>
#include "libgeom/geom.h"
#define n 100

int main()
{

    struct figura circle;
    char ptr[100] = {'0'};
    char rad[10] = {'0'};
    fgets(ptr, n * sizeof(int), stdin);
    radius(ptr, rad);
    sixcheck(ptr);
    unexpected_check(ptr);
    skobcheck(ptr, rad);
    probelcheck1(ptr);
    xcheck(ptr);
    ycheck(ptr);
    radcheck(rad, ptr);
    radminus(ptr, rad);
    namecheck(ptr, &circle, rad);
    return 0;
}
