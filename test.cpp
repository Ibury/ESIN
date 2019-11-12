#include <iostream>

using namespace std;

long quadrat(int n)
{
    // Pre: n >= 0
    // Post: Retorna n^2
    long res;
    if (n <= 1)
        res = 1;
    else if (n % 2 == 0)
        res = 4 * quadrat(n / 2);
    else
        res = 4 * quadrat(n / 2) + 2 * n - 1;
    return res;
}

int main()
{
    for (auto i = 1U; i <= 10; ++i)
    {
        cout << i << " x " << i << " = " << quadrat(i) << endl;
    }
}