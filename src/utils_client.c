#include "mlmsim.h"

int easy_pow(int base, int pow)
{
    int sum;

    if (base <= 1)
        return (base);
    sum = base;
    while (pow > 1)
    {
        sum *= base;
        pow--;
    }
    return (sum);
}