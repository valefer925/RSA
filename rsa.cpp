#include <iostream>
#include<math.h>
using namespace std;

long long euclidesExt(long long a, long long b, long long* x, long long* y)
{
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }

    long long x1, y1;
    long long gcd = euclidesExt(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}

long long inversoMult(long long int a, long long int n)
{
    long long x, y;
    long long g = euclidesExt(a, n, &x, &y);
    if (g != 1)
        return -1;
    else
    {
        return (x % n + n) % n;
    }
}

long long int gcd(long long int a, long long int b) {
    long long int t;
    while (true) {
        t = a % b;
        if (t == 0)
            return b;
        a = b;
        b = t;
    }
}

void NAIVE_RSA_KEY_GENERATOR(long long int p, long long int q, long long int& n, long long int& e, long long int& d) {
    n = p * q;
    long long int phi = (p - 1) * (q - 1);
    long long int aux = 0;
    while (e < phi) { // e = {2,(p - 1) * (q - 1)}
        aux = gcd(e, phi);
        if (aux == 1) {
            d = inversoMult(e, phi);
            break;
        }
        else
            e++;
    }
}
long long int mod(unsigned long long int base, unsigned long long int exp, unsigned long long int mod)
{
    long int x = 1;
    int i;
    long long int pow = base % mod;

    for (i = 0; i < sizeof(int) * 64; i++)
    {
        int least_sig_bit = 0x00000001 & (exp >> i);
        if (least_sig_bit)
            x = (x * pow) % mod;
        pow = (pow * pow) % mod;
    }

    return x;
}

int main() {
    long long int m = 0, p = 3, q = 11, n = 0, e = 2, d = 0, Pm = 0, Sc = 0;

    NAIVE_RSA_KEY_GENERATOR(p, q, n, e, d);
    int same = 0;
    for (int i = 0; i < n; i++)
    {
        m = i;
        int c = mod(m, e, n);
        if (m == c)
            same++;
        cout << "\t" << m << " ^ " << e << " mod " << n << "    c: " << "  " << "m: " << mod(c, d, n) << endl;
        cout << endl;

    }
    cout << "mc = md  ->   " << same << endl;
    return 0;
}