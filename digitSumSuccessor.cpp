#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int sumDigit(long long nb)
{

    int Sum = 0;

    while (nb > 0)
    {
        Sum += nb % 10;
        nb /= 10;
    }
    return Sum;
}
/**
 *
 *
 * @param n le nombre de chiffres dans le nombre
 */
long long nbzero(long long n)
{

    if (n < 10)
        return n;

    int nb = 1;
    long long p = pow(10, nb);
    while (n % p == 0)
    {
        nb++;
        p = pow(10, nb);
    }
    return pow(10, nb - 1);
}
long long nineadd(long long n)
{
    if (n == 0)
    {
        return 1;
    }

    long long r = 0;
    while (n > 0)
    {
        r += 9 * pow(10, n);
        n--;
    }
    return r;
}

int main()
{
    long long n;
    cin >> n;
    cin.ignore();
    long long cpt = n + 1;
    cerr << " objectif ==>" << n << endl;
    ;
    int sd = sumDigit(n);
    cerr << "SD objectif ==>" << sd << endl;
    while (cpt <= 100000000000)
    {

        long long tmp = sumDigit(cpt);
        if (tmp == sd)
        {
            break;
        }
        if (tmp > sd)
        {
            // pow(10,nbzero(n)) - n%10)

            cpt += nbzero(n);
        }
        else if (sd > tmp + 10)
        {
            cpt += nineadd((sd - tmp) / 9 - 1);
        }
        else
            cpt += (sd - tmp);

        cerr << "cpt AFT==>" << cpt << endl;
    }
    // Write an answer using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << cpt << endl;
}
